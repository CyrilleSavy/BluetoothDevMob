/*
------------------------------------------------------------
Copyright 2003-2005 Haute �cole ARC Ing�ni�rie, Switzerland. 
All rights reserved.
------------------------------------------------------------
Nom du fichier : 	mLcd.h	
Auteur et Date :	Monnerat Serge 20.1.2003

But : Module permettant la gestion de l'�cran LCD

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
// Mode incr�ment, pas de shift �cran 		
#define kIncrModeShiftOff         ((UINT8)(0x06))
// Efface le display et address counter=0
#define kClearDisplay      				((UINT8)(0x01))

//-----------------------------------------------------------------------------
// Envoi d'une commandes au LCD
// aCmd: la commande � transmettre au Lcd
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
// D�clenchement du backlight
//-----------------------------------------------------------------------------
void mLcd_WrtiteBackLightOff(void);

//-----------------------------------------------------------------------------
//	Ecriture sur le LCD d'un caract�re � un endroit pr�cis
// 	aChar: Le caract�re que l'on veut afficher
// 	aXpos: Position horizontale du 1er caract�re
// 	aYPos: Position verticale du 1er caract�re  
//-----------------------------------------------------------------------------
void mLcd_Write(UINT8 aChar,UINT8 aXpos,UINT8 aYPos);

//-----------------------------------------------------------------------------
//	Ecriture sur le LCD complet
// 	aChar: Pointeur sur la cha�ne de charact�re � afficher 32 caract�res
//-----------------------------------------------------------------------------
void mLcd_WriteEntireDisplay(UINT8* aChar);

//-----------------------------------------------------------------------------
// D�placement absolu du curseur
// aXpos: Position horizontale du curseur
// aYPos: Position verticale  du curseur
//-----------------------------------------------------------------------------
void mLcd_MoveCursor(UINT8 aXpos,UINT8 aYPos);


#endif