/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define ADK_INTERNAL
#include "BT.h"
#include "HCI.h"
#include "sgBuf.h"
#include "GenericTypeDefs.h"
#include "../PHY/usb_host_bluetooth.h"
#include "../debug.h"
#include "../Bt_stack/bt_common.h"
#include "../Microchip/Include/USB/usb.h"

#define BT_VERBOSE		0
#define PACKET_RX_BACKLOG_SZ	4

//Dummy device name. Use the btSetLocalName in main to change name
#define BT_DEVICE_NAME "PIC24F"

//Bluetooth device
BtDevice gBtDevice;

// Dummy buffer for unusable USB packets
//static uint8_t* backlog[PACKET_RX_BACKLOG_SZ] = {0, };

//Function pointers for bluetooth event handle
static BtFuncs cbks;

// Buffer to store Events USB packets
static uint32_t packetStoreEVT[(BT_RX_BUF_SZ + 3) >> 2];

//Buffer to store ACL RX packets
static uint32_t packetStoreACL[(BT_RX_BUF_SZ + 3) >> 2];

//Buffer to store ACL packets we will send
static uint32_t packetStoreACL_TX[(BT_RX_BUF_SZ + 3) >> 2];

//Buffer to store all commands we want to send
static uint32_t packetStoreCMD[(BT_RX_BUF_SZ + 3) >> 2];


// Pointers to the appropriate buffer
static uint8_t* packetEVT = (uint8_t*)packetStoreEVT;
static uint8_t* packetACL = (uint8_t*)packetStoreACL;
static uint8_t* packetCMD = (uint8_t*)packetStoreCMD;


static uint8_t pageState;
static uint16_t gAclPacketsCanSend = 0;


// Linked list to store unused packets
typedef struct BtEnqueuedNode{

    struct BtEnqueuedNode* next;

    sg_buf* buf;
    uint16_t conn;
    char first;
    uint8_t bcastType;

}BtEnqueuedNode;

//Linked list head pointer
BtEnqueuedNode* enqueuedPackets = 0;

// Static function prototypes
static void btDiscoverableConnectable(void);

/**
 * Send commands to Enpoint 0 (Command endpoint)
 *
 * @param buf : buffer that contains the buffer to send
 * @param sz :  numbers of byte to send
 */
static void btUSBSendEP0(const uint8_t* buf, uint32_t sz){
    //Get dongle Address
    BYTE bDevAddr = USBHostBluetoothGetDeviceAddress();

    // Type of the URB
    BYTE bType = USB_SETUP_HOST_TO_DEVICE |
                 USB_SETUP_TYPE_CLASS |
                 USB_SETUP_RECIPIENT_DEVICE;
    
    //URB for the Host driver
    BOOL bRetVal = USBHostIssueDeviceRequest(bDevAddr, bType, 0, 0, 0, sz,
            (BYTE *)buf, USB_DEVICE_REQUEST_SET, 0x00);

    // Test the return value
    if (bRetVal == USB_SUCCESS )
    {
        DelayMs(25);
        return 1;
    }
    return 0;
}

/**
 * Send ACL data to the Endpoint 2
 * @param buf : Buffer containing the ACL data to be send
 * @param sz : number of byte to send
 */
static void btUSBSendACL(const uint8_t* buf, uint32_t sz){
   BYTE bDevAddr = USBHostBluetoothGetDeviceAddress();
   BOOL bRetVal = USBHostWrite(bDevAddr,_EP02_OUT, (BYTE* ) buf, sz);

    if(bRetVal == USB_SUCCESS)
    {
        DelayMs(1);
        SIOPrintString("USB ACL WR succ\r\n");
        return 1;
    }
   SIOPrintString("USB ACL WR err\r\n");
    return 0;
}


/**
 * Start a packet in "packet"
 * @param ogf : OGF number. See BT Core 4.0 for more details
 * @param ocf : OCF number. See BT Core 4.0 for more details
 * @return : "state" pointer
 */
static uint8_t* hciCmdPacketStart(uint16_t ogf, uint16_t ocf){		

    HCI_Cmd* cmd = (HCI_Cmd*)packetStoreCMD;

    cmd->opcode = HCI_OPCODE(ogf, ocf);
    // The first 2 bytes is command and the third is the size
    return packetCMD + 3;
}

/**
 * Add a 32 bit value (4 bytes) to the command buffer
 * @param state : "state" pointer to the current command state
 * @param val : value to write
 * @return : "state" pointer
 */
static uint8_t* hciCmdPacketAddU32(uint8_t* state, uint32_t val){	//add a uint32 to packet, update state

    *state++ = val;
    *state++ = val >> 8;
    *state++ = val >> 16;
    *state++ = val >> 24;

    return state;
}

/**
 * Add a 24 bit value (3 bytes) to the command buffer
 * @param state : "state" pointer to the current command state
 * @param val : value to write
 * @return : "state" pointer
 */
static uint8_t* hciCmdPacketAddU24(uint8_t* state, uint32_t val){	//add a uint24 to packet, update state

    *state++ = val;
    *state++ = val >> 8;
    *state++ = val >> 16;

    return state;
}

