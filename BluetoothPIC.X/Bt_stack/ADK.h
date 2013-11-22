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
#ifndef _ADK_H_
#define _ADK_H_

#include <stdint.h>
#include "btL2CAP.h"
#include "btSDP.h"
#include "btRFCOMM.h"

#define ADK_INTERNAL


#define NUM_LEDS  64
#define NUM_DIGITS  6
#define NUM_ICONS  8

#define DMA_CHANNEL_LEDS	0	//we use channel 0

typedef void (*adkPutcharF)(char c);

typedef char (*adkBtConnectionRequestF)(const uint8_t* mac, uint32_t devClass, uint8_t linkType);	//return 1 to accept
typedef char (*adkBtLinkKeyRequestF)(const uint8_t* mac, uint8_t* buf);		//retrieve link key, fill buffer with it, return 1. if no key -> return 0
typedef void (*adkBtLinkKeyCreatedF)(const uint8_t* mac, const uint8_t* buf); 	//link key was just created, save it if you want it later
typedef char (*adkBtPinRequestF)(const uint8_t* mac, uint8_t* buf);		//fill buff with PIN code, return num bytes used (16 max) return 0 to decline
typedef char (*adkBtDiscoveryResultF)(const uint8_t* mac, uint8_t PSRM, uint8_t PSPM, uint8_t PSM, uint16_t CO, uint32_t devClass); //return 0 to stop scan immediately
typedef void (*adkBtSspDisplayF)(const uint8_t* mac, uint32_t val);

#define ADK_BT_SSP_DONE_VAL		0x0FF00000

#define BLUETOOTH_MAC_SIZE		6	//bytes
#define BLUETOOTH_LINK_KEY_SIZE		16	//bytes
#define BLUETOOTH_MAX_PIN_SIZE		16	//bytes
#define BLUETOOTH_MAX_NAME_LEN		248	//bytes
#define ADK_UNIQUE_ID_LEN		4	//4 32-bit values

/* keep in sync with Audio.h */
#define AUDIO_NULL 0
#define AUDIO_USB 1
#define AUDIO_BT  2
#define AUDIO_ALARM 3

#define AUDIO_MAX_SOURCE 4

/*	--- structure(s) and types reference ---

typedef struct{

    uint8_t flags;

    void* (*serviceInstanceAllocate)(uint16_t conn, uint16_t chan, uint16_t remChan);
    void (*serviceInstanceFree)(void* service);

    void (*serviceRx)(void* service, const uint8_t* data, uint16_t size);

}L2capService;


typedef void (*BtRfcommPortOpenF)(void* port, uint8_t dlci);
typedef void (*BtRfcommPortCloseF)(void* port, uint8_t dlci);
typedef void (*BtRfcommPortRxF)(void* port, uint8_t dlci, const uint8_t* buf, uint16_t sz);


*/


//generic
void adkInit(void);

//BT
void btEnable(adkBtConnectionRequestF crF, adkBtLinkKeyRequestF krF, adkBtLinkKeyCreatedF kcF, adkBtPinRequestF prF, adkBtDiscoveryResultF drF);
void btSetLocalName_ADK(const char* name);
void btGetRemoteName_ADK(const uint8_t* mac, uint8_t PSRM, uint8_t PSM, uint16_t co, char* nameBuf);
void btScan_ADK(void);
void btDiscoverable_ADK(char on);
void btConnectable_ADK(char on);
void btSetDeviceClass_ADK(uint32_t cls);

//advanced BT
//ACL
void l2capServiceTx_ADK(uint16_t conn, uint16_t remChan, const uint8_t* data, uint32_t size); //send data over L2CAP
void l2capServiceCloseConn_ADK(uint16_t conn, uint16_t chan);
char l2capServiceRegister_ADK(uint16_t PSM, const L2capService* svcData);
char l2capServiceUnregister_ADK(uint16_t PSM);

//SDP
void btSdpServiceDescriptorAdd_ADK(const uint8_t* descriptor, uint16_t descrLen); //a copy will NOT be made do not include handle
void btSdpServiceDescriptorDel_ADK(const uint8_t* descriptor);
    
//RFCOMM
void btRfcommRegisterPort_ADK(uint8_t dlci, BtRfcommPortOpenF oF, BtRfcommPortCloseF cF, BtRfcommPortRxF rF);
void btRfcommPortTx_ADK(void* port, uint8_t dlci, const uint8_t* data, uint16_t size); //makes a copy of your buffer
uint8_t btRfcommReserveDlci_ADK(uint8_t preference);	//return dlci if success, zero if fail
void btRfcommReleaseDlci_ADK(uint8_t dlci);

//SSP
void btSetSspCallback(adkBtSspDisplayF pdF);



#endif


