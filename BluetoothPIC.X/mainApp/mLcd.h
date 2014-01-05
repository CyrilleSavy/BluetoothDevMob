/*
------------------------------------------------------------
Copyright 2003-2005 Haute école ARC Ingéniérie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier : 	mLcd.h	
Auteur et Date :	Monnerat Serge 20.1.2003

But : Module permettant la gestion de l'écran LCD

Modifications
Date		Faite	Ctrl		Description
------------------------------------------------------------
*/

#ifndef __MLCD__
#define __MLCD__


#ifndef _H_ASSERT_
#include "assert.h"
#endif

#include "GenericTypeDefs.h"

// Lcd en mode 2 lignes,bus de 8 bits			
#define k8BitsMode_2Lines   			((UINT8)(0x38))
// Enclenche le display sans le curseur 		
#define kDisplayOnNoCursor				((UINT8)(0x0c))
// Mode incrément, pas de shift écran 		
#define kIncrModeShiftOff         ((UINT8)(0x06))
// Efface le display et address counter=0
#define kClearDisplay      				((UINT8)(0x01))

//-----------------------------------------------------------------------------
// Envoi d'une commandes au LCD
// aCmd: la commande à transmettre au Lcd
//-----------------------------------------------------------------------------
void mLcd_SendLcdCmd(UINT8 aCmd);

//-----------------------------------------------------------------------------
// Configuration du module LCD     
//-----------------------------------------------------------------------------
void mLcd_Setup(void);

//-----------------------------------------------------------------------------  
//	Ouverture de l'interface
//-----------------------------------------------------------------------------
void mLcd_Open(void);

//-----------------------------------------------------------------------------  
//	Fermeture de l'interface
//-----------------------------------------------------------------------------
void mLcd_Close(void);

//-----------------------------------------------------------------------------
// Enclenchement du backlight
//-----------------------------------------------------------------------------
void mLcd_WrtiteBackLightOn(void);

//-----------------------------------------------------------------------------
// Déclenchement du backlight
//-----------------------------------------------------------------------------
void mLcd_WrtiteBackLightOff(void);

//-----------------------------------------------------------------------------
//	Ecriture sur le LCD d'un caractère à un endroit précis
// 	aChar: Le caractère que l'on veut afficher
// 	aXpos: Position horizontale du 1er caractère
// 	aYPos: Position verticale du 1er caractère  
//-----------------------------------------------------------------------------
void mLcd_Write(UINT8 aChar,UINT8 aXpos,UINT8 aYPos);

//-----------------------------------------------------------------------------
//	Ecriture sur le LCD complet
// 	aChar: Pointeur sur la chaîne de charactère à afficher 32 caractères
//-----------------------------------------------------------------------------
void mLcd_WriteEntireDisplay(UINT8* aChar);

//-----------------------------------------------------------------------------
// Déplacement absolu du curseur
// aXpos: Position horizontale du curseur
// aYPos: Position verticale  du curseur
//-----------------------------------------------------------------------------
void mLcd_MoveCursor(UINT8 aXpos,UINT8 aYPos);


#endif