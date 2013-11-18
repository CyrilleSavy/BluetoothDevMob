#include <stdlib.h>
#include <stdint.h>
#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "../bluetoothUSB/usb_host_bluetooth.h"
#include "../MPLABX_prj/ADK.h"
#include "../MPLABX_prj/BT.h"


/*
 *
 * FONCTIONS STATIQUE POUR BT
 *
 */


// *****************************************************************************
// *****************************************************************************
// Configuration Bits
// *****************************************************************************
// *****************************************************************************
#if defined __C30__ || defined __XC16__
    #if defined(__PIC24FJ256GB110__)
        _CONFIG2(FNOSC_PRIPLL & POSCMOD_HS & PLL_96MHZ_ON & PLLDIV_DIV2) // Primary HS OSC with PLL, USBPLL /2
        _CONFIG1(JTAGEN_OFF & FWDTEN_OFF & ICS_PGx2)   // JTAG off, watchdog timer off
#endif
#elif defined( __PIC32MX__ )

    #pragma config UPLLEN   = ON            // USB PLL Enabled
    #pragma config FPLLMUL  = MUL_15        // PLL Multiplier
    #pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
    #pragma config FPLLIDIV = DIV_2         // PLL Input Divider
    #pragma config FPLLODIV = DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config FWDTEN   = OFF           // Watchdog Timer
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = OFF           // Secondary Oscillator Enable (KLO was off)
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection
    #pragma config CP       = OFF           // Code Protect
    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = ON            // Background Debugger Enable

#else

  #error Cannot define configuration bits.

#endif

// Bluetoot SPP normalized UUID
#define BT_SPP_UUID	0x00, 0x00, 0x11, 0x01, 0x00, 0x00, 0x10, 0x00, 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB
#define SW_NUM   4
#define LED_NUM  8

/* Types*/
// APP settings
typedef struct AdkSettings{
  char btName[249]; //null terminated
  char btPIN[17];  //null terminated
}AdkSettings;


typedef struct
{
    BOOL gSwTab[SW_NUM];
    BOOL gLedTab[LED_NUM];
    uint16_t gTrimmVal ;
    char *gLCDStr;
}BluetoothAppDeviceCtrl;


/* Variables */

// Main settings
AdkSettings settings;
BluetoothAppDeviceCtrl hardDevices;
// Pointer to pin code
const char* btPIN = 0;
//Simple serial pairing done value
volatile static uint32_t btSSP = ADK_BT_SSP_DONE_VAL;
//Bluetoth device
extern BtDevice gBtDevice;






// Apply defaults settings
void readSettings(){
   //apply defaults
   strcpy(settings.btName, "CyrilleIsBest!");
   strcpy(settings.btPIN, "1234");
}

/*INITIALIZES THE SYSTEM*/
void SysInit(){
    // Set LED Pins to Outputs
    InitAllLEDs();
    InitAllSwitches();
    mInitPOT();

    // Init UART
    //DEBUG_Init(0);
    SIOInit();
}




//SSP callback function
void adkBtSspF(const uint8_t* mac, uint32_t val){
  btSSP = val;
  SIOPrintString("ssp with val ");
  SIOPutDec(val);
  SIOPrintString("\r\n");
}

/****************************************************************************
  Function:
    BYTE ReadPOT(void)

  Summary:
    Reads the pot value and returns the percentage of full scale (0-100)

  Description:
    Reads the pot value and returns the percentage of full scale (0-100)

  Precondition:
    A/D is initialized properly

  Parameters:
    None

  Return Values:
    None

  Remarks:
    None
  ***************************************************************************/
static BYTE ReadPOT(void)
{
            WORD_VAL w;
            DWORD temp;

            AD1CHS = 0x9;           //MUXA uses AN9

            // Get an ADC sample
            AD1CON1bits.SAMP = 1;           //Start sampling
            for(w.Val=0;w.Val<1000;w.Val++){Nop();} //Sample delay, conversion start automatically
            AD1CON1bits.SAMP = 0;           //Start sampling
            for(w.Val=0;w.Val<1000;w.Val++){Nop();} //Sample delay, conversion start automatically
            while(!AD1CON1bits.DONE);       //Wait for conversion to complete

            temp = (DWORD)ADC1BUF0;
            temp = temp * 100;
            temp = temp/1023;


    return (BYTE)temp;
}


