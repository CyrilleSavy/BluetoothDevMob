/*
   Copyright 2012 Guillem Vinals Gangolells <guillem@guillem.co.uk>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "Microchip/Include/Compiler.h"
#include "GenericTypeDefs.h"
#include "mainApp/HardwareProfile.h"

/* Debug values */

#define DBG_MASK 0x0021
#define DBG_LEVEL DBG_ALL
#define DBG_ASSERTIONS TRUE
#define DBG_ENABLE TRUE

enum
{
    DBG_ALL = 0,
    DBG_EXINFO,
    DBG_INFO,
    DBG_WARN,
    DBG_ERR,
    DBG_NONE
};

#define DBG_CLASS_NONE 0x0000
#define DBG_CLASS_APP 0x0001
#define DBG_CLASS_PHY 0x0002
#define DBG_CLASS_HCI 0x0004
#define DBG_CLASS_L2CAP 0x0008
#define DBG_CLASS_SDP 0x0010
#define DBG_CLASS_RFCOMM 0x0020
#define DBG_CLASS DBG_CLASS_NONE

#define DEBUG_APP (DBG_MASK & DBG_CLASS_APP)
#define DEBUG_RFCOMM (DBG_MASK & DBG_CLASS_RFCOMM)
#define DEBUG_SDP (DBG_MASK & DBG_CLASS_SDP)
#define DEBUG_L2CAP (DBG_MASK & DBG_CLASS_L2CAP)
#define DEBUG_HCI (DBG_MASK & DBG_CLASS_HCI)
#define DEBUG_PHY (DBG_MASK & DBG_CLASS_PHY)

