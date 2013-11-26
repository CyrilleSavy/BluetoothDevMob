#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../mainApp/main.c ../mainApp/usb_config.c ../Microchip/Common/TimeDelay.c ../Microchip/USB/usb_host.c ../debug.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/ADK.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/BT.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btL2CAP.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btRFCOMM.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btSDP.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/PHY/usb_host_bluetooth.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/sgBuf.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Microchip/Common/uart2.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/849512359/main.o ${OBJECTDIR}/_ext/849512359/usb_config.o ${OBJECTDIR}/_ext/221508487/TimeDelay.o ${OBJECTDIR}/_ext/343710134/usb_host.o ${OBJECTDIR}/_ext/1472/debug.o ${OBJECTDIR}/_ext/1945444792/ADK.o ${OBJECTDIR}/_ext/1945444792/BT.o ${OBJECTDIR}/_ext/1945444792/btL2CAP.o ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o ${OBJECTDIR}/_ext/1945444792/btSDP.o ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o ${OBJECTDIR}/_ext/1945444792/sgBuf.o ${OBJECTDIR}/_ext/1042080697/uart2.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/849512359/main.o.d ${OBJECTDIR}/_ext/849512359/usb_config.o.d ${OBJECTDIR}/_ext/221508487/TimeDelay.o.d ${OBJECTDIR}/_ext/343710134/usb_host.o.d ${OBJECTDIR}/_ext/1472/debug.o.d ${OBJECTDIR}/_ext/1945444792/ADK.o.d ${OBJECTDIR}/_ext/1945444792/BT.o.d ${OBJECTDIR}/_ext/1945444792/btL2CAP.o.d ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o.d ${OBJECTDIR}/_ext/1945444792/btSDP.o.d ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o.d ${OBJECTDIR}/_ext/1945444792/sgBuf.o.d ${OBJECTDIR}/_ext/1042080697/uart2.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/849512359/main.o ${OBJECTDIR}/_ext/849512359/usb_config.o ${OBJECTDIR}/_ext/221508487/TimeDelay.o ${OBJECTDIR}/_ext/343710134/usb_host.o ${OBJECTDIR}/_ext/1472/debug.o ${OBJECTDIR}/_ext/1945444792/ADK.o ${OBJECTDIR}/_ext/1945444792/BT.o ${OBJECTDIR}/_ext/1945444792/btL2CAP.o ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o ${OBJECTDIR}/_ext/1945444792/btSDP.o ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o ${OBJECTDIR}/_ext/1945444792/sgBuf.o ${OBJECTDIR}/_ext/1042080697/uart2.o