int main ( void )
{
    unsigned int last_sw_state = 1;
    unsigned int last_sw2_state = 1;
    unsigned int i = 0 ;
    //Initialise the system
    SysInit();

    //Initialise the USB Host
    if ( USBHostInit(0) == TRUE )
    {
        SIOPrintString( "USB initialized.\n" );
    }
    else
    {
        SIOPrintString( "Unable to initialise the USB: HALT\n" );
    }

    DelayMs(100); 
    SIOPrintString( "USB-Bluetooth Dongle Demo v1\n" );


    //Wait on usb dongle initialization
    while(gBtDevice.isInitialized ==  FALSE)
    {
         USBHostTasks();
         USBScan_Google();
    }

    //Initialize hardware devices
    hardDevices.gLCDStr = NULL;
    for(i=0;i<LED_NUM;i++)
    {
        hardDevices.gLedTab[i]==FALSE;
    }
    for(i=0;i<SW_NUM;i++)
    {
        hardDevices.gSwTab[i]==FALSE;
    }
    hardDevices.gTrimmVal = 0 ;

    
    //Start bluetooth
    btStart();
    //Read default settings
    readSettings();

    //Get pin code string
    btPIN = settings.btPIN;

    //Set new name
    btSetLocalName(settings.btName);
    //Set Bluetooth discoverable
    btDiscoverable(1);
    //Set bluetooth connactable
    btConnectable(1);

    //Set SSP callback
    btSetSspCallback(adkBtSspF);


    //Main loop
    while (1)
    {

        // Get the switchs
        hardDevices.gSwTab[0]=Switch1Pressed();
        hardDevices.gSwTab[1]=Switch2Pressed();
        hardDevices.gSwTab[2]=Switch3Pressed();
        hardDevices.gSwTab[3]=Switch4Pressed();

        i=0;
        //Write the LEDS
        for(i=0;i<LED_NUM;i++)
        {
            BOOL aVal = hardDevices.gLedTab[i] ;
            switch(i)
            {
                case 0 :
                    mLED_3 = aVal;
                    break;
                case 1 :
                    mLED_4 = aVal;
                    break;
                case 2 :
                     mLED_5 = aVal;
                    break;
                case 3 :
                     mLED_6 = aVal;
                    break;
                case 4 :
                     mLED_7 = aVal;
                    break;
                case 5 :
                     mLED_8 = aVal;
                    break;
                case 6 :
                     mLED_9 = aVal;
                    break;
                case 7 :
                     mLED_10 = aVal;
                    break;
            }
        }

        //Read pot
        hardDevices.gTrimmVal = ReadPOT();

        //Later write the LCD
       

        //Maintain the USB status
        USBHostTasks();

        //Maintain the application
        USBScan_Google();
    }

}

/**
 *
 * Bluetooth Interface Functions and variables
 *
 *
 */

//commands
#define MAX_PACKET_SZ                       249  //256b payload + header
#define MAX_CMD_PARAM                       5

#define LED_CMD                             1
#define SW_CMD                              2


/**
 * Communcation protocol implementation
 * @param cmd
 * @param dataIn
 * @param sz
 * @param fromBT
 * @param reply
 * @param maxReplySz
 * @return
 */
static uint16_t commandAnalyzer(char* reply,char* cmdBuf){  //returns num bytes to reply with (or 0 for no reply)

    return 0 ;
}





// Reception buffer
static uint8_t cmdBuf[MAX_PACKET_SZ];
static uint32_t bufPos = 0;


/**
 * Open RFCOMM Channel
 * @param port
 * @param dlci
 */
static void btAdkPortOpen(void* port, uint8_t dlci){

    bufPos = 0;
    SIOPrintString("RFCOMM Port Opened");
}

/**
 * RFCOMM Channel closed
 * @param port
 * @param dlci
 */
