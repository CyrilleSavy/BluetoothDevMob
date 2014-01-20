/*
------------------------------------------------------------
Copyright 2003-2006 Haute école ARC Ingéniérie, Switzerland. 
All rights reserved.
------------------------------------------------------------

Nom du fichier :	mLcd.c
Auteur et Date :	Monnerat Serge 8.5.2006

Description dans le fichier mLcd.h
------------------------------------------------------------
*/


#include "mLcd.h"
#include "HardwareProfile.h"

// Nb de caractère max du lcd, ici 2 lignes de 16 caractères
#define kMaxLcdCarac ((UINT8)(32))

// Nb de ligne
#define kNbOfLine ((UINT8)(2))

// Nb de caractères par ligne
#define kNbOfChar ((UINT8)(16))

// Définition des commandes LCD --> data 0 à data 7
// Address counter=0	
#define kReturnHome      					((UINT8)(0x02))
// Enclenche le display avec le curseur qui clignote	
#define kDisplayOnWithCursorBlink	((UINT8)(0x0f))
// Eteint l'écran		
#define kDisplayOff								((UINT8)(0x08))
// Déplacement du curseur vers la droite		
#define kMoveCursorRight					((UINT8)(0x14))
// Déplacement du curseur vers la gauche			
#define kMoveCursorLeft						((UINT8)(0x10))
// Début de la ligne 2		
#define kLineJump         				((UINT8)(0xc0))
// Set DDRAM address		
#define kSetDDRAMAdr              ((UINT8)(0x80))

//-----------------------------------------------------------------------------
// Lecture du Busy Flag
// Retour : état du busy flag
//-----------------------------------------------------------------------------
static BOOL mLcd_ReadLcdBusy(void);

//-----------------------------------------------------------------------------
// Envoi des données au LCD
// aData: les données à transmettre au LCD
//-----------------------------------------------------------------------------
static void mLcd_SendLcdData(UINT8 aData);


//-----------------------------------------------------------------------------
// Configuration du module LCD      
//-----------------------------------------------------------------------------
void mLcd_Setup(void)
{
    InitLCDdataPorts();
    InitLCDcontrolPorts();
	InitLCDOpenCollectorData();
    InitLCDOpenCollectorCtrl() ;

    mLCD_A=1;
    mLCD_VDD=0;
    mLCD_V0=0;
    mLCD_RS=0;
    mLCD_RW=0;
    mLCD_E=1;
            
    mLCD_D0=0;
    mLCD_D1=0;
    mLCD_D2=0;
    mLCD_D3=0;
    mLCD_D4=0;
    mLCD_D5=0;
    mLCD_D6=0;
    mLCD_D7=0;

/*  // Configuration du Port B
  iDio_CfgPortB(kPullupOff,kReduceDriveOff);
  
  // Configuration du Port B en entrée ou en sortie
  iDio_SetPortBDirection(kMaskIoAll,kIoOutput);
  
  // Configuration du Port K
  iDio_CfgPortK(kPullupOff,kReduceDriveOff);
  
  // Configuration du Port K en entrée ou en sortie
  iDio_SetPortKDirection((UInt8)(kMaskIo0+kMaskIo1+kMaskIo2+kMaskIo3),kIoOutput);
  
  // Toutes les sorties à 0
  iDio_SetPortK((UInt8)(kMaskIo0+kMaskIo1+kMaskIo2+kMaskIo3),kIoOff);
*/
}


//-----------------------------------------------------------------------------  
//	Ouverture de l'interface (init du display)
//-----------------------------------------------------------------------------
void mLcd_Open(void)
{
	unsigned long i = 0 ;

    //power supply of LCD
    mLCD_VDD=1;
    mLCD_V0=1;

    DelayMs(40);

	// Selection du mode 2 lignes + display on
    mLcd_SendLcdCmd(0x3C);
    Delay10us(4);

    
    // attendre ~39us
    
    // Selection du mode pas curseur + display on
    mLcd_SendLcdCmd(0x0C);
    Delay10us(4);

    
    // attendre ~39us

    //Display clear
    mLcd_SendLcdCmd(0x01);
    DelayMs(2);
    
    // attendre ~1.53ms
    mLcd_SendLcdCmd(0x06);
    Delay10us(4);

}