/**
 * Add a 16 bit value (2 bytes) to the command buffer
 * @param state : "state" pointer to the current command state
 * @param val : value to write
 * @return : "state" pointer
 */
static uint8_t* hciCmdPacketAddU16(uint8_t* state, uint16_t val){	//add a uint32 to packet, update state

    *state++ = val;
    *state++ = val >> 8;

    return state;
}


/**
 * Add a 8 bit value (1 byte) to the command buffer
 * @param state : "state" pointer to the current command state
 * @param val : value to write
 * @return : "state" pointer
 */
static uint8_t* hciCmdPacketAddU8(uint8_t* state, uint8_t val){		//add a uint32 to packet, update state

    *state++ = val;

    return state;
}

/**
 * Finish the command buffer with calculate the size
 * @param state : "state" pointer
 * @return : size of the packet
 */
static uint32_t hciCmdPacketFinish(uint8_t* state){			//finish, return size to send

    HCI_Cmd* cmd = (HCI_Cmd*)packetStoreCMD;
    uint32_t paramLen = state - packetCMD - 3;

    cmd->totalParamLen = paramLen;
    return paramLen + 3;
}


/**
 * Send the command packet through USB
 * @param cmd : Pointer to the HCI command finished buffer
 */
static void btTxCmdPacketEx(const HCI_Cmd* cmd){

    // Send packet on the command endpoint
    btUSBSendEP0((uint8_t*)cmd, 3 + cmd->totalParamLen);
}

/**
 * Wrap function to simplify upper code
 */
static void btTxCmdPacket(void){

   btTxCmdPacketEx((HCI_Cmd*)packetStoreCMD);
}

/**
 * NOT USED IN THE PROJECT
 * Transmit an ACL data to the correst endpoint (EP2)
 * @param conn : Connection handle
 * @param first ? (Maybe the first byte to be sent)
 * @param bcastType : ? (Read the documentation)
 * @param data : Data buffer of ACL packets
 * @param sz : size of the ACL data packets
 */
static void btAclDataTxBuf(uint16_t conn, char first, uint8_t bcastType, const uint8_t* data, uint16_t sz){
/*
    // Data buffer preparation
    WORD i = 0;
    //Calculate header + packet length
    WORD aTotalLength = sz + 4;
    
    //Pointer to the ACL buffer to send
    HCI_ACL_Data* acl = (HCI_ACL_Data*)packetStoreACL_TX;

    //Get ACL info
    acl->info = conn | (first ? 0x2000 : 0x1000) | ((uint32_t)bcastType) << 14;
    //Writing total length
    acl->totalDataLen = sz;

    //Michael's hack
    for(i=0;i<sz;i++)
    {
     acl->data[i] = data[i] ;
    }

    //Send ACL buffer
    btUSBSendACL((uint8_t*)acl,aTotalLength);
  */
}

/**
 * Send ACL data from a Linked list (sg_buf)
 * @param conn : Connection handle
 * @param first : ?
 * @param bcastType : ?
 * @param buf : Linked list header
 */
static void btAclDoDataTx(uint16_t conn, char first, uint8_t bcastType, sg_buf* buf){

    sg_iter iter;
    HCI_ACL_Data* acl = (HCI_ACL_Data*)packetStoreACL_TX;
    const uint8_t* data;
    //To save data pointer address
    BYTE *data_addr = 0x00 ;
    uint32_t len;

    //Decrease the ACL packets counter
    gAclPacketsCanSend --;

    //Get ACL packet info
    acl->info = conn | (first ? 0x2000 : 0x1000) | ((uint32_t)bcastType) << 14;

    //Get total of length
    acl->totalDataLen = sg_length(buf);
    SIOPrintString("[BT ACL TX] : Data len = ");
    SIOPutDec(acl->totalDataLen);
    SIOPrintString("\r\n");

    //Get iterator on linked list
    iter = sg_iter_start(buf);

    //get the address
    data_addr = acl->data;

    while(sg_iter_next(&iter, &data, &len))
    {
        WORD i = 0;
        //Copy the datas into the buffer
        for(i=0;i<len;i++)
        {
            data_addr[i] = data[i];
        }

        // Offset of Data addr
        data_addr += i ;
    }



    //Send the ACL Buffer
    btUSBSendACL((uint8_t*)acl,4+acl->totalDataLen );

    //Free the linked list
    sg_free(buf);
    //Free the buffer
    free(buf);
}

/**
 * Try to send the linked list buffer
 * @param conn : Connection handle
 * @param first : ?
 * @param bcastType : ?
 * @param buf : Linked list header
 */
void btAclDataTx(uint16_t conn, char first, uint8_t bcastType, sg_buf* buf){

    // Test  if we reach the max number of ACL sent packets
    if(gAclPacketsCanSend){

        btAclDoDataTx(conn, first, bcastType, buf);
    }
    else{
        SIOPrintString("ACL packets enqeued !\r\n");
        //We must to store the packets we can't send yet
        BtEnqueuedNode *q = enqueuedPackets, *n = malloc(sizeof(BtEnqueuedNode));
        // Oops, not enough memory for malloc
        if(!n){

            //packet dropped due to lack of memory...sorry
            SIOPrintString("ACL packets enqeued failed !\r\n");
            sg_free(buf);
            free(buf);
            return;
        }
        //Configuring Enqued node
        n->buf = buf;
        n->conn = conn;
        n->first = first;
        n->bcastType = bcastType;
        n->next = 0x00;

        while(q && q->next)
        {
            q = q->next;
        }
        if(q) 
        {
            q->next = n;
        }
        else 
        {
            enqueuedPackets = n;
        }
    }
}