#if DBG_ENABLE == TRUE
    /*
    void DBG_dump(UINT uClass, BYTE *pData, UINT uLen);
    void DBG_trace(UINT uClass, CHAR *pszFile, INT iLine);
    void DBG_info(UINT uClass, CHAR *pszString, ...);
    void DBG_exInfo(UINT uClass, CHAR *pszString, ...);
    void DBG_warn(UINT uClass, CHAR *pszString, ...);
    void DBG_error(UINT uClass, CHAR *pszString, ...);

    #define DBG_DUMP(X, Y)      DBG_dump(DBG_CLASS, X, Y);
    #define DBG_TRACE()         DBG_trace(DBG_CLASS, __FILE__, __LINE__);
    #define DBG_INFO(X, ...)    DBG_info(DBG_CLASS, X, ##__VA_ARGS__);
    #define DBG_EXINFO(X, ...)  DBG_exInfo(DBG_CLASS, X, ##__VA_ARGS__);
    #define DBG_WARN(X, ...)    DBG_warn(DBG_CLASS, X, ##__VA_ARGS__);
    #define DBG_ERROR(X, ...)   DBG_error(DBG_CLASS, X, ##__VA_ARGS__);
    */
    #define DBG_DUMP(X, Y)      DBG_dump(DBG_CLASS, X, Y);
    #define DBG_TRACE()         DBG_trace(DBG_CLASS, __FILE__, __LINE__);
    #define DBG_INFO(X, ...)                                    \
        if ((DBG_CLASS & DBG_MASK) && (DBG_INFO >= DBG_LEVEL))  \
            SIOPrintString(X, ##__VA_ARGS__);                   \

    #define DBG_EXINFO(X, ...)                                     \
          if ((DBG_CLASS & DBG_MASK) && (DBG_EXINFO >= DBG_LEVEL)) \
              SIOPrintString(X, ##__VA_ARGS__);                    \

    #define DBG_WARN(X, ...)                                     \
          if ((DBG_CLASS & DBG_MASK) && (DBG_WARN >= DBG_LEVEL)) \
              SIOPrintString(X, ##__VA_ARGS__);                  \

    #define DBG_ERROR(X, ...)                                   \
          if ((DBG_CLASS & DBG_MASK) && (DBG_ERR >= DBG_LEVEL)) \
              SIOPrintString(X, ##__VA_ARGS__);                 \

#else
    #define DBG_DUMP(X, Y)
    #define DBG_TRACE()
    #define DBG_INFO(X, ...)
    #define DBG_EXINFO(X, ...)
    #define DBG_WARN(X, ...)
    #define DBG_ERROR(X, ...)

#endif

#if DBG_ASSERTIONS == TRUE
    /*
    void DBG_assert(BOOL bCondition, CHAR *pszFile, INT iLine);
    
    #define ASSERT(X)        DBG_assert(X, __FILE__, __LINE__);
    */
    #define ASSERT(X)                                                          \
    if(!(X))                                                                   \
    {                                                                          \
        DBG_ERROR("ERROR: Assertion failed! (%s:%d)\n", __FILE__, __LINE__);   \
        exit(0);                                                               \
    }                                                                          \

#else
    #define ASSERT(X)

#endif


/**************************************************************************
    Function:
        void DEBUG_Initialize( void );

    Summary:
        Initializes the debug module.  This can be I/O pins, memory, etc.
        based on the debug implementation

    Description:
        Initializes the debug module.  This can be I/O pins, memory, etc.
        based on the debug implementation

    Precondition:
        None

    Parameters:
        None

    Return Values:
        None

    Remarks:
        None

  **************************************************************************/
void DEBUG_Initialize();

#if !defined(DEBUG_MODE)
    #define DEBUG_Initialize(a)
#endif

/**************************************************************************
    Function:
        void DEBUG_PutChar(char c);

    Summary:
        Puts a character into the debug stream.

    Description:
        This function puts a single character into the debug stream.

    Precondition:
        None

    Parameters:
        None

    Return Values:
        None

    Remarks:
        None

  **************************************************************************/
void DEBUG_PutChar(char c);

#if !defined(DEBUG_MODE)
    #define DEBUG_PutChar(a)
#endif

/**************************************************************************
    Function:
        void DEBUG_PutString(char* data);

    Summary:
        Prints a string to the debug stream.

    Description:
        Prints a string to the debug stream.

    Precondition:
        None

    Parameters:
        None

    Return Values:
        None

    Remarks:
        None

  **************************************************************************/
void DEBUG_PutString(char* data);

#if !defined(DEBUG_MODE)
    #define DEBUG_PutString(a) SIOPrintString(a)
#endif

/**************************************************************************
    Function:
        void DEBUG_PutHexUINT8(UINT8 data);

    Summary:
        Puts a hexidecimal 8-bit number into the debug stream.

    Description:
        Puts a hexidecimal byte of data into the debug stream.  How this
        is handled is implementation specific.  Some implementations may
        convert this to ASCII.  Others may print the byte directly to save
        memory/time.

    Precondition:
        None

    Parameters:
        None

    Return Values:
        None

    Remarks:
        None

  **************************************************************************/
void DEBUG_PutHexUINT8(UINT8 data);

#if !defined(DEBUG_MODE)
    #define DEBUG_PutHexUINT8(a)
#endif

/**************************************************************************
    Function:
        void DEBUG_PutHexUINT16(UINT16 data);

    Summary:
        Puts a hexidecimal 16-bit number into the debug stream.

    Description:
        Puts a hexidecimal byte of data into the debug stream.  How this
        is handled is implementation specific.  Some implementations may
        convert this to ASCII.  Others may print the byte directly to save
        memory/time.

    Precondition:
        None

    Parameters:
        None

    Return Values:
        None

    Remarks:
        None

  **************************************************************************/
void DEBUG_PutHexUINT16(UINT16 data);

#if !defined(DEBUG_MODE)
    #define DEBUG_PutHexUINT16(a)
#endif

/**************************************************************************
    Function:
        void DEBUG_PutHexUINT32(UINT32 data);

    Summary:
        Puts a hexidecimal 32-bit number into the debug stream.

    Description:
        Puts a hexidecimal byte of data into the debug stream.  How this
        is handled is implementation specific.  Some implementations may
        convert this to ASCII.  Others may print the byte directly to save
        memory/time.

    Precondition:
        None

    Parameters:
        None

    Return Values:
        None

    Remarks:
        None

  **************************************************************************/
void DEBUG_PutHexUINT32(UINT32 data);

#if !defined(DEBUG_MODE)
    #define DEBUG_PutHexUINT32(a)
#endif


#endif /*__DEBUG_H__*/