//-----------------------------------------------------------------------------  
//	Fermeture de l'interface
//-----------------------------------------------------------------------------
void mLcd_Close(void)
{
	// Attente du busy flag=0
	while(TRUE==mLcd_ReadLcdBusy());
	
	// Efface la mémoire
	mLcd_SendLcdCmd(kClearDisplay);
	
	// Attente du busy flag=0
	while(TRUE==mLcd_ReadLcdBusy());
	
	// Lcd éteint
	mLcd_SendLcdCmd(kDisplayOff);
}

//-----------------------------------------------------------------------------
// Enclenchement du backlight
//-----------------------------------------------------------------------------
void mLcd_WrtiteBackLightOn(void)
{
mLCD_A=0;
}


//-----------------------------------------------------------------------------
// Déclenchement du backlight
//-----------------------------------------------------------------------------
void mLcd_WrtiteBackLightOff(void)
{
mLCD_A=1;
}

//-----------------------------------------------------------------------------
// Ecriture sur le LCD d'un caractère à un endroit précis
// aChar: Le caractère que l'on veut afficher
// aXpos: Position horizontale du 1er caractère
// aYPos: Position verticale du 1er caractère  
//-----------------------------------------------------------------------------
void mLcd_Write(UINT8 aChar,UINT8 aXpos,UINT8 aYPos)
{
	UINT16 aTmp=0;
	
	// Contrôle si le numéro de ligne est en accord avec notre LCD
	if((aYPos>=kNbOfLine)||(aYPos<0))
	  {
	    //aTmp=assert(0);
	  }
	
	// Contrôle si le numéro de caractère est en accord avec notre LCD
	if((aXpos>=kNbOfChar)||(aXpos<0))
	  {
	    //aTmp=assert(0);
	  }
	
	// Modification de l'Address Counter AC
	// Calcul de l'adresse DDRAM
	aTmp=kSetDDRAMAdr+aXpos+(aYPos*0x40);
	
	// Attente du busy flag=0
	while(TRUE==mLcd_ReadLcdBusy());
	
	// Set DDRAM Address Counter
	mLcd_SendLcdCmd(aTmp);
	
	// Attente du busy flag=0
	while(TRUE==mLcd_ReadLcdBusy());
	
	// Envoi du caractère au LCD
	mLcd_SendLcdData(aChar);
}

//-----------------------------------------------------------------------------
//	Ecriture sur le LCD complet
// aChar: Pointeur sur la chaîne de charactère à afficher 32 caractères
//-----------------------------------------------------------------------------
void mLcd_WriteEntireDisplay(UINT8* aChar)
{

	UINT16 i;
	
	// Attente du busy flag=0
	while(TRUE==mLcd_ReadLcdBusy());
	
	// Efface la mémoire
	mLcd_SendLcdCmd(kReturnHome); 
    DelayMs(2);
	
	// Envoi des 32 caractères à l'affichage
	for (i=0;i<kMaxLcdCarac;i++) 
		{
	  	// Attente du busy=0
			while(TRUE==mLcd_ReadLcdBusy());
			
			// Envoi du caractère au LCD
			mLcd_SendLcdData(*aChar);
            Delay10us(5);
			
			// Si fin de 1ère ligne on passe à la 2e
			if((kNbOfChar-1)==i)
				{
					// Attente du busy flag=0
					while(TRUE==mLcd_ReadLcdBusy());
	
					// 2e ligne
					mLcd_SendLcdCmd(kLineJump);
                    Delay10us(5);
				}
			
			// Caractère suivant
			aChar++;
	  }
}

//-----------------------------------------------------------------------------
// Lecture du Busy Flag
// Retour : état du busy flag
//-----------------------------------------------------------------------------
static BOOL mLcd_ReadLcdBusy(void)
{
 	BOOL aVal;
 	
  Delay10us(1);
  mLCD_E=1;
  mLCD_RW=0;
  mLCD_RS=0;
  Delay10us(1);


 	// Data 7 en entrée
 	//iDio_SetPortBDirection(kMaskIo7,kIoInput);
    TRISAbits.TRISA3 = 1 ;
 	
 	// E inactif
 	//iDio_SetPortK(kMaskIo0,kIoOff);
    Delay10us(1);
   mLCD_E=1;	
   Delay10us(1);
	// Bit RS=0 --> on sélectionne les registres d'instruction
  //iDio_SetPortK(kMaskIo2,kIoOff);
  mLCD_RS=0;
  Delay10us(1);
  
  // Bit RW=1, read
  //iDio_SetPortK(kMaskIo1,kIoOn);
  mLCD_RW=1;
  Delay10us(1);
  
	// RS et RW doivent être présent depuis 40 ns
  // avant que start read (E) soit inséré
	//iDio_SetPortK(kMaskIo0,kIoOff);
  mLCD_E=1;
  Delay10us(1);
	
	// E (start read) doit être inséré pendant au moins 230ns
	// les données sont valides après 120ns
	//iDio_SetPortK(kMaskIo0,kIoOn);
  mLCD_E=0;
  Delay10us(1);
	
 	// Lecture du data 7 --> busy flag
 aVal=PORTAbits.RA3; //mLCD_D7
 	
 	// Reset de E
 	//iDio_SetPortK(kMaskIo0,kIoOff);
   mLCD_E=1;
   Delay10us(1);
	
 	// Data 7 en sortie
 	//iDio_SetPortBDirection(kMaskIo7,kIoOutput);
    TRISAbits.TRISA3 = 0 ;
   Delay10us(1);
   
   mLCD_E=1;
   mLCD_RW=0;
   mLCD_RS=0;
	
 	return aVal; 
}

