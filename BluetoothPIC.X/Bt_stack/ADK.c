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


#include "ADK.h"
#include "BT.h"
#include "HCI.h"
#include "btL2CAP.h"
#include "btRFCOMM.h"
#include "btSDP.h"
#include "sgBuf.h"
#include "../mainApp/HardwareProfile.h"


static adkBtConnectionRequestF bt_crF = 0;
static adkBtLinkKeyRequestF bt_krF = 0;
static adkBtLinkKeyCreatedF bt_kcF = 0;
static adkBtPinRequestF bt_prF = 0;
static adkBtDiscoveryResultF bt_drF = 0;
static adkBtSspDisplayF bt_pdF = 0;

static char btLinkKeyRequest(void* userData, const uint8_t* mac, uint8_t* buf){

    if(bt_krF) return bt_krF(mac, buf);

    SIOPrintString("BT Link key request from %02x:%02x:%02x:%02x:%02x:%02x -> denied due to lack of handler", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);
    return 0;
}
static uint8_t btPinRequestF(void* userData, const uint8_t* mac, uint8_t* buf){	//fill buff with PIN code, return num bytes used (16 max) return 0 to decline

    if(bt_prF) return bt_prF(mac, buf);

    SIOPrintString("BT PIN request from %02x:%02x:%02x:%02x:%02x:%02x -> '0000' due to lack of handler", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]);

    buf[0] = buf[1] = buf[2] = buf[3] = '0';
    return 4;
}

static void btLinkKeyCreated(void* userData, const uint8_t* mac, const uint8_t* buf){

    if(bt_kcF) bt_kcF(mac, buf);
}

static char btConnReqF(void* userData, const uint8_t* mac, uint32_t devClass, uint8_t linkType){	//return 1 to accept

    if(bt_crF) return bt_crF(mac, devClass, linkType);

    SIOPrintString("BT connection request: %s connection from %02x:%02x:%02x:%02x:%02x:%02x (class %06X) -> accepted due to lack of handler\n", linkType ? "ACL" : "SCO", mac[5], mac[4], mac[3], mac[2], mac[1], mac[0], devClass);
    return 1;
}

static void btConnStartF(void* userData, uint16_t conn, const uint8_t* mac, uint8_t linkType, uint8_t encrMode){

    SIOPrintString("BT %s connection up with handle %d to %02x:%02x:%02x:%02x:%02x:%02x encryption type %d\n",
    linkType ? "ACL" : "SCO", conn, mac[5], mac[4], mac[3], mac[2], mac[1], mac[0], encrMode);
    l2capAclLinkUp(conn);
}

static void btConnEndF(void* userData, uint16_t conn, uint8_t reason){

    SIOPrintString("BT connection with handle ");
    SIOPutDec(conn);
    SIOPrintString(" down for reason ");
    SIOPutDec(reason);
    SIOPrintString("\r\n");

    l2capAclLinkDown(conn);
}

static void btAclDataRxF(void* userData, uint16_t conn, char first, uint8_t bcastType, const uint8_t* data, uint16_t sz){

    l2capAclLinkDataRx(conn, first, data, sz);
}

static void btSspShowF(void* userData, const uint8_t* mac, uint32_t val){

    if(val == BT_SSP_DONE_VAL) val = ADK_BT_SSP_DONE_VAL;

    if(bt_pdF) bt_pdF(mac, val);
}

static char btVerboseScanCbkF(void* userData, BtDiscoveryResult* dr){

    if(bt_drF) return bt_drF(dr->mac, dr->PSRM, dr->PSPM, dr->PSM, dr->co, dr->dc);

    SIOPrintString("BT: no callback for scan makes the scan useless, no?");
    return 0;
}

void adkInit(void){

    //Create the BT functions structure
    static const BtFuncs myBtFuncs = {0, btVerboseScanCbkF, btConnReqF, btConnStartF, btConnEndF, btPinRequestF, btLinkKeyRequest, btLinkKeyCreated, btAclDataRxF, btSspShowF};

    //Bluetooth initialisation
    btInit(&myBtFuncs);

    //Start the listener service
    btSdpRegisterL2capService();     //SDP daemon
    btRfcommRegisterL2capService();  //RFCOMM framework

    //Configuration is Event controlled
    // Initiate the configuration processe by reset the dongle
    btReset_hci();

}

void btEnable(adkBtConnectionRequestF crF, adkBtLinkKeyRequestF krF, adkBtLinkKeyCreatedF kcF, adkBtPinRequestF prF, adkBtDiscoveryResultF drF){

    bt_crF = crF;
    bt_krF = krF;
    bt_kcF = kcF;
    bt_prF = prF;
    bt_drF = drF;
}

void btSetSspCallback(adkBtSspDisplayF pdF){

    bt_pdF = pdF;
}

void btSetLocalName_ADK(const char* name){

    btSetLocalName(name);
}

void btGetRemoteName_ADK(const uint8_t* mac, uint8_t PSRM, uint8_t PSM, uint16_t co, char* nameBuf){

    btGetRemoteName(mac, PSRM, PSM, co, nameBuf);
}

void btScan_ADK(void){

    btScan();
}

void btDiscoverable_ADK(char on){

    btDiscoverable(on);
}

void btConnectable_ADK(char on){

    btConnectable(on);
}

void btSetDeviceClass_ADK(uint32_t cls){

    btSetDeviceClass(cls);
}

void l2capServiceTx_ADK(uint16_t conn, uint16_t remChan, const uint8_t* data, uint32_t size){ //send data over L2CAP

    sg_buf* buf = sg_alloc();

    if(!buf) return;
    if(sg_add_back(buf, data, size, SG_FLAG_MAKE_A_COPY)) l2capServiceTx(conn, remChan, buf);
    else sg_free(buf);
}

void l2capServiceCloseConn_ADK(uint16_t conn, uint16_t chan){

    l2capServiceCloseConn(conn, chan);
}

char l2capServiceRegister_ADK(uint16_t PSM, const L2capService* svcData){

    return l2capServiceRegister(PSM, svcData);
}

char l2capServiceUnregister_ADK(uint16_t PSM){

    return l2capServiceUnregister(PSM);
}

void btSdpServiceDescriptorAdd_ADK(const uint8_t* descriptor, uint16_t descrLen){

    btSdpServiceDescriptorAdd(descriptor, descrLen);
}

void btSdpServiceDescriptorDel_ADK(const uint8_t* descriptor){

    btSdpServiceDescriptorDel(descriptor);
}

void btRfcommRegisterPort_ADK(uint8_t dlci, BtRfcommPortOpenF oF, BtRfcommPortCloseF cF, BtRfcommPortRxF rF){

    btRfcommRegisterPort(dlci, oF, cF, rF);
}

void btRfcommPortTx_ADK(void* port, uint8_t dlci, const uint8_t* data, uint16_t size){

    btRfcommPortTx(port, dlci, data, size);
}

uint8_t btRfcommReserveDlci_ADK(uint8_t preference){

    return btRfcommReserveDlci(preference);
}

void btRfcommReleaseDlci_ADK(uint8_t dlci){

    btRfcommReleaseDlci(dlci);
}