/**
 * Enqueue non-handled packets. We don't use it. Only here for code compatibility
 * @param typ : Type of received packet
 */
/*
static void btEnqueuePacket(uint8_t typ){	//we got a packet but it's not for us - enqueue it for someone else to use

    uint8_t* copy;
    unsigned sz, i;

    switch(typ){
        case UART_PKT_TYP_ACL:
            sz = ((HCI_ACL_Data*)packetStoreACL)->totalDataLen + 4L;
            break;

        case UART_PKT_TYP_SCO:
           // sz = ((HCI_SCO_Data*)packetStore)->totalDataLen + 3L;
            break;

        case UART_PKT_TYP_EVT:
            sz = ((HCI_Event*)packetStoreEVT)->totalParamLen + 2L;
            break;

        default:
            //no idea what it is...drop it on the floor
            return;
    }

    copy = malloc(sz + 1);
    if(!copy) return; //cannot alloc -> fail

    copy[0] = typ;
   // for(i = 0; i < sz; i++) copy[i + 1] = packet[i];
    for(i = 0; i < PACKET_RX_BACKLOG_SZ; i++) if(!backlog[i]) break;
    if(i == PACKET_RX_BACKLOG_SZ){ //we have to drop something

        #if BT_VERBOSE

            dbgPrintf("BT: dropping backlog item: %d, 0x%x\n", backlog[0][0], backlog[0][1]);

        #endif
        free(backlog[0]);
        for(i = 0; i < PACKET_RX_BACKLOG_SZ - 1; i++) backlog[i] = backlog[i + 1];
    }
    backlog[i] = copy;
}
*/



/**
 * Scans the differents endpoints to see if some data are available
 */
void USBScan_Google()
{
    BYTE bDevAddr = USBHostBluetoothGetDeviceAddress();
    HCI_Event* e = (HCI_Event*)packetStoreEVT;
    HCI_ACL_Data* acl = (HCI_ACL_Data*)packetStoreACL;
    
    if (bDevAddr != 0)
    {
        if(USBHostBluetoothRx1IsBusy(bDevAddr) ==FALSE)
        {
            //Scan the EP1 (Event data)
            USBHostBluetoothRead_EP1(bDevAddr,e,EVENT_PACKET_LENGTH);
	}
        else
        {
            
        }

        if(USBHostBluetoothRx2IsBusy(bDevAddr) == FALSE)
        {
            //Scan the EP2 (ACL data)
            USBHostBluetoothRead_EP2(bDevAddr,acl, DATA_PACKET_LENGTH );
	}
        else
        {

        }
    }
}

/**
 * Event handler of the application
 * @param address : Address of the USB device how created the event
 * @param event : Event type
 * @param data : packet received
 * @param size : size of the packet
 * @return : TRUE if handled
 */