static void btAdkPortClose(void* port, uint8_t dlci){

    //nothing here [yet?]
    SIOPrintString("RFCOMM Port Closed");
}


/**
 * RFCOMM when we receive a packet
 * @param port
 * @param dlci
 * @param data
 * @param sz
 */
static void btAdkPortRx(void* port, uint8_t dlci, const uint8_t* data, uint16_t sz){

      uint8_t reply[MAX_PACKET_SZ];
      uint8_t aTemp[5] ;
      uint8_t i = 0 ;
      bufPos = 0;

      //copy to buffer as much as we can
      while(bufPos < MAX_PACKET_SZ && sz){
        cmdBuf[bufPos++] = *data++;
        cmdBuf[bufPos] = 0x00;
        sz--;
      }

      //Test the first byte
      if(cmdBuf[0] != '$')
      {
          //Do nothing
          return;
      }
      //get the command byte
      switch(cmdBuf[1])
      {
          // Led write
          case '1' :
              hardDevices.gLedTab[cmdBuf[3]-48] = cmdBuf[5]-48;
              break;
          //Switch read
          case '2':
              sprintf(reply,"$2_");
              for(i=0;i<SW_NUM;i++)
              {
                sprintf(aTemp,"%1d_",hardDevices.gSwTab[i]);
                strcat(reply,aTemp);
              }
              strcat(reply,"\r\n");
              btRfcommPortTx(port, dlci, reply, 13);

              break;
          //Pot read
          case '3' :
              sprintf(reply,"$3_");
              sprintf(aTemp,"%03d_",hardDevices.gTrimmVal);
              strcat(reply,aTemp);
              strcat(reply,"\r\n");
              btRfcommPortTx(port, dlci, reply, 9);
              break;
          default :
              return ;
      }

      

   
}


/**
 *
 * BLUETOOTH SUPPORT FUNCTIONS
 *
 */

static const uint8_t maxPairedDevices = 4;
static uint8_t numPairedDevices = 0;
static uint8_t savedMac[4][BLUETOOTH_MAC_SIZE];
static uint8_t savedKey[4][BLUETOOTH_LINK_KEY_SIZE];

static char adkBtConnectionRequest(const uint8_t* mac, uint32_t devClass, uint8_t linkType){	//return 1 to accept
    SIOPrintString("BT : Connexion request\r\n");
    return 1;
}

static char adkBtLinkKeyRequest(const uint8_t* mac, uint8_t* buf){ //link key create

  uint8_t i, j;
  SIOPrintString("BT : Link key request\r\n");
  for(i = 0; i < numPairedDevices; i++){

    for(j = 0; j < BLUETOOTH_MAC_SIZE && savedMac[i][j] == mac[j]; j++);
    if(j == BLUETOOTH_MAC_SIZE){ //match
        SIOPrintString("BT : MAC match\r\n Saved key = ");
        for(j = 0; j < BLUETOOTH_LINK_KEY_SIZE; j++){
          SIOPutHex(savedKey[i][j]);
          SIOPutChar(' ');
          buf[j] = savedKey[i][j];
        }
        SIOPrintString("\r\n");

        return 1;
        //UGLY CODE : Do like we didn't connect early
        //return 0;
    }
  }
  return 0;
}

static void adkBtLinkKeyCreated(const uint8_t* mac, const uint8_t* buf){ 	//link key was just created, save it if you want it later

   uint8_t j;

   for(j = 0; j < BLUETOOTH_LINK_KEY_SIZE; j++){
   }
   SIOPrintString("BT : LinkKey Created\r\n");
   if(numPairedDevices < maxPairedDevices){
      SIOPrintString("BT : LinkKey : ");
      for(j = 0; j < BLUETOOTH_LINK_KEY_SIZE; j++)
      {
          SIOPutHex(buf[j]);
          SIOPutChar(' ');
          savedKey[numPairedDevices][j] = buf[j];
      }
      SIOPrintString("\r\nBT : MAC remote : ");
      for(j = 0; j < BLUETOOTH_MAC_SIZE; j++) 
      {
          SIOPutHex(mac[j]);
          SIOPutChar(' ');
          savedMac[numPairedDevices][j] = mac[j];
      }
      numPairedDevices++;
      SIOPrintString("\r\n");
   }
   else{
   }
}

