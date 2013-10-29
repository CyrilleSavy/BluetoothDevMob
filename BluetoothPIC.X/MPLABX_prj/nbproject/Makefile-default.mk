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
SOURCEFILES_QUOTED_IF_SPACED=../Bluetooth/bt_utils.c ../Bluetooth/hci.c ../Bluetooth/hci_usb.c ../Bluetooth/l2cap_2.c ../Bluetooth/rfcomm.c ../Bluetooth/rfcomm_fcs.c ../Bluetooth/sdp.c ../bluetoothUSB/usb_host_bluetooth.c ../mainApp/main.c ../mainApp/usb_config.c ../Microchip/Common/TimeDelay.c ../Microchip/USB/usb_host.c ../BTApp.c ../debug.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/380863233/bt_utils.o ${OBJECTDIR}/_ext/380863233/hci.o ${OBJECTDIR}/_ext/380863233/hci_usb.o ${OBJECTDIR}/_ext/380863233/l2cap_2.o ${OBJECTDIR}/_ext/380863233/rfcomm.o ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o ${OBJECTDIR}/_ext/380863233/sdp.o ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o ${OBJECTDIR}/_ext/849512359/main.o ${OBJECTDIR}/_ext/849512359/usb_config.o ${OBJECTDIR}/_ext/221508487/TimeDelay.o ${OBJECTDIR}/_ext/343710134/usb_host.o ${OBJECTDIR}/_ext/1472/BTApp.o ${OBJECTDIR}/_ext/1472/debug.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/380863233/bt_utils.o.d ${OBJECTDIR}/_ext/380863233/hci.o.d ${OBJECTDIR}/_ext/380863233/hci_usb.o.d ${OBJECTDIR}/_ext/380863233/l2cap_2.o.d ${OBJECTDIR}/_ext/380863233/rfcomm.o.d ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o.d ${OBJECTDIR}/_ext/380863233/sdp.o.d ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o.d ${OBJECTDIR}/_ext/849512359/main.o.d ${OBJECTDIR}/_ext/849512359/usb_config.o.d ${OBJECTDIR}/_ext/221508487/TimeDelay.o.d ${OBJECTDIR}/_ext/343710134/usb_host.o.d ${OBJECTDIR}/_ext/1472/BTApp.o.d ${OBJECTDIR}/_ext/1472/debug.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/380863233/bt_utils.o ${OBJECTDIR}/_ext/380863233/hci.o ${OBJECTDIR}/_ext/380863233/hci_usb.o ${OBJECTDIR}/_ext/380863233/l2cap_2.o ${OBJECTDIR}/_ext/380863233/rfcomm.o ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o ${OBJECTDIR}/_ext/380863233/sdp.o ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o ${OBJECTDIR}/_ext/849512359/main.o ${OBJECTDIR}/_ext/849512359/usb_config.o ${OBJECTDIR}/_ext/221508487/TimeDelay.o ${OBJECTDIR}/_ext/343710134/usb_host.o ${OBJECTDIR}/_ext/1472/BTApp.o ${OBJECTDIR}/_ext/1472/debug.o

