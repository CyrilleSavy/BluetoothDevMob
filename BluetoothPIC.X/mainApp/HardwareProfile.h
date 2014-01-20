/********************************************************************
 FileName:     	HardwareProfile - PIC24F ADK for Android.h
 Dependencies:  See INCLUDES section
 Processor:     PIC24FJ256GB110
 Hardware:      PIC24F ADK for Android
 Compiler:      Microchip C30
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the �Company�) for its PIC� Microcontroller is intended and
 supplied to you, the Company�s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
  2.3   09/15/2008   Broke out each hardware platform into its own
                     "HardwareProfile - xxx.h" file
********************************************************************/

#ifndef HARDWARE_PROFILE_PIC24F_ADK_FOR_ANDROID_H
#define HARDWARE_PROFILE_PIC24F_ADK_FOR_ANDROID_H

#include <p24FJ256GB110.h>


    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/
    /******** Application specific definitions *************************/
    /*******************************************************************/
    /*******************************************************************/
    /*******************************************************************/

    /** Board definition ***********************************************/
    //These defintions will tell the main() function which board is
    //  currently selected.  This will allow the application to add
    //  the correct configuration bits as wells use the correct
    //  initialization functions for the board.  These defitions are only
    //  required in the stack provided demos.  They are not required in
    //  final application design.
    #define DEMO_BOARD PIC24F_ADK_FOR_ANDROID
    #define CLOCK_FREQ 32000000
    #define BAUDRATE2 115200UL
    #define BRG_DIV2 4
    #define BRGH2 1

    #define GetSystemClock()            CLOCK_FREQ
    #define GetPeripheralClock()        CLOCK_FREQ
    #define GetInstructionClock()       GetSystemClock()

    #define DEMO_BOARD_NAME_STRING "Accessory Development Starter Kit (PIC24F) for Android(tm)"
    
    /** LED ************************************************************/
    #define InitAllLEDs()  {TRISE = 0; LATE = 0;}

    #define mLED_3              LATEbits.LATE0
    #define mLED_4              LATEbits.LATE1
    #define mLED_5              LATEbits.LATE2
    #define mLED_6              LATEbits.LATE3
    #define mLED_7              LATEbits.LATE4
    #define mLED_8              LATEbits.LATE5
    #define mLED_9              LATEbits.LATE6
    #define mLED_10             LATEbits.LATE7
    
    #define LED0_On()         mLED_3  = 1;
    #define LED1_On()         mLED_4  = 1;
    #define LED2_On()         mLED_5  = 1;
    #define LED3_On()         mLED_6  = 1;
    #define LED4_On()         mLED_7  = 1;
    #define LED5_On()         mLED_8  = 1;
    #define LED6_On()         mLED_9  = 1;
    #define LED7_On()         mLED_10 = 1;
    
    #define LED0_Off()        mLED_3  = 0;
    #define LED1_Off()        mLED_4  = 0;
    #define LED2_Off()        mLED_5  = 0;
    #define LED3_Off()        mLED_6  = 0;
    #define LED4_Off()        mLED_7  = 0;
    #define LED5_Off()        mLED_8  = 0;
    #define LED6_Off()        mLED_9  = 0;
    #define LED7_Off()        mLED_10 = 0;

    /** LCD ************************************************************/
    #define InitLCDdataPorts()  {TRISDbits.TRISD10 = 0; TRISDbits.TRISD9 = 0 ; TRISDbits.TRISD8 = 0 ;TRISAbits.TRISA3 = 0 ;TRISAbits.TRISA4 = 0 ;TRISAbits.TRISA5 = 0 ;TRISAbits.TRISA14 = 0 ;TRISAbits.TRISA15 = 0 ;}
    #define InitLCDOpenCollectorData() {ODCDbits.ODD10=1 ; ODCDbits.ODD9=1 ; ODCDbits.ODD8=1 ; ODCAbits.ODA3=1 ; ODCAbits.ODA4=1 ;ODCAbits.ODA5=1 ; ODCAbits.ODA14=1 ; ODCAbits.ODA15=1 ;}
	#define InitLCDcontrolPorts()  {TRISFbits.TRISF2 = 0 ;TRISFbits.TRISF5 = 0 ;TRISFbits.TRISF4 = 0 ;TRISDbits.TRISD15 = 0 ;TRISDbits.TRISD14 = 0 ;TRISBbits.TRISB15 = 0 ;}
	#define InitLCDOpenCollectorCtrl()  {ODCFbits.ODF2=1 ; 	ODCFbits.ODF5=1 ; 	ODCFbits.ODF4=1 ; 	ODCDbits.ODD15=1 ; 	ODCDbits.ODD14=1 ; 	ODCBbits.ODB5=1 ;}

    #define mLCD_D0            LATDbits.LATD10 //PORTDbits.RD10
    #define mLCD_D1            LATDbits.LATD9 //PORTDbits.RD9
    #define mLCD_D2            LATDbits.LATD8 // PORTDbits.RD8
    #define mLCD_D3            LATAbits.LATA15 //PORTAbits.RA15
    #define mLCD_D4            LATAbits.LATA14 //PORTAbits.RA14
    #define mLCD_D5            LATAbits.LATA5 //PORTAbits.RA5
    #define mLCD_D6            LATAbits.LATA4 //PORTAbits.RA4
    #define mLCD_D7            LATAbits.LATA3 //PORTAbits.RA3

    #define mLCD_A             PORTFbits.RF2
    #define mLCD_VDD           LATFbits.LATF5//PORTFbits.RF5
    #define mLCD_V0            LATFbits.LATF4//PORTFbits.RF4
    #define mLCD_RS            LATDbits.LATD15 // PORTDbits.RD15
    #define mLCD_RW            LATDbits.LATD14 //PORTDbits.RD14
    #define mLCD_E             LATBbits.LATB15 //PORTBbits.RB15
    
    /** SWITCH *********************************************************/
    #define InitAllSwitches()   {TRISAbits.TRISA1 = 1; TRISBbits.TRISB11 = 1; TRISFbits.TRISF12 = 1; TRISFbits.TRISF13 = 1; AD1PCFGLbits.PCFG11 = 1; }
    
    #define Switch1Pressed()    ((PORTFbits.RF13  == 0)? TRUE : FALSE)
    #define Switch2Pressed()    ((PORTFbits.RF12  == 0)? TRUE : FALSE)
    #define Switch3Pressed()    ((PORTBbits.RB11  == 0)? TRUE : FALSE)
    #define Switch4Pressed()    ((PORTAbits.RA1 == 0)? TRUE : FALSE)

    /** POT ************************************************************/
    #define mInitPOT()  {AD1PCFGLbits.PCFG9 = 0;    AD1CON2bits.VCFG = 0x0;    AD1CON3bits.ADCS = 0xFF;    AD1CON1bits.SSRC = 0x0;    AD1CON3bits.SAMC = 0b10000;    AD1CON1bits.FORM = 0b00;    AD1CON2bits.SMPI = 0x0;    AD1CON1bits.ADON = 1;}

    /** I/O pin definitions ********************************************/
    #define INPUT_PIN 1
    #define OUTPUT_PIN 0

    /** Debug print interface ******************************************/
    #define DEBUG_Init(a) 
    #define DEBUG_Error(a)          
    #define DEBUG_PrintString(a) 
    #define DEBUG_PrintHex(a)


/** Serial IO ******************************************************/
#ifdef __DEBUG
    #define SIOInit()               UART2Init()
    #define SIOPrintString(s, ...) 
    #define SIOPrintStringArduino(s, ...) UART2PrintString(s)
    #define SIOPutDec(d)          
    #define SIOPutHex(h)          
    #define SIOPutChar(c)          
#else
    #define SIOInit()               UART2Init()
    #define SIOPrintStringArduino(s, ...) UART2PrintString(s)
    #define SIOPrintString(s, ...)  
    #define SIOPutDec(d)            
    #define SIOPutHex(h)            
    #define SIOPutChar(c)           
#endif

#endif  //HARDWARE_PROFILE_PIC24F_ADK_FOR_ANDROID_H
