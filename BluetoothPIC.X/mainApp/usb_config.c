/*
********************************************************************************
                                                                                
Software License Agreement                                                      
                                                                                
Copyright © 2007-2008 Microchip Technology Inc. and its licensors.  All         
rights reserved.                                                                
                                                                                
Microchip licenses to you the right to: (1) install Software on a single        
computer and use the Software with Microchip 16-bit microcontrollers and        
16-bit digital signal controllers ("Microchip Product"); and (2) at your        
own discretion and risk, use, modify, copy and distribute the device            
driver files of the Software that are provided to you in Source Code;           
provided that such Device Drivers are only used with Microchip Products         
and that no open source or free software is incorporated into the Device        
Drivers without Microchip's prior written consent in each instance.             
                                                                                
You should refer to the license agreement accompanying this Software for        
additional information regarding your rights and obligations.                   
                                                                                
SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY         
KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY              
WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A          
PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE             
LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY,               
CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY           
DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY         
INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR         
LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY,                 
SERVICES, ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY         
DEFENSE THEREOF), OR OTHER SIMILAR COSTS.                                       
                                                                                
********************************************************************************
*/

// Created by the Microchip USBConfig Utility, Version 0.0.12.0, 3/28/2008, 8:58:18

#include "GenericTypeDefs.h"
#include "HardwareProfile.h"
#include "../Microchip/Include/USB/usb.h"
#include "../PHY/usb_host_bluetooth.h"

// *****************************************************************************
// Client Driver Function Pointer Table for the USB Embedded Host foundation
// *****************************************************************************

CLIENT_DRIVER_TABLE usbClientDrvTable[NUM_CLIENT_DRIVER_ENTRIES] =
{                                        
    {
        USBHostBluetoothInit,
        USBHostBluetoothEventHandler,
        0
    },
    //Nos points d'entrées. On utilise les mêmes pour l'instant
    {
        USBHostBluetoothInit,
        USBHostBluetoothEventHandler,
        0
    },

};

// *****************************************************************************
// USB Embedded Host Targeted Peripheral List (TPL)
// *****************************************************************************
   /*[1] Device identification information
        [2] Initial USB configuration to use
        [3] Client driver table entry
        [4] Flags (HNP supported, client driver entry, SetConfiguration() commands allowed)
    ---------------------------------------------------------------------
                [1]                      [2][3] [4]
    ---------------------------------------------------------------------*/
USB_TPL usbTPL[NUM_TPL_ENTRIES] =
{
    { INIT_CL_SC_P( 0xE0ul, 1ul, 1ul ), 0x00, 0, {TPL_CLASS_DRV} }, // BT Radio
    { INIT_CL_SC_P( 0xFFul, 1ul, 1ul ), 0x00, 0, {TPL_CLASS_DRV}  }, // Stick Trust USB-Bluetooth
    { INIT_VID_PID( 0x0A12ul, 0x0001ul), 0x00, 0, 0},
};