BOOL USB_GoogleADKEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    HCI_Event* e = (HCI_Event*)packetStoreEVT;
    HCI_ACL_Data* acl = (HCI_ACL_Data*)packetStoreACL;
    uint8_t* packetState;
    uint16_t conn;
    uint8_t mac[6];
    uint8_t buf[16];
    uint16_t i, j;
    uint8_t pinVal = 0 ;

    switch (event)
    {
        //In case we introduce the bluetooth dongle in the USB port
        case EVENT_BLUETOOTH_ATTACH:
            if (size == sizeof(BLUETOOTH_DEVICE_ID))
            {
                ((BLUETOOTH_DEVICE_ID *)data)->deviceAddress = address;
                SIOPrintString("Generic device connected, deviceAddress=");
                SIOPutDec(address);
                SIOPutChar('\r');
                SIOPutChar('\n');

                //Initializing and Configuring the bt dongle
                 adkInit();
                 return TRUE;
            }
            break;

        //In case we eject the dongle
        case EVENT_BLUETOOTH_DETACH:
            SIOPrintString("USB device disconnected\r\n");
            *(BYTE *)data   = 0;
            gBtDevice.isInitialized = FALSE;
            
            return TRUE;

        //When sco data is send...useless for us
        case EVENT_BLUETOOTH_TX2_DONE:
            return TRUE;

        //When we receive event from interrupt endpoint
        case EVENT_BLUETOOTH_RX1_DONE:
            if(NULL != data)
            {
            //SEE HCI CORE v4.0 SPECIFICATIONS

            //Connection request
            if(e->eventCode == HCI_EVT_Connection_Request_Event){
                SIOPrintString("HCI Connexion Request event\r\n");

                uint32_t dc = e->params[6] + (((uint32_t)e->params[7]) << 8) + (((uint32_t)e->params[8]) << 16);

                for(i = 0; i < sizeof(mac); i++) mac[i] = e->params[i];

                if(cbks.BtConnReqF(cbks.userData, mac, dc, e->params[9])){ //accept it

                    packetState = hciCmdPacketStart(HCI_OGF_Link_Control, HCI_CMD_Accept_Connection_Request);
                    i = 1;
                }
                else{ //reject it

                    packetState = hciCmdPacketStart(HCI_OGF_Link_Control, HCI_CMD_Reject_Connection_Request);
                    i = 0x0F; //rejected...
                }
                packetState = hciCmdPacketAddU8(packetState, mac[0]);
                packetState = hciCmdPacketAddU8(packetState, mac[1]);
                packetState = hciCmdPacketAddU8(packetState, mac[2]);
                packetState = hciCmdPacketAddU8(packetState, mac[3]);
                packetState = hciCmdPacketAddU8(packetState, mac[4]);
                packetState = hciCmdPacketAddU8(packetState, mac[5]);
                packetState = hciCmdPacketAddU8(packetState, i); //we'll be the slave on the connection...for now
                hciCmdPacketFinish(packetState);
                btTxCmdPacket();
            }
            //Status event... not complete yet
            else if(e->eventCode == HCI_EVT_Command_Status_Event)
            {
                SIOPrintString("HCI Status event\r\n");
                //TODO Handle the status code
                btGetStatus(e);
            }

            //Connection complete with the pair device
            else if(e->eventCode == HCI_EVT_Connection_Complete_Event && !e->params[0]){
                SIOPrintString("HCI Connection complete event\r\n");
                conn = e->params[1] + (((uint32_t)e->params[2]) << 8);

                cbks.BtConnStartF(cbks.userData, conn, e->params + 3, e->params[9], e->params[10]);
            }

            // Compatibility event...we dont'use it for the moment
            else if(e->eventCode == HCI_EVT_Max_Slots_Change_Event)
            {
                SIOPrintString("HCI Max slot event : Con = ");
                SIOPutHex(e->params[0] | (e->params[1]<<8));
                SIOPrintString(" Slots = ");
                SIOPutHex(e->params[2]);
                SIOPrintString("\r\n");

            }
            // If the dongle lost the connection with the pair
            else if(e->eventCode == HCI_EVT_Disconnection_Complete_Event){

                SIOPrintString("HCI Disc event\r\n");
                BtEnqueuedNode *t, *n = enqueuedPackets, *p = 0x00;
                conn = e->params[1] + (((uint32_t)e->params[2]) << 8);

                cbks.BtConnEndF(cbks.userData, conn, e->params[3]);

                while(n){

                    if(n->conn == conn){

                        if(p) p->next = n->next;
                        else enqueuedPackets = n->next;
                        t = n;
                        n = n->next;
                        sg_free(t->buf);
                        free(t->buf);
                        free(t);
                    }
                    else{

                        p = n;
                        n = n->next;
                    }
                }
            }

            // Pin request ?? Don't know if necessary for SSP
            else if(e->eventCode == HCI_EVT_PIN_Code_Request_Event){
                SIOPrintString("HCI Pin requ event\r\n");
                for(i = 0; i < sizeof(mac); i++) 
                {
                    mac[i] = e->params[i];
                }
                pinVal = cbks.BtPinRequestF(cbks.userData, mac, buf);
                packetState = hciCmdPacketStart(HCI_OGF_Link_Control, pinVal ? HCI_CMD_PIN_Code_Request_Reply : HCI_CMD_PIN_Code_Request_Negative_Reply);
                packetState = hciCmdPacketAddU8(packetState, mac[0]);
                packetState = hciCmdPacketAddU8(packetState, mac[1]);
                packetState = hciCmdPacketAddU8(packetState, mac[2]);
                packetState = hciCmdPacketAddU8(packetState, mac[3]);
                packetState = hciCmdPacketAddU8(packetState, mac[4]);
                packetState = hciCmdPacketAddU8(packetState, mac[5]);

                if(pinVal){ //accept

                    packetState = hciCmdPacketAddU8(packetState, pinVal);
                    for(j = 0; j < 16; j++) 
                    {
                        packetState = hciCmdPacketAddU8(packetState, buf[j]);
                    }
                }
                hciCmdPacketFinish(packetState);
                btTxCmdPacket();
            }

            //Number of completed packets
            else if(e->eventCode == HCI_EVT_Number_Of_Completed_Packets_Event){
                SIOPrintString("HCI Num complete ACL \r\n");
                uint8_t numHandles = e->params[0];

                for(i = 0; i < numHandles; i++)
                {
                    gAclPacketsCanSend += (((uint16_t)e->params[1 + i * 4 + 3]) << 8) | e->params[1 + i * 4 + 2];
                }
                
                while(gAclPacketsCanSend && enqueuedPackets){

                    BtEnqueuedNode* n = enqueuedPackets;

                    enqueuedPackets = n->next;
                    btAclDoDataTx(n->conn, n->first, n->bcastType, n->buf);
                    free(n);
                }
            }

            // Link key request event
            else if(e->eventCode == HCI_EVT_Link_Key_Request_Event){
                SIOPrintString("HCI Link key req \r\n");
                for(i = 0; i < sizeof(mac); i++) 
                {
                    mac[i] = e->params[i];
                }
                
                i = cbks.BtLinkKeyRequestF(cbks.userData, mac, buf);
                SIOPrintString("BT Link key res : ");
                SIOPutDec(i);
                SIOPrintString("\r\n");
                packetState = hciCmdPacketStart(HCI_OGF_Link_Control, i ? HCI_CMD_Link_Key_Request_Reply : HCI_CMD_Link_Key_Request_Negative_Reply);
                packetState = hciCmdPacketAddU8(packetState, mac[0]);
                packetState = hciCmdPacketAddU8(packetState, mac[1]);
                packetState = hciCmdPacketAddU8(packetState, mac[2]);
                packetState = hciCmdPacketAddU8(packetState, mac[3]);
                packetState = hciCmdPacketAddU8(packetState, mac[4]);
                packetState = hciCmdPacketAddU8(packetState, mac[5]);

                SIOPrintString("Link key = ");
                if(i){ //link key given to us
                    for(j = 0; j < 16; j++)
                    {
                        SIOPutHex(buf[j]);
                        SIOPutChar(' ');
                        packetState = hciCmdPacketAddU8(packetState, buf[j]);
                    }
                }
                SIOPrintString("\r\n");
                hciCmdPacketFinish(packetState);
                btTxCmdPacket();
            }
            //Usually end of a sucessful pairing
            else if(e->eventCode == HCI_EVT_Link_Key_Notification_Event){
                SIOPrintString("HCI Link key not \r\n");
                for(i = 0; i < sizeof(mac); i++)
                {
                    mac[i] = e->params[i];
                }
                for(i = 0; i < 16; i++) 
                {
                    buf[i] = e->params[i + sizeof(mac)];
                }

                cbks.BtLinkKeyCreatedF(cbks.userData, mac, buf);
            }

        //If support simple pairing...not sure if its good enough
        #if SUPORT_SSP //this was done last minute, but should work :) -DG

            else if(e->eventCode == HCI_EVT_IO_Capability_Request_Event){
                SIOPrintString("HCI SPP io cap \r\n");
                for(i = 0; i < sizeof(mac); i++) mac[i] = e->params[i];

                packetState = hciCmdPacketStart(HCI_OGF_Link_Control, HCI_CMD_IO_Capability_Request_Reply);
                packetState = hciCmdPacketAddU8(packetState, mac[0]);
                packetState = hciCmdPacketAddU8(packetState, mac[1]);
                packetState = hciCmdPacketAddU8(packetState, mac[2]);
                packetState = hciCmdPacketAddU8(packetState, mac[3]);
                packetState = hciCmdPacketAddU8(packetState, mac[4]);
                packetState = hciCmdPacketAddU8(packetState, mac[5]);

                //TODO Review the capabilities parameters
                packetState = hciCmdPacketAddU8(packetState, 0x01); //we claim to be display-only - it works for us
                packetState = hciCmdPacketAddU8(packetState, 0x00); //we do not support OOB
                packetState = hciCmdPacketAddU8(packetState, 0x02); //we don't care about MITM and like Dedicated Bonding
                hciCmdPacketFinish(packetState);
                btTxCmdPacket();
            }

            else if(e->eventCode == HCI_EVT_User_Passkey_Request_Event)
            {
                SIOPrintString("HCI SPP Passkey \r\n");
                Nop();
            }
            
            else if(e->eventCode == HCI_EVT_User_Confirmation_Request_Event){

                SIOPrintString("HCI SPP Confirmation \r\n");
                for(i = 0; i < sizeof(mac); i++) mac[i] = e->params[i];
                uint32_t val = 0;

                for(i = 0; i < 4; i++) val = (val << 8) | e->params[sizeof(mac) + 3 - i];

                //we are disaply-only so accept it unconditionally
                packetState = hciCmdPacketStart(HCI_OGF_Link_Control, HCI_CMD_User_Confirmation_Request_Reply);
                packetState = hciCmdPacketAddU8(packetState, mac[0]);
                packetState = hciCmdPacketAddU8(packetState, mac[1]);
                packetState = hciCmdPacketAddU8(packetState, mac[2]);
                packetState = hciCmdPacketAddU8(packetState, mac[3]);
                packetState = hciCmdPacketAddU8(packetState, mac[4]);
                packetState = hciCmdPacketAddU8(packetState, mac[5]);
                hciCmdPacketFinish(packetState);
                btTxCmdPacket();

                cbks.BtSspShow(cbks.userData, mac, val);
            }
            else if(e->eventCode == HCI_EVT_Simple_Pairing_Complete_Event){
                SIOPrintString("HCI SPP complete \r\n");
                for(i = 0; i < sizeof(mac); i++) mac[i] = e->params[i];
                uint32_t val = 0;

                for(i = 0; i < 4; i++) val = (val << 8) | e->params[sizeof(mac) + 3 - i];

                cbks.BtSspShow(cbks.userData, mac, BT_SSP_DONE_VAL);
            }

            //For compatibility....maybe for some future use
            else if(e->eventCode == HCI_EVT_Link_Super_Timeout_Changed)
            {
                
            }
            else if(e->eventCode == HCI_EVT_IO_Capability_Response_Event)
            {
                
            }
            //Command complete event. Call the state machine for initialisation
            else if(e->eventCode == HCI_EVT_Command_Complete_Event)
            {
                SIOPrintString("HCI cmd complete \r\n");
                cmd_event_state(e);
            }

        #endif
            // For compatibility only
            else{
               // btEnqueuePacket(UART_PKT_TYP_EVT);
            }

            }
            return TRUE;

        //ACL data comming
        case EVENT_BLUETOOTH_RX2_DONE:
            if(NULL != data)
            {
              SIOPrintString("HCI ACL received \r\n");
              cbks.BtAclDataRxF(cbks.userData, acl->info & 0x0FFF, ((acl->info >> 12) & 3) == 2, acl->info >> 14, acl->data, acl->totalDataLen);
            }
            return TRUE;

        case EVENT_VBUS_REQUEST_POWER:
            // We'll let anything attach.
            return TRUE;

        case EVENT_VBUS_RELEASE_POWER:
            // We aren't keeping track of power.
            return TRUE;

        case EVENT_HUB_ATTACH:
            SIOPrintString("%s:%d ERROR: HUB devices not supported.\n", __FILE__, __LINE__);
            return TRUE;
            break;

        case EVENT_UNSUPPORTED_DEVICE:
            SIOPrintString("%s:%d ERROR: Unsupported device.\n", __FILE__, __LINE__);
            return TRUE;
            break;

        case EVENT_CANNOT_ENUMERATE:
            SIOPrintString("%s:%d ERROR: Cannot enumerate device.\n", __FILE__, __LINE__);
            return TRUE;
            break;

        case EVENT_CLIENT_INIT_ERROR:
            SIOPrintString("%s:%d ERROR: Client init error.\n", __FILE__, __LINE__);
            return TRUE;
            break;

        case EVENT_OUT_OF_MEMORY:
            SIOPrintString("%s:%d ERROR: Out of heap memory.\n", __FILE__, __LINE__);
            return TRUE;
            break;

        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
            SIOPrintString("%s:%d ERROR: Unspecified error.\n", __FILE__, __LINE__);
            return TRUE;
            break;

        case EVENT_SUSPEND:
        case EVENT_DETACH:
        case EVENT_RESUME:
        case EVENT_BUS_ERROR:
            return TRUE;
            break;

        default:
            break;
    }

    return FALSE;
}