static char adkBtPinRequest(const uint8_t* mac, uint8_t* buf){		//fill buff with PIN code, return num bytes used (16 max) return 0 to decline

   uint8_t v, i = 0;
   SIOPrintString("BT : PIN request");
   if(btPIN){
     for(i = 0; btPIN[i]; i++) 
     {
         buf[i] = btPIN[i];
     }
     return i;
   }
   return 0;
}


//APP descriptor
#define MAGIX	0xFA
static uint8_t sdpDescrSPP[] =
{
        //service class ID list
        SDP_ITEM_DESC(SDP_TYPE_UINT, SDP_SZ_2), 0x00, 0x01, SDP_ITEM_DESC(SDP_TYPE_ARRAY, SDP_SZ_u8), 0x11,
            SDP_ITEM_DESC(SDP_TYPE_UUID, SDP_SZ_16), BT_SPP_UUID,
        //ServiceId
        SDP_ITEM_DESC(SDP_TYPE_UINT, SDP_SZ_2), 0x00, 0x03, SDP_ITEM_DESC(SDP_TYPE_UUID, SDP_SZ_2), 0x11, 0x01,
        //ProtocolDescriptorList
        SDP_ITEM_DESC(SDP_TYPE_UINT, SDP_SZ_2), 0x00, 0x04, SDP_ITEM_DESC(SDP_TYPE_ARRAY, SDP_SZ_u8), 15,
            SDP_ITEM_DESC(SDP_TYPE_ARRAY, SDP_SZ_u8), 6,
                SDP_ITEM_DESC(SDP_TYPE_UUID, SDP_SZ_2), 0x01, 0x00, // L2CAP
                SDP_ITEM_DESC(SDP_TYPE_UINT, SDP_SZ_2), 0x01, 0x00, // L2CAP PSM
            SDP_ITEM_DESC(SDP_TYPE_ARRAY, SDP_SZ_u8), 0x05,
                SDP_ITEM_DESC(SDP_TYPE_UUID, SDP_SZ_2), 0x00, 0x03, // RFCOMM
                SDP_ITEM_DESC(SDP_TYPE_UINT, SDP_SZ_1), MAGIX, // port ###
        //Name
        SDP_ITEM_DESC(SDP_TYPE_UINT, SDP_SZ_2), 0x01, 0x00, SDP_ITEM_DESC(SDP_TYPE_TEXT, SDP_SZ_u8), 0x05, 'C', 'O', 'M','1',0x00,
};


void btStart(){
    uint8_t i, dlci;
    int f;

    btEnable(adkBtConnectionRequest, adkBtLinkKeyRequest, adkBtLinkKeyCreated, adkBtPinRequest, NULL);

    dlci = btRfcommReserveDlci(RFCOMM_DLCI_PREFERENCE_NONE);//RFCOMM_DLCI_NEED_EVEN);

    if(!dlci)
    {
        SIOPrintString("BTADK: failed to allocate DLCI\n");
    }
    else{

        //change descriptor to be valid...
        for(i = 0, f = -1; i < sizeof(sdpDescrSPP); i++){

            if(sdpDescrSPP[i] == MAGIX){
                if(f == -1) f = i;
                else break;
            }
        }

        if(i != sizeof(sdpDescrSPP) || f == -1){

            SIOPrintString("BTADK: failed to find a single marker in descriptor\n");
            btRfcommReleaseDlci(dlci);
            return;
        }

        sdpDescrSPP[f] = dlci >> 1;

        SIOPrintString("BTADK has DLCI ");
        SIOPutDec(dlci);
        SIOPrintString("\r\n");

        btRfcommRegisterPort(dlci, btAdkPortOpen, btAdkPortClose, btAdkPortRx);
        btSdpServiceDescriptorAdd(sdpDescrSPP, sizeof(sdpDescrSPP));
    }
}