//-----------------------------------------------------------------------------
// Envoi des données au LCD
// aData: les données à transmettre au LCD
//-----------------------------------------------------------------------------
static void mLcd_SendLcdData(UINT8 aData)
{
  // E inactif
  Delay10us(1);
  mLCD_E=1;
  mLCD_RW=0;
  mLCD_RS=1;
  
  // écriture des données
  //iDio_SetPortB(aData);
    mLCD_D0= aData & 0x01;
    mLCD_D1= (aData & 0x02)>>1;
    mLCD_D2= (aData & 0x04)>>2;
    mLCD_D3= (aData & 0x08)>>3;
    mLCD_D4= (aData & 0x10)>>4;
    mLCD_D5= (aData & 0x20)>>5;
    mLCD_D6= (aData & 0x40)>>6;
    mLCD_D7= (aData & 0x80)>>7;
    Delay10us(1);

  // Bit E (start data read/write) à 1
  // le bits E doit être à 1 pendant au moins 230nsec
  //iDio_SetPortK(kMaskIo0,kIoOn);
  mLCD_E=0;
  Delay10us(1);

  // Bit E (start data read/write) à 0
  // les data sont latchés à ce moment là
  //iDio_SetPortK(kMaskIo0,kIoOff);
  mLCD_E=1;
  mLCD_RW=0;
  mLCD_RS=0;

}

//-----------------------------------------------------------------------------
// Envoi d'une commandes au LCD
// aCmd: la commande à transmettre au Lcd
//-----------------------------------------------------------------------------
void mLcd_SendLcdCmd(UINT8 aCmd)
{
  // E inactif
 	//iDio_SetPortK(kMaskIo0,kIoOff);
  Delay10us(1);
  mLCD_E=1;
  mLCD_RW=0;
  mLCD_RS=0;

  // écriture des données
  //iDio_SetPortB(aCmd);
    mLCD_D0= aCmd & 0x01;
    mLCD_D1= (aCmd & 0x02)>>1;
    mLCD_D2= (aCmd & 0x04)>>2;
    mLCD_D3= (aCmd & 0x08)>>3;
    mLCD_D4= (aCmd & 0x10)>>4;
    mLCD_D5= (aCmd & 0x20)>>5;
    mLCD_D6= (aCmd & 0x40)>>6;
    mLCD_D7= (aCmd & 0x80)>>7;
    Delay10us(1);

  // Bit E (start data read/write) à 1
  // le bits E doit être à 1 pendant au moins 230nsec
  //iDio_SetPortK(kMaskIo0,kIoOn);
  mLCD_E=0;
   Delay10us(1);
 
  // Bit E (start data read/write) à 0
	// les data sont latchés à ce moment là, elles doivent être valides 
	//pendant 10 ns
	//iDio_SetPortK(kMaskIo0,kIoOff);
        mLCD_E=1;
  Delay10us(1);

  mLCD_E=1;
  mLCD_RW=0;
  mLCD_RS=0;

}


//-----------------------------------------------------------------------------
// Déplacement absolu du curseur
// aXpos: Position horizontale du curseur
// aYPos: Position verticale  du curseur
//-----------------------------------------------------------------------------
void mLcd_MoveCursor(UINT8 aXpos,UINT8 aYPos)
{
	UINT16 aTmp=0;
	
	// Attente du busy flag=0
	while(TRUE==mLcd_ReadLcdBusy());
	
	// Calcul de l'adresse DDRAM
	aTmp=kSetDDRAMAdr+aXpos+(aYPos*0x40);
	
	// Set DDRAM Address Counter
	mLcd_SendLcdCmd(aTmp);
}