static char btTryRxEventPacket(uint8_t wantedType){
/*
    uint8_t i, j;

    for(i = 0; i < PACKET_RX_BACKLOG_SZ; i++){

        if(backlog[i] && backlog[i][0] == UART_PKT_TYP_EVT && (!wantedType || backlog[i][1] == wantedType)){

        }
    }
    return 0;
 */
}

static void btRxEventPacket(uint8_t wantedType){

    //while(!btTryRxEventPacket(wantedType)); //coopYield();
}

void btReset_hci()
{
    uint8_t* packetState;

    SIOPrintString("Bt Reset\n");
    //Command RESET
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Reset);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btGetBufferSize()
{
 uint8_t* packetState;

 //get buffer size
 packetState = hciCmdPacketStart(HCI_OGF_Informational, HCI_CMD_Read_Buffer_Size);
 hciCmdPacketFinish(packetState);
 btTxCmdPacket();
}


void setSimplePassCode(uint8_t aEnable)
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Simple_Pairing_Mode);
    packetState = hciCmdPacketAddU8(packetState, aEnable); //enable it
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btReadLocalSupportedFeature()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Informational, HCI_CMD_Read_Local_Supported_Features);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btReadLocalVersionInfo()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Informational, HCI_CMD_Read_Local_Version_Information);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btReadDeviceClass()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Read_Class_Of_Device);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btReadLocalName()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Read_Local_Name);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btDeleteStoredKeys()
{
    uint8_t* packetState;

    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Delete_Stored_Link_Key);
    //On balance une adresse mac nulle
    packetState = hciCmdPacketAddU8(packetState,0) ;
    packetState = hciCmdPacketAddU8(packetState,0 );
    packetState = hciCmdPacketAddU8(packetState,0 );
    packetState = hciCmdPacketAddU8(packetState,0 );
    packetState = hciCmdPacketAddU8(packetState,0 );
    packetState = hciCmdPacketAddU8(packetState,0 );
    // Tout supprimer
    packetState = hciCmdPacketAddU8(packetState,0x01);

    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btWriteInquiryMode()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Inquiry_Mode);
    packetState = hciCmdPacketAddU8(packetState,2) ;
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btWriteDefaultLinkPolicySettings()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Policy, HCI_CMD_Write_Def_Link_Policy_Settings);
    packetState = hciCmdPacketAddU8(packetState,0x00) ;
    packetState = hciCmdPacketAddU8(packetState,0x05) ;
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btSetEventMask()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Set_Event_Mask);
    packetState = hciCmdPacketAddU8(packetState,0xff) ;
    packetState = hciCmdPacketAddU8(packetState,0xff) ;
    packetState = hciCmdPacketAddU8(packetState,0xfb) ;
    packetState = hciCmdPacketAddU8(packetState,0xff) ;
    packetState = hciCmdPacketAddU8(packetState,0x07) ;
    packetState = hciCmdPacketAddU8(packetState,0xf8) ;
    packetState = hciCmdPacketAddU8(packetState,0xbf) ;
    packetState = hciCmdPacketAddU8(packetState,0x3d) ;
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btWritePageTimeout(uint16_t aTimeout)
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Page_Timeout);
    packetState = hciCmdPacketAddU16(packetState,aTimeout) ;
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btWriteHostSize()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Host_Buffer_Size);
    packetState = hciCmdPacketAddU16(packetState,DATA_PACKET_LENGTH-4) ;
    packetState = hciCmdPacketAddU8(packetState,0) ;
    packetState = hciCmdPacketAddU8(packetState,1) ;
    packetState = hciCmdPacketAddU8(packetState,0) ;
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btWriteConnAcceptTimeout()
{
    uint8_t* packetState;
    
    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Connection_Accept_Timeout);
    packetState = hciCmdPacketAddU16(packetState,32000) ;
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btInit(const BtFuncs* btf){
    
    gBtDevice.isInitialized = FALSE;
    gBtDevice.isVisible = FALSE;
    sprintf(gBtDevice.localName,BT_DEVICE_NAME);
     SIOPrintString("***** HCI BT Init *****  \r\n");
    cbks = *btf;
}