# Source Files
SOURCEFILES=../Bluetooth/bt_utils.c ../Bluetooth/hci.c ../Bluetooth/hci_usb.c ../Bluetooth/l2cap_2.c ../Bluetooth/rfcomm.c ../Bluetooth/rfcomm_fcs.c ../Bluetooth/sdp.c ../bluetoothUSB/usb_host_bluetooth.c ../mainApp/main.c ../mainApp/usb_config.c ../Microchip/Common/TimeDelay.c ../Microchip/USB/usb_host.c ../BTApp.c ../debug.c


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
${OBJECTDIR}/_ext/380863233/bt_utils.o: ../Bluetooth/bt_utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/bt_utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/bt_utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/bt_utils.c  -o ${OBJECTDIR}/_ext/380863233/bt_utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/bt_utils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/bt_utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/hci.o: ../Bluetooth/hci.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/hci.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/hci.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/hci.c  -o ${OBJECTDIR}/_ext/380863233/hci.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/hci.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/hci.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/hci_usb.o: ../Bluetooth/hci_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/hci_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/hci_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/hci_usb.c  -o ${OBJECTDIR}/_ext/380863233/hci_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/hci_usb.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/hci_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/l2cap_2.o: ../Bluetooth/l2cap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/l2cap_2.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/l2cap_2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/l2cap_2.c  -o ${OBJECTDIR}/_ext/380863233/l2cap_2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/l2cap_2.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/l2cap_2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/rfcomm.o: ../Bluetooth/rfcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/rfcomm.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/rfcomm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/rfcomm.c  -o ${OBJECTDIR}/_ext/380863233/rfcomm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/rfcomm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/rfcomm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o: ../Bluetooth/rfcomm_fcs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/rfcomm_fcs.c  -o ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/sdp.o: ../Bluetooth/sdp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/sdp.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/sdp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/sdp.c  -o ${OBJECTDIR}/_ext/380863233/sdp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/sdp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/sdp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o: ../bluetoothUSB/usb_host_bluetooth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/842785765 
	@${RM} ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o.d 
	@${RM} ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bluetoothUSB/usb_host_bluetooth.c  -o ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/849512359/main.o: ../mainApp/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/849512359 
	@${RM} ${OBJECTDIR}/_ext/849512359/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/849512359/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mainApp/main.c  -o ${OBJECTDIR}/_ext/849512359/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/849512359/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/849512359/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/849512359/usb_config.o: ../mainApp/usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/849512359 
	@${RM} ${OBJECTDIR}/_ext/849512359/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/849512359/usb_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mainApp/usb_config.c  -o ${OBJECTDIR}/_ext/849512359/usb_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/849512359/usb_config.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/849512359/usb_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221508487/TimeDelay.o: ../Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/221508487 
	@${RM} ${OBJECTDIR}/_ext/221508487/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/221508487/TimeDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Microchip/Common/TimeDelay.c  -o ${OBJECTDIR}/_ext/221508487/TimeDelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221508487/TimeDelay.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/221508487/TimeDelay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/343710134/usb_host.o: ../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/343710134 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Microchip/USB/usb_host.c  -o ${OBJECTDIR}/_ext/343710134/usb_host.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_host.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_host.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/BTApp.o: ../BTApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/BTApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/BTApp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../BTApp.c  -o ${OBJECTDIR}/_ext/1472/BTApp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/BTApp.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/BTApp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/debug.o: ../debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../debug.c  -o ${OBJECTDIR}/_ext/1472/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/380863233/bt_utils.o: ../Bluetooth/bt_utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/bt_utils.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/bt_utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/bt_utils.c  -o ${OBJECTDIR}/_ext/380863233/bt_utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/bt_utils.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/bt_utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/hci.o: ../Bluetooth/hci.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/hci.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/hci.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/hci.c  -o ${OBJECTDIR}/_ext/380863233/hci.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/hci.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/hci.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/hci_usb.o: ../Bluetooth/hci_usb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/hci_usb.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/hci_usb.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/hci_usb.c  -o ${OBJECTDIR}/_ext/380863233/hci_usb.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/hci_usb.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/hci_usb.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/l2cap_2.o: ../Bluetooth/l2cap_2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/l2cap_2.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/l2cap_2.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/l2cap_2.c  -o ${OBJECTDIR}/_ext/380863233/l2cap_2.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/l2cap_2.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/l2cap_2.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/rfcomm.o: ../Bluetooth/rfcomm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/rfcomm.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/rfcomm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/rfcomm.c  -o ${OBJECTDIR}/_ext/380863233/rfcomm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/rfcomm.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/rfcomm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o: ../Bluetooth/rfcomm_fcs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/rfcomm_fcs.c  -o ${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/rfcomm_fcs.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/380863233/sdp.o: ../Bluetooth/sdp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/380863233 
	@${RM} ${OBJECTDIR}/_ext/380863233/sdp.o.d 
	@${RM} ${OBJECTDIR}/_ext/380863233/sdp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Bluetooth/sdp.c  -o ${OBJECTDIR}/_ext/380863233/sdp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/380863233/sdp.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/380863233/sdp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o: ../bluetoothUSB/usb_host_bluetooth.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/842785765 
	@${RM} ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o.d 
	@${RM} ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../bluetoothUSB/usb_host_bluetooth.c  -o ${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/842785765/usb_host_bluetooth.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/849512359/main.o: ../mainApp/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/849512359 
	@${RM} ${OBJECTDIR}/_ext/849512359/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/849512359/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mainApp/main.c  -o ${OBJECTDIR}/_ext/849512359/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/849512359/main.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/849512359/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/849512359/usb_config.o: ../mainApp/usb_config.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/849512359 
	@${RM} ${OBJECTDIR}/_ext/849512359/usb_config.o.d 
	@${RM} ${OBJECTDIR}/_ext/849512359/usb_config.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../mainApp/usb_config.c  -o ${OBJECTDIR}/_ext/849512359/usb_config.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/849512359/usb_config.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/849512359/usb_config.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/221508487/TimeDelay.o: ../Microchip/Common/TimeDelay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/221508487 
	@${RM} ${OBJECTDIR}/_ext/221508487/TimeDelay.o.d 
	@${RM} ${OBJECTDIR}/_ext/221508487/TimeDelay.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Microchip/Common/TimeDelay.c  -o ${OBJECTDIR}/_ext/221508487/TimeDelay.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/221508487/TimeDelay.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/221508487/TimeDelay.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/343710134/usb_host.o: ../Microchip/USB/usb_host.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/343710134 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o.d 
	@${RM} ${OBJECTDIR}/_ext/343710134/usb_host.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../Microchip/USB/usb_host.c  -o ${OBJECTDIR}/_ext/343710134/usb_host.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/343710134/usb_host.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/343710134/usb_host.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/BTApp.o: ../BTApp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/BTApp.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/BTApp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../BTApp.c  -o ${OBJECTDIR}/_ext/1472/BTApp.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/BTApp.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/BTApp.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1472/debug.o: ../debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1472 
	@${RM} ${OBJECTDIR}/_ext/1472/debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../debug.c  -o ${OBJECTDIR}/_ext/1472/debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1472/debug.o.d"      -g -omf=elf -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--heap=16,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MPLABX_prj.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=16,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem$(MP_EXTRA_LD_POST) 
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