# Source Files
SOURCEFILES=../mainApp/main.c ../mainApp/usb_config.c ../Microchip/Common/TimeDelay.c ../Microchip/USB/usb_host.c ../debug.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/ADK.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/BT.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btL2CAP.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btRFCOMM.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btSDP.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/PHY/usb_host_bluetooth.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/sgBuf.c D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Microchip/Common/uart2.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ256GB110
MP_LINKER_FILE_OPTION=,--script=p24FJ256GB110.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/849512359/main.o: ../mainApp/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/849512359 
	@${RM} ${OBJECTDIR}/_ext/849512359/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/849512359/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mainApp/main.c  -o ${OBJECTDIR}/_ext/849512359/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/849512359/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/849512359/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/849512359/usb_config.o: ../mainApp/usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/849512359 
	@${RM} ${OBJECTDIR}/_ext/849512359/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/849512359/usb_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mainApp/usb_config.c  -o ${OBJECTDIR}/_ext/849512359/usb_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/849512359/usb_config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/849512359/usb_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221508487/TimeDelay.o: ../Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/221508487 
	@${RM} ${OBJECTDIR}/_ext/221508487/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/221508487/TimeDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Microchip/Common/TimeDelay.c  -o ${OBJECTDIR}/_ext/221508487/TimeDelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221508487/TimeDelay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/221508487/TimeDelay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/343710134/usb_host.o: ../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/343710134 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Microchip/USB/usb_host.c  -o ${OBJECTDIR}/_ext/343710134/usb_host.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_host.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_host.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/debug.o: ../debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../debug.c  -o ${OBJECTDIR}/_ext/1472/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/ADK.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/ADK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/ADK.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/ADK.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/ADK.c  -o ${OBJECTDIR}/_ext/1945444792/ADK.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/ADK.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/ADK.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/BT.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/BT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/BT.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/BT.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/BT.c  -o ${OBJECTDIR}/_ext/1945444792/BT.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/BT.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/BT.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/btL2CAP.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btL2CAP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btL2CAP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btL2CAP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btL2CAP.c  -o ${OBJECTDIR}/_ext/1945444792/btL2CAP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/btL2CAP.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/btL2CAP.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/btRFCOMM.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btRFCOMM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btRFCOMM.c  -o ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/btRFCOMM.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/btRFCOMM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/btSDP.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btSDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btSDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btSDP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btSDP.c  -o ${OBJECTDIR}/_ext/1945444792/btSDP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/btSDP.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/btSDP.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/PHY/usb_host_bluetooth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/235082244 
	@${RM} ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o.d 
	@${RM} ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/PHY/usb_host_bluetooth.c  -o ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/sgBuf.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/sgBuf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/sgBuf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/sgBuf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/sgBuf.c  -o ${OBJECTDIR}/_ext/1945444792/sgBuf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/sgBuf.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/sgBuf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1042080697/uart2.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Microchip/Common/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1042080697 
	@${RM} ${OBJECTDIR}/_ext/1042080697/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1042080697/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Microchip/Common/uart2.c  -o ${OBJECTDIR}/_ext/1042080697/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1042080697/uart2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1042080697/uart2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/849512359/main.o: ../mainApp/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/849512359 
	@${RM} ${OBJECTDIR}/_ext/849512359/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/849512359/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mainApp/main.c  -o ${OBJECTDIR}/_ext/849512359/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/849512359/main.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/849512359/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/849512359/usb_config.o: ../mainApp/usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/849512359 
	@${RM} ${OBJECTDIR}/_ext/849512359/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/849512359/usb_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mainApp/usb_config.c  -o ${OBJECTDIR}/_ext/849512359/usb_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/849512359/usb_config.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/849512359/usb_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221508487/TimeDelay.o: ../Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/221508487 
	@${RM} ${OBJECTDIR}/_ext/221508487/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/221508487/TimeDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Microchip/Common/TimeDelay.c  -o ${OBJECTDIR}/_ext/221508487/TimeDelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221508487/TimeDelay.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/221508487/TimeDelay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/343710134/usb_host.o: ../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/343710134 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Microchip/USB/usb_host.c  -o ${OBJECTDIR}/_ext/343710134/usb_host.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_host.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_host.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/debug.o: ../debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../debug.c  -o ${OBJECTDIR}/_ext/1472/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/debug.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/ADK.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/ADK.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/ADK.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/ADK.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/ADK.c  -o ${OBJECTDIR}/_ext/1945444792/ADK.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/ADK.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/ADK.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/BT.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/BT.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/BT.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/BT.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/BT.c  -o ${OBJECTDIR}/_ext/1945444792/BT.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/BT.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/BT.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/btL2CAP.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btL2CAP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btL2CAP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btL2CAP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btL2CAP.c  -o ${OBJECTDIR}/_ext/1945444792/btL2CAP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/btL2CAP.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/btL2CAP.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/btRFCOMM.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btRFCOMM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btRFCOMM.c  -o ${OBJECTDIR}/_ext/1945444792/btRFCOMM.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/btRFCOMM.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/btRFCOMM.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/btSDP.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btSDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btSDP.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/btSDP.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/btSDP.c  -o ${OBJECTDIR}/_ext/1945444792/btSDP.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/btSDP.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/btSDP.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/PHY/usb_host_bluetooth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/235082244 
	@${RM} ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o.d 
	@${RM} ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/PHY/usb_host_bluetooth.c  -o ${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/235082244/usb_host_bluetooth.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1945444792/sgBuf.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/sgBuf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1945444792 
	@${RM} ${OBJECTDIR}/_ext/1945444792/sgBuf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1945444792/sgBuf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Bt_stack/sgBuf.c  -o ${OBJECTDIR}/_ext/1945444792/sgBuf.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1945444792/sgBuf.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1945444792/sgBuf.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1042080697/uart2.o: D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Microchip/Common/uart2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1042080697 
	@${RM} ${OBJECTDIR}/_ext/1042080697/uart2.o.d 
	@${RM} ${OBJECTDIR}/_ext/1042080697/uart2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  D:/Module_DevMobile/Repo_Projet/BluetoothDevMob/BluetoothPIC.X/Microchip/Common/uart2.c  -o ${OBJECTDIR}/_ext/1042080697/uart2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1042080697/uart2.o.d"      -g -omf=elf -O2 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1042080697/uart2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=3000,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=3000,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