void btGetStatus(HCI_Event* e)
{
    WORD aCmd = 0x0000 ;

    //On récupère la commande
    aCmd = ((e->params[1] & 0xFF)| e->params[2] << 8);

    switch(aCmd)
    {
        default:
            ;
    }
}

void cmd_event_state(HCI_Event* e)
{
    WORD aCmd = 0x0000 ;
    uint16_t aclLen, aclNum, scoNum;
    uint8_t scoLen;
    uint8_t i = 0;

    //On récupère la commande
    aCmd = ((e->params[1] & 0xFF)| e->params[2] << 8);

    switch(aCmd)
    {
        // Si on recoit l'attestation d'un reset
        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Reset):
                 SIOPrintString("BT : RESET OK \r\n");
                //On veut lire les capacité supoortée
                btReadLocalSupportedFeature();
            break;


        //On a recu les info que l'on voulait
        case HCI_OPCODE(HCI_OGF_Informational, HCI_CMD_Read_Local_Supported_Features) :
            SIOPrintString("BT : RD LOCAL OK \r\n");
            //On récupère le status
            if(e->params[3] == 0)
            {
            //On récupère les infos
            }
            else
            {

            }
            btReadLocalVersionInfo();

            break;

         //On a recu les info que l'on voulait
        case HCI_OPCODE(HCI_OGF_Informational, HCI_CMD_Read_Local_Version_Information) :
            SIOPrintString("BT : RD VERS OK \r\n");
            //On récupère le status
            if(e->params[3] == 0)
            {
            //On récupère les infos
            }
            else
            {
            }
           btGetBufferSize();

            break;

        case HCI_OPCODE(HCI_OGF_Informational, HCI_CMD_Read_Buffer_Size) :
            //On récupère les tailles
            aclLen = (((uint16_t)e->params[5]) << 8) | e->params[4];
            scoLen = e->params[6];
            aclNum = (((uint16_t)e->params[8]) << 8) | e->params[7];
            scoNum = (((uint16_t)e->params[10]) << 8) | e->params[9];

            SIOPrintString("BT : RD BUFFER OK ACL Len : ");
            //Get the maximum of size we can send in one time
            SIOPutDec(aclLen);
            SIOPrintString(" ACL num : ");
            SIOPutDec(aclNum);
            SIOPrintString("\r\n");
            gAclPacketsCanSend = aclNum;

           // btWriteHostSize();
            btLocalMac(NULL);
            break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Host_Buffer_Size):
            //On veut l'addresse MAC
            btLocalMac(NULL);
            break;

              // On récupère l'adresse mac
       case  HCI_OPCODE(HCI_OGF_Informational, HCI_CMD_Read_BD_ADDR) :
               for(i = 0; i < 6; i++) {
                   gBtDevice.mac[i] = e->params[4 + i];
               }
               SIOPrintString("BT MAC: %02X:%02X:%02X:%02X:%02X:%02X\n", gBtDevice.mac[5], gBtDevice.mac[4], gBtDevice.mac[3], gBtDevice.mac[2], gBtDevice.mac[1], gBtDevice.mac[0]);

               //On lit la classe de notre dongle
               btReadDeviceClass();
               break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Read_Class_Of_Device):

            //On va lire le nom en cours
            btReadLocalName();
            break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Read_Local_Name):

            //On écrit le timeout
            btWriteConnAcceptTimeout();
           
            break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Connection_Accept_Timeout):
             //On supprime les clés
            btDeleteStoredKeys();
            break;


        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Delete_Stored_Link_Key):
          
            btSetEventMask();
            break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Set_Event_Mask):
               // On autorise le mot de passe simple
            if(SUPORT_SSP){
                setSimplePassCode(0);
            }
            break;

             // On autorise le mot de passe simple
        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Simple_Pairing_Mode):

            btWriteInquiryMode();
            break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Inquiry_Mode):
            //Sniff et switch mode
            btWriteDefaultLinkPolicySettings();

            break;

        case HCI_OPCODE(HCI_OGF_Policy, HCI_CMD_Write_Def_Link_Policy_Settings):
            btWritePageTimeout(10000);
            break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Page_Timeout):
             // On configure le nom de la sation
            btSetLocalName(gBtDevice.localName);
            break;
       
        case  HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Change_Local_Name):

            // On écrit la classe de périphérque
            //btSetDeviceClass(0x6e0100);
            if(gBtDevice.isInitialized == FALSE)
            {
                btSetDeviceClass(0x040280);
            }
            break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Class_Of_Device) :

            // On ne le voit pas
            pageState = 0;

            // On rend   le périphérique visible
            btDiscoverableConnectable();
            break;

        case HCI_OPCODE(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Scan_Enable):

            //pageState = 0;
            if(gBtDevice.isInitialized == FALSE)
            {
                //Une erreur est survenue
                if(e->params[3] == 0)
                {
                    gBtDevice.isVisible = TRUE;
                }
                else
                {
                    gBtDevice.isVisible = FALSE;
                }
              }
            // On a terminé l'init
            gBtDevice.isInitialized = TRUE;

            break;

        case HCI_OPCODE(HCI_OGF_Link_Control,HCI_CMD_IO_Capability_Request_Reply):
            break;

        case HCI_OPCODE(HCI_OGF_Link_Control,HCI_CMD_User_Confirmation_Request_Reply):
            break;
        default :
            ;
    }
}


void btDeinit(void){

    //int i;
    //for(i = 0; i < PACKET_RX_BACKLOG_SZ; i++) if(backlog[i]) free(backlog[i]);
}

void btLocalMac(uint8_t* buf){
    uint8_t* packetState;

    packetState = hciCmdPacketStart(HCI_OGF_Informational, HCI_CMD_Read_BD_ADDR);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btSetLocalName(const char* name){

    HCI_Cmd* cmd = (HCI_Cmd*)packetStoreCMD;
    uint8_t* packetState;

    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Change_Local_Name);
    while(name && *name) 
    {
        packetState = hciCmdPacketAddU8(packetState, *name++);
    }
    packetState = hciCmdPacketAddU8(packetState, 0);
    hciCmdPacketFinish(packetState);
    if(cmd->totalParamLen > 248) 
    {
        return 0;	//too long
    }
    cmd->totalParamLen = 248;
    btTxCmdPacket();
}


/*Function not used*/
void btScan(void){

}
/*Function not used*/
void btGetRemoteName(const uint8_t* mac, uint8_t PSRM, uint8_t PSM, uint16_t co, char* nameBuf){

/*    HCI_Event* evt = (HCI_Event*)packetEVT;
    uint8_t* packetState;
    int i = 0;

    packetState = hciCmdPacketStart(HCI_OGF_Link_Control, HCI_CMD_Remote_Name_Request);
    packetState = hciCmdPacketAddU8(packetState, mac[0]);
    packetState = hciCmdPacketAddU8(packetState, mac[1]);
    packetState = hciCmdPacketAddU8(packetState, mac[2]);
    packetState = hciCmdPacketAddU8(packetState, mac[3]);
    packetState = hciCmdPacketAddU8(packetState, mac[4]);
    packetState = hciCmdPacketAddU8(packetState, mac[5]);
    packetState = hciCmdPacketAddU8(packetState, PSRM);
    packetState = hciCmdPacketAddU8(packetState, PSM);
    packetState = hciCmdPacketAddU16(packetState, co);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();

    btRxEventPacket(HCI_EVT_Remote_Name_Request_Complete_Event);

    if(evt->params[0] == 0){

        while(i < 248 && evt->params[7 + i]){
            nameBuf[i] = evt->params[7 + i];
            i++;
        }
        nameBuf[i] = 0;
        return 1;
    }
    else return 0;
 */
}

static void btDiscoverableConnectable(void){

    HCI_Event* evt = (HCI_Event*)packetEVT;
    uint8_t* packetState;

    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Scan_Enable);
    packetState = hciCmdPacketAddU8(packetState, pageState);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}

void btDiscoverable(char on){

    uint8_t nv = (pageState &~ PAGE_STATE_INQUIRY) | (on ? PAGE_STATE_INQUIRY : 0);
    pageState = nv;

    btDiscoverableConnectable();
}

void btConnectable(char on){

    uint8_t nv = (pageState &~ PAGE_STATE_PAGE) | (on ? PAGE_STATE_PAGE : 0);
    pageState = nv;

    btDiscoverableConnectable();
}

void btSetDeviceClass(uint32_t cls){
    uint8_t* packetState;

    packetState = hciCmdPacketStart(HCI_OGF_Controller_and_Baseband, HCI_CMD_Write_Class_Of_Device);
    packetState = hciCmdPacketAddU24(packetState, cls);
    hciCmdPacketFinish(packetState);
    btTxCmdPacket();
}



