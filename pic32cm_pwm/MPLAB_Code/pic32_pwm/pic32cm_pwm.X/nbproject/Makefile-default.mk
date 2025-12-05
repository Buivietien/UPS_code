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
FINAL_IMAGE=${DISTDIR}/pic32cm_pwm.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/pic32cm_pwm.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../src/config/default/peripheral/adc/plib_adc0.c ../src/config/default/peripheral/adc/plib_adc1.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/dac/plib_dac.c ../src/config/default/peripheral/divas/plib_divas.c ../src/config/default/peripheral/dmac/plib_dmac.c ../src/config/default/peripheral/eic/plib_eic.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/sercom/usart/plib_sercom1_usart.c ../src/config/default/peripheral/systick/plib_systick.c ../src/config/default/peripheral/tc/plib_tc4.c ../src/config/default/peripheral/tcc/plib_tcc0.c ../src/config/default/peripheral/tcc/plib_tcc1.c ../src/config/default/peripheral/tcc/plib_tcc2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/libc_syscalls.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/gcode_parser/gcode_command.c ../src/gcode_parser/GCodeParser.c ../src/inverter_control/relay.c ../src/inverter_control/spwm.c ../src/inverter_control/adc.c ../src/inverter_control/sogi_pll.c ../src/pid_controller/pid_control.c ../src/printf_custom/printf.c ../src/printf_custom/uart_setup.c ../src/push_pull_control/push_pull_ctrl.c ../src/system_mornitor_n_leds/leds.c ../src/system_mornitor_n_leds/system_mornitor.c ../src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/60163342/plib_adc0.o ${OBJECTDIR}/_ext/60163342/plib_adc1.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/60166132/plib_dac.o ${OBJECTDIR}/_ext/1985337713/plib_divas.o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ${OBJECTDIR}/_ext/60167341/plib_eic.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ${OBJECTDIR}/_ext/60181570/plib_tcc0.o ${OBJECTDIR}/_ext/60181570/plib_tcc1.o ${OBJECTDIR}/_ext/60181570/plib_tcc2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1988303524/gcode_command.o ${OBJECTDIR}/_ext/1988303524/GCodeParser.o ${OBJECTDIR}/_ext/1330506277/relay.o ${OBJECTDIR}/_ext/1330506277/spwm.o ${OBJECTDIR}/_ext/1330506277/adc.o ${OBJECTDIR}/_ext/1330506277/sogi_pll.o ${OBJECTDIR}/_ext/1514240246/pid_control.o ${OBJECTDIR}/_ext/1155226525/printf.o ${OBJECTDIR}/_ext/1155226525/uart_setup.o ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o ${OBJECTDIR}/_ext/1580483562/leds.o ${OBJECTDIR}/_ext/1580483562/system_mornitor.o ${OBJECTDIR}/_ext/1360937237/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/60163342/plib_adc0.o.d ${OBJECTDIR}/_ext/60163342/plib_adc1.o.d ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d ${OBJECTDIR}/_ext/60166132/plib_dac.o.d ${OBJECTDIR}/_ext/1985337713/plib_divas.o.d ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d ${OBJECTDIR}/_ext/60167341/plib_eic.o.d ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d ${OBJECTDIR}/_ext/1865521619/plib_port.o.d ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o.d ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d ${OBJECTDIR}/_ext/60181570/plib_tcc0.o.d ${OBJECTDIR}/_ext/60181570/plib_tcc1.o.d ${OBJECTDIR}/_ext/60181570/plib_tcc2.o.d ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d ${OBJECTDIR}/_ext/1171490990/initialization.o.d ${OBJECTDIR}/_ext/1171490990/interrupts.o.d ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d ${OBJECTDIR}/_ext/1171490990/exceptions.o.d ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d ${OBJECTDIR}/_ext/1988303524/gcode_command.o.d ${OBJECTDIR}/_ext/1988303524/GCodeParser.o.d ${OBJECTDIR}/_ext/1330506277/relay.o.d ${OBJECTDIR}/_ext/1330506277/spwm.o.d ${OBJECTDIR}/_ext/1330506277/adc.o.d ${OBJECTDIR}/_ext/1330506277/sogi_pll.o.d ${OBJECTDIR}/_ext/1514240246/pid_control.o.d ${OBJECTDIR}/_ext/1155226525/printf.o.d ${OBJECTDIR}/_ext/1155226525/uart_setup.o.d ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o.d ${OBJECTDIR}/_ext/1580483562/leds.o.d ${OBJECTDIR}/_ext/1580483562/system_mornitor.o.d ${OBJECTDIR}/_ext/1360937237/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/60163342/plib_adc0.o ${OBJECTDIR}/_ext/60163342/plib_adc1.o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ${OBJECTDIR}/_ext/60166132/plib_dac.o ${OBJECTDIR}/_ext/1985337713/plib_divas.o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ${OBJECTDIR}/_ext/60167341/plib_eic.o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ${OBJECTDIR}/_ext/1865521619/plib_port.o ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ${OBJECTDIR}/_ext/60181570/plib_tcc0.o ${OBJECTDIR}/_ext/60181570/plib_tcc1.o ${OBJECTDIR}/_ext/60181570/plib_tcc2.o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ${OBJECTDIR}/_ext/1171490990/initialization.o ${OBJECTDIR}/_ext/1171490990/interrupts.o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ${OBJECTDIR}/_ext/1171490990/exceptions.o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ${OBJECTDIR}/_ext/1988303524/gcode_command.o ${OBJECTDIR}/_ext/1988303524/GCodeParser.o ${OBJECTDIR}/_ext/1330506277/relay.o ${OBJECTDIR}/_ext/1330506277/spwm.o ${OBJECTDIR}/_ext/1330506277/adc.o ${OBJECTDIR}/_ext/1330506277/sogi_pll.o ${OBJECTDIR}/_ext/1514240246/pid_control.o ${OBJECTDIR}/_ext/1155226525/printf.o ${OBJECTDIR}/_ext/1155226525/uart_setup.o ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o ${OBJECTDIR}/_ext/1580483562/leds.o ${OBJECTDIR}/_ext/1580483562/system_mornitor.o ${OBJECTDIR}/_ext/1360937237/main.o

# Source Files
SOURCEFILES=../src/config/default/peripheral/adc/plib_adc0.c ../src/config/default/peripheral/adc/plib_adc1.c ../src/config/default/peripheral/clock/plib_clock.c ../src/config/default/peripheral/dac/plib_dac.c ../src/config/default/peripheral/divas/plib_divas.c ../src/config/default/peripheral/dmac/plib_dmac.c ../src/config/default/peripheral/eic/plib_eic.c ../src/config/default/peripheral/evsys/plib_evsys.c ../src/config/default/peripheral/nvic/plib_nvic.c ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c ../src/config/default/peripheral/port/plib_port.c ../src/config/default/peripheral/sercom/usart/plib_sercom1_usart.c ../src/config/default/peripheral/systick/plib_systick.c ../src/config/default/peripheral/tc/plib_tc4.c ../src/config/default/peripheral/tcc/plib_tcc0.c ../src/config/default/peripheral/tcc/plib_tcc1.c ../src/config/default/peripheral/tcc/plib_tcc2.c ../src/config/default/stdio/xc32_monitor.c ../src/config/default/initialization.c ../src/config/default/interrupts.c ../src/config/default/libc_syscalls.c ../src/config/default/exceptions.c ../src/config/default/startup_xc32.c ../src/gcode_parser/gcode_command.c ../src/gcode_parser/GCodeParser.c ../src/inverter_control/relay.c ../src/inverter_control/spwm.c ../src/inverter_control/adc.c ../src/inverter_control/sogi_pll.c ../src/pid_controller/pid_control.c ../src/printf_custom/printf.c ../src/printf_custom/uart_setup.c ../src/push_pull_control/push_pull_ctrl.c ../src/system_mornitor_n_leds/leds.c ../src/system_mornitor_n_leds/system_mornitor.c ../src/main.c

# Pack Options 
PACK_COMMON_OPTIONS=-I "${CMSIS_DIR}/CMSIS/Core/Include"



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

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=PIC32CM1216MC00048
ProjectDir="C:\Users\BUIVIETIEN\Downloads\ups_code(1)\ups_code\pic32cm_pwm\MPLAB_Code\pic32_pwm\pic32cm_pwm.X"
ProjectName=pic32cm_pwm
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\pic32cm_pwm.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="pic32cm_pwm.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif
MDFUHostPath="C:\Program Files\Microchip\MPLABX\v6.25\mplab_platform\mplab-pymdfu\bin\windows\pymdfu-bin.exe"
PYFWImageBuilderPath="C:\Program Files\Microchip\MPLABX\v6.25\mplab_platform\mplab-pymdfu\bin\windows\pyfwimagebuilder-bin.exe"

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/pic32cm_pwm.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
	@echo "--------------------------------------"
	@echo "User defined post-build step: [copy ${ImagePath} ".\lastbuild.${OUTPUT_SUFFIX}"]"
	@copy ${ImagePath} ".\lastbuild.${OUTPUT_SUFFIX}"
	@echo "--------------------------------------"

MP_PROCESSOR_OPTION=32CM1216MC00048
MP_LINKER_FILE_OPTION=,--script="..\..\Demo_code\src\config\default\PIC32CM1216MC00048.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/60163342/plib_adc0.o: ../src/config/default/peripheral/adc/plib_adc0.c  .generated_files/flags/default/874757e404374e851fe0c0f420503456e39cde40 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60163342" 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60163342/plib_adc0.o.d" -o ${OBJECTDIR}/_ext/60163342/plib_adc0.o ../src/config/default/peripheral/adc/plib_adc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60163342/plib_adc1.o: ../src/config/default/peripheral/adc/plib_adc1.c  .generated_files/flags/default/1b640e874318cef40e8d5cfcd75984b1f9b190fd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60163342" 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60163342/plib_adc1.o.d" -o ${OBJECTDIR}/_ext/60163342/plib_adc1.o ../src/config/default/peripheral/adc/plib_adc1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/c2ea0ca9489e5ee2d911cda6d723871398064435 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60166132/plib_dac.o: ../src/config/default/peripheral/dac/plib_dac.c  .generated_files/flags/default/c79ef95b3f6bce0b475ea3fad3baaaad6bbfee42 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60166132" 
	@${RM} ${OBJECTDIR}/_ext/60166132/plib_dac.o.d 
	@${RM} ${OBJECTDIR}/_ext/60166132/plib_dac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60166132/plib_dac.o.d" -o ${OBJECTDIR}/_ext/60166132/plib_dac.o ../src/config/default/peripheral/dac/plib_dac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1985337713/plib_divas.o: ../src/config/default/peripheral/divas/plib_divas.c  .generated_files/flags/default/e7c197db4c186c9553beb6f092eac0c33950ce2a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1985337713" 
	@${RM} ${OBJECTDIR}/_ext/1985337713/plib_divas.o.d 
	@${RM} ${OBJECTDIR}/_ext/1985337713/plib_divas.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1985337713/plib_divas.o.d" -o ${OBJECTDIR}/_ext/1985337713/plib_divas.o ../src/config/default/peripheral/divas/plib_divas.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865161661/plib_dmac.o: ../src/config/default/peripheral/dmac/plib_dmac.c  .generated_files/flags/default/98a1eab822c84d8051533895242625e094557ac3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865161661" 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ../src/config/default/peripheral/dmac/plib_dmac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167341/plib_eic.o: ../src/config/default/peripheral/eic/plib_eic.c  .generated_files/flags/default/2cd6eaa6b976af6bbd506e9c7309aee068ee15f9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60167341" 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167341/plib_eic.o.d" -o ${OBJECTDIR}/_ext/60167341/plib_eic.o ../src/config/default/peripheral/eic/plib_eic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/d3b4efbd2d384644e32994c3a0ed7a2615dbf395 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/fb8eda4336ce4517f1da754411f6edfa00bbecc5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/935e09c6436564a38e64e08aca974f098a291dc6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/823a561aeb33af7de5a9d3334bc5616f7f2ef42a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom1_usart.c  .generated_files/flags/default/9e63fd8d60d2ef287726443215025bfd7b6573b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1827571544/plib_systick.o: ../src/config/default/peripheral/systick/plib_systick.c  .generated_files/flags/default/612bf942faedd3b45f2551dff0251c759d071121 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1827571544" 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1827571544/plib_systick.o.d" -o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ../src/config/default/peripheral/systick/plib_systick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc4.o: ../src/config/default/peripheral/tc/plib_tc4.c  .generated_files/flags/default/4cf084b660e4fff9b228be6419530cea3f099ce7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc4.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ../src/config/default/peripheral/tc/plib_tc4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60181570/plib_tcc0.o: ../src/config/default/peripheral/tcc/plib_tcc0.c  .generated_files/flags/default/bbd2c44cb67071b60bbd69a5d79f17c082b03bde .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181570" 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181570/plib_tcc0.o.d" -o ${OBJECTDIR}/_ext/60181570/plib_tcc0.o ../src/config/default/peripheral/tcc/plib_tcc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60181570/plib_tcc1.o: ../src/config/default/peripheral/tcc/plib_tcc1.c  .generated_files/flags/default/d770139286c0e62cccee10358c11a7109859070d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181570" 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181570/plib_tcc1.o.d" -o ${OBJECTDIR}/_ext/60181570/plib_tcc1.o ../src/config/default/peripheral/tcc/plib_tcc1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60181570/plib_tcc2.o: ../src/config/default/peripheral/tcc/plib_tcc2.c  .generated_files/flags/default/3db2f27270088428f032f5401cf23a2c720176e3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181570" 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181570/plib_tcc2.o.d" -o ${OBJECTDIR}/_ext/60181570/plib_tcc2.o ../src/config/default/peripheral/tcc/plib_tcc2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/beeaa6456bddaed3fe9718a9c15c3d1f8819ad17 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/a5c382fe2951acc22d1c8b8787022a47e4468e80 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/aff3c45e344de9e51854061c9c0c7ca586feb8ac .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/1919afcaa319c1904104dae7d68b1ae6487a1e03 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/7c108b6fc96270dab59e4a2184b53921ffa9a50f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/4fa38827a11bea2a9cf00df9af8c6edb5e1f89e2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1988303524/gcode_command.o: ../src/gcode_parser/gcode_command.c  .generated_files/flags/default/e60d27ee260b8fe79bdb1db754f73aab03809521 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1988303524" 
	@${RM} ${OBJECTDIR}/_ext/1988303524/gcode_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1988303524/gcode_command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1988303524/gcode_command.o.d" -o ${OBJECTDIR}/_ext/1988303524/gcode_command.o ../src/gcode_parser/gcode_command.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1988303524/GCodeParser.o: ../src/gcode_parser/GCodeParser.c  .generated_files/flags/default/e491d209ec63f80205de89f418d8c1d3edb5b5bb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1988303524" 
	@${RM} ${OBJECTDIR}/_ext/1988303524/GCodeParser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1988303524/GCodeParser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1988303524/GCodeParser.o.d" -o ${OBJECTDIR}/_ext/1988303524/GCodeParser.o ../src/gcode_parser/GCodeParser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1330506277/relay.o: ../src/inverter_control/relay.c  .generated_files/flags/default/5e703f2ff17307488d3e0c932a843e9a9833fa6d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1330506277" 
	@${RM} ${OBJECTDIR}/_ext/1330506277/relay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1330506277/relay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1330506277/relay.o.d" -o ${OBJECTDIR}/_ext/1330506277/relay.o ../src/inverter_control/relay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1330506277/spwm.o: ../src/inverter_control/spwm.c  .generated_files/flags/default/478fbc1958f49a8c20524c0a8878aa00689b15b3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1330506277" 
	@${RM} ${OBJECTDIR}/_ext/1330506277/spwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1330506277/spwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1330506277/spwm.o.d" -o ${OBJECTDIR}/_ext/1330506277/spwm.o ../src/inverter_control/spwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1330506277/adc.o: ../src/inverter_control/adc.c  .generated_files/flags/default/c04fa00d6c1ebf1416fe1d8b33d808bfb92112c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1330506277" 
	@${RM} ${OBJECTDIR}/_ext/1330506277/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1330506277/adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1330506277/adc.o.d" -o ${OBJECTDIR}/_ext/1330506277/adc.o ../src/inverter_control/adc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1330506277/sogi_pll.o: ../src/inverter_control/sogi_pll.c  .generated_files/flags/default/945366c905eb900bc40a86a5c56a7521257c8662 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1330506277" 
	@${RM} ${OBJECTDIR}/_ext/1330506277/sogi_pll.o.d 
	@${RM} ${OBJECTDIR}/_ext/1330506277/sogi_pll.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1330506277/sogi_pll.o.d" -o ${OBJECTDIR}/_ext/1330506277/sogi_pll.o ../src/inverter_control/sogi_pll.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1514240246/pid_control.o: ../src/pid_controller/pid_control.c  .generated_files/flags/default/91f1dd486b75dcf303c37deaf6e538658a5f3c8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1514240246" 
	@${RM} ${OBJECTDIR}/_ext/1514240246/pid_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514240246/pid_control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1514240246/pid_control.o.d" -o ${OBJECTDIR}/_ext/1514240246/pid_control.o ../src/pid_controller/pid_control.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1155226525/printf.o: ../src/printf_custom/printf.c  .generated_files/flags/default/e5301741e129c044a2054811282de767f36c36ab .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1155226525" 
	@${RM} ${OBJECTDIR}/_ext/1155226525/printf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1155226525/printf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1155226525/printf.o.d" -o ${OBJECTDIR}/_ext/1155226525/printf.o ../src/printf_custom/printf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1155226525/uart_setup.o: ../src/printf_custom/uart_setup.c  .generated_files/flags/default/45e0e0ce34261c3997548a272aaf53d12e81a77f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1155226525" 
	@${RM} ${OBJECTDIR}/_ext/1155226525/uart_setup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1155226525/uart_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1155226525/uart_setup.o.d" -o ${OBJECTDIR}/_ext/1155226525/uart_setup.o ../src/printf_custom/uart_setup.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o: ../src/push_pull_control/push_pull_ctrl.c  .generated_files/flags/default/f87b45e5be751914c1b58b185436721817658bb7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1915239442" 
	@${RM} ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o.d" -o ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o ../src/push_pull_control/push_pull_ctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1580483562/leds.o: ../src/system_mornitor_n_leds/leds.c  .generated_files/flags/default/21186246ff294562daaee55617590b9d7b1e0334 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1580483562" 
	@${RM} ${OBJECTDIR}/_ext/1580483562/leds.o.d 
	@${RM} ${OBJECTDIR}/_ext/1580483562/leds.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1580483562/leds.o.d" -o ${OBJECTDIR}/_ext/1580483562/leds.o ../src/system_mornitor_n_leds/leds.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1580483562/system_mornitor.o: ../src/system_mornitor_n_leds/system_mornitor.c  .generated_files/flags/default/584f8f6fceb5be39c137ddc32a4d006c4cd589a8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1580483562" 
	@${RM} ${OBJECTDIR}/_ext/1580483562/system_mornitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1580483562/system_mornitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1580483562/system_mornitor.o.d" -o ${OBJECTDIR}/_ext/1580483562/system_mornitor.o ../src/system_mornitor_n_leds/system_mornitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/375e268f58b458d5796a751fe5b8dd4ef0fdb792 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
else
${OBJECTDIR}/_ext/60163342/plib_adc0.o: ../src/config/default/peripheral/adc/plib_adc0.c  .generated_files/flags/default/e3e8c1968b706330ff983153f1b4be192a9536fc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60163342" 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60163342/plib_adc0.o.d" -o ${OBJECTDIR}/_ext/60163342/plib_adc0.o ../src/config/default/peripheral/adc/plib_adc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60163342/plib_adc1.o: ../src/config/default/peripheral/adc/plib_adc1.c  .generated_files/flags/default/5c9c5aba7ac4705f99f65e072aaf686d86931d63 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60163342" 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60163342/plib_adc1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60163342/plib_adc1.o.d" -o ${OBJECTDIR}/_ext/60163342/plib_adc1.o ../src/config/default/peripheral/adc/plib_adc1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1984496892/plib_clock.o: ../src/config/default/peripheral/clock/plib_clock.c  .generated_files/flags/default/29c73ef438f8757ce3904a19f1b7a2695674a1b6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1984496892" 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o.d 
	@${RM} ${OBJECTDIR}/_ext/1984496892/plib_clock.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1984496892/plib_clock.o.d" -o ${OBJECTDIR}/_ext/1984496892/plib_clock.o ../src/config/default/peripheral/clock/plib_clock.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60166132/plib_dac.o: ../src/config/default/peripheral/dac/plib_dac.c  .generated_files/flags/default/1cac4cdf89c76a9348ab9603834ac929e01eefc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60166132" 
	@${RM} ${OBJECTDIR}/_ext/60166132/plib_dac.o.d 
	@${RM} ${OBJECTDIR}/_ext/60166132/plib_dac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60166132/plib_dac.o.d" -o ${OBJECTDIR}/_ext/60166132/plib_dac.o ../src/config/default/peripheral/dac/plib_dac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1985337713/plib_divas.o: ../src/config/default/peripheral/divas/plib_divas.c  .generated_files/flags/default/9e8da855e7594459cec82f5c298bff0063d4f1c5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1985337713" 
	@${RM} ${OBJECTDIR}/_ext/1985337713/plib_divas.o.d 
	@${RM} ${OBJECTDIR}/_ext/1985337713/plib_divas.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1985337713/plib_divas.o.d" -o ${OBJECTDIR}/_ext/1985337713/plib_divas.o ../src/config/default/peripheral/divas/plib_divas.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865161661/plib_dmac.o: ../src/config/default/peripheral/dmac/plib_dmac.c  .generated_files/flags/default/94a37f0220b545e611f58c109c3b2b42d2a7b60f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865161661" 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865161661/plib_dmac.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865161661/plib_dmac.o.d" -o ${OBJECTDIR}/_ext/1865161661/plib_dmac.o ../src/config/default/peripheral/dmac/plib_dmac.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60167341/plib_eic.o: ../src/config/default/peripheral/eic/plib_eic.c  .generated_files/flags/default/987420e4438c709e18aa9a612f438b3ccac58985 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60167341" 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o.d 
	@${RM} ${OBJECTDIR}/_ext/60167341/plib_eic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60167341/plib_eic.o.d" -o ${OBJECTDIR}/_ext/60167341/plib_eic.o ../src/config/default/peripheral/eic/plib_eic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1986646378/plib_evsys.o: ../src/config/default/peripheral/evsys/plib_evsys.c  .generated_files/flags/default/767e274d9a6bbc8505e18e552ceba4847f2978a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1986646378" 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d 
	@${RM} ${OBJECTDIR}/_ext/1986646378/plib_evsys.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1986646378/plib_evsys.o.d" -o ${OBJECTDIR}/_ext/1986646378/plib_evsys.o ../src/config/default/peripheral/evsys/plib_evsys.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865468468/plib_nvic.o: ../src/config/default/peripheral/nvic/plib_nvic.c  .generated_files/flags/default/9dc6e0a2b08b5d102f5a1dedab0bbe64c9220db4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865468468" 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865468468/plib_nvic.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865468468/plib_nvic.o.d" -o ${OBJECTDIR}/_ext/1865468468/plib_nvic.o ../src/config/default/peripheral/nvic/plib_nvic.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o: ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c  .generated_files/flags/default/81ed7f9911dc309390347083d6e834b1880adbcc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1593096446" 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o.d" -o ${OBJECTDIR}/_ext/1593096446/plib_nvmctrl.o ../src/config/default/peripheral/nvmctrl/plib_nvmctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1865521619/plib_port.o: ../src/config/default/peripheral/port/plib_port.c  .generated_files/flags/default/5797c9562ac71ce36045238b350025bd1aec590d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1865521619" 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o.d 
	@${RM} ${OBJECTDIR}/_ext/1865521619/plib_port.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1865521619/plib_port.o.d" -o ${OBJECTDIR}/_ext/1865521619/plib_port.o ../src/config/default/peripheral/port/plib_port.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o: ../src/config/default/peripheral/sercom/usart/plib_sercom1_usart.c  .generated_files/flags/default/8810601360baca5c536d5e26c6f626a6f0e8dfda .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/504274921" 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o.d" -o ${OBJECTDIR}/_ext/504274921/plib_sercom1_usart.o ../src/config/default/peripheral/sercom/usart/plib_sercom1_usart.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1827571544/plib_systick.o: ../src/config/default/peripheral/systick/plib_systick.c  .generated_files/flags/default/7f063fcdeeebae461e549c6d9fb12bf7a1fc7213 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1827571544" 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o.d 
	@${RM} ${OBJECTDIR}/_ext/1827571544/plib_systick.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1827571544/plib_systick.o.d" -o ${OBJECTDIR}/_ext/1827571544/plib_systick.o ../src/config/default/peripheral/systick/plib_systick.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/829342655/plib_tc4.o: ../src/config/default/peripheral/tc/plib_tc4.c  .generated_files/flags/default/a6f6c6d13233c729ac5b07f42a3479aee1498b8a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/829342655" 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o.d 
	@${RM} ${OBJECTDIR}/_ext/829342655/plib_tc4.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/829342655/plib_tc4.o.d" -o ${OBJECTDIR}/_ext/829342655/plib_tc4.o ../src/config/default/peripheral/tc/plib_tc4.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60181570/plib_tcc0.o: ../src/config/default/peripheral/tcc/plib_tcc0.c  .generated_files/flags/default/8f21c65b1aabe4ab45603f5a366058355a87c307 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181570" 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc0.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc0.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181570/plib_tcc0.o.d" -o ${OBJECTDIR}/_ext/60181570/plib_tcc0.o ../src/config/default/peripheral/tcc/plib_tcc0.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60181570/plib_tcc1.o: ../src/config/default/peripheral/tcc/plib_tcc1.c  .generated_files/flags/default/86f34814592077acfbb96a8f83ea37485bd860c3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181570" 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc1.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc1.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181570/plib_tcc1.o.d" -o ${OBJECTDIR}/_ext/60181570/plib_tcc1.o ../src/config/default/peripheral/tcc/plib_tcc1.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/60181570/plib_tcc2.o: ../src/config/default/peripheral/tcc/plib_tcc2.c  .generated_files/flags/default/5959e31ad8f11109af922955b9332871157a9fd8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/60181570" 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc2.o.d 
	@${RM} ${OBJECTDIR}/_ext/60181570/plib_tcc2.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/60181570/plib_tcc2.o.d" -o ${OBJECTDIR}/_ext/60181570/plib_tcc2.o ../src/config/default/peripheral/tcc/plib_tcc2.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/163028504/xc32_monitor.o: ../src/config/default/stdio/xc32_monitor.c  .generated_files/flags/default/b13a25189311ba72ee6c3b5fab904549c91ecf6e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/163028504" 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/163028504/xc32_monitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/163028504/xc32_monitor.o.d" -o ${OBJECTDIR}/_ext/163028504/xc32_monitor.o ../src/config/default/stdio/xc32_monitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/initialization.o: ../src/config/default/initialization.c  .generated_files/flags/default/208648c4f590ba3b6e7370ef8556d53280a75e53 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/initialization.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/initialization.o.d" -o ${OBJECTDIR}/_ext/1171490990/initialization.o ../src/config/default/initialization.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/interrupts.o: ../src/config/default/interrupts.c  .generated_files/flags/default/e3a0bcc732bd4615a771f71fe13b170edad42512 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/interrupts.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/interrupts.o.d" -o ${OBJECTDIR}/_ext/1171490990/interrupts.o ../src/config/default/interrupts.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/libc_syscalls.o: ../src/config/default/libc_syscalls.c  .generated_files/flags/default/b50cc3e666c9157432825919d1c19f516185a2cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/libc_syscalls.o.d" -o ${OBJECTDIR}/_ext/1171490990/libc_syscalls.o ../src/config/default/libc_syscalls.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/exceptions.o: ../src/config/default/exceptions.c  .generated_files/flags/default/fca6f63c96811301320bd59972d3892b51af15c6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/exceptions.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/exceptions.o.d" -o ${OBJECTDIR}/_ext/1171490990/exceptions.o ../src/config/default/exceptions.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1171490990/startup_xc32.o: ../src/config/default/startup_xc32.c  .generated_files/flags/default/dc0f96cec2aa9242d199ed3cdd3bedefda7cfde3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1171490990" 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d 
	@${RM} ${OBJECTDIR}/_ext/1171490990/startup_xc32.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1171490990/startup_xc32.o.d" -o ${OBJECTDIR}/_ext/1171490990/startup_xc32.o ../src/config/default/startup_xc32.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1988303524/gcode_command.o: ../src/gcode_parser/gcode_command.c  .generated_files/flags/default/31ccc19e1a5be30b537ca783fa587ce422ec2ca8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1988303524" 
	@${RM} ${OBJECTDIR}/_ext/1988303524/gcode_command.o.d 
	@${RM} ${OBJECTDIR}/_ext/1988303524/gcode_command.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1988303524/gcode_command.o.d" -o ${OBJECTDIR}/_ext/1988303524/gcode_command.o ../src/gcode_parser/gcode_command.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1988303524/GCodeParser.o: ../src/gcode_parser/GCodeParser.c  .generated_files/flags/default/1ca702fda81462c4bf3a27c4892b0bb9d7ea88e7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1988303524" 
	@${RM} ${OBJECTDIR}/_ext/1988303524/GCodeParser.o.d 
	@${RM} ${OBJECTDIR}/_ext/1988303524/GCodeParser.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1988303524/GCodeParser.o.d" -o ${OBJECTDIR}/_ext/1988303524/GCodeParser.o ../src/gcode_parser/GCodeParser.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1330506277/relay.o: ../src/inverter_control/relay.c  .generated_files/flags/default/c09a85582aa0d2caa5730e9f9624a6adb5f489a3 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1330506277" 
	@${RM} ${OBJECTDIR}/_ext/1330506277/relay.o.d 
	@${RM} ${OBJECTDIR}/_ext/1330506277/relay.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1330506277/relay.o.d" -o ${OBJECTDIR}/_ext/1330506277/relay.o ../src/inverter_control/relay.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1330506277/spwm.o: ../src/inverter_control/spwm.c  .generated_files/flags/default/d22a32b080fdd577c96b584e14be4d551a4c1437 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1330506277" 
	@${RM} ${OBJECTDIR}/_ext/1330506277/spwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1330506277/spwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1330506277/spwm.o.d" -o ${OBJECTDIR}/_ext/1330506277/spwm.o ../src/inverter_control/spwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1330506277/adc.o: ../src/inverter_control/adc.c  .generated_files/flags/default/aa0e08b50d1d562cf4d1ac14dbb8fa15630bee68 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1330506277" 
	@${RM} ${OBJECTDIR}/_ext/1330506277/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/1330506277/adc.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1330506277/adc.o.d" -o ${OBJECTDIR}/_ext/1330506277/adc.o ../src/inverter_control/adc.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1330506277/sogi_pll.o: ../src/inverter_control/sogi_pll.c  .generated_files/flags/default/d61389c8be2c18f421a859332733301c067fa4dd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1330506277" 
	@${RM} ${OBJECTDIR}/_ext/1330506277/sogi_pll.o.d 
	@${RM} ${OBJECTDIR}/_ext/1330506277/sogi_pll.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1330506277/sogi_pll.o.d" -o ${OBJECTDIR}/_ext/1330506277/sogi_pll.o ../src/inverter_control/sogi_pll.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1514240246/pid_control.o: ../src/pid_controller/pid_control.c  .generated_files/flags/default/3ad325691f74121a62cec1327bb1753e8906851b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1514240246" 
	@${RM} ${OBJECTDIR}/_ext/1514240246/pid_control.o.d 
	@${RM} ${OBJECTDIR}/_ext/1514240246/pid_control.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1514240246/pid_control.o.d" -o ${OBJECTDIR}/_ext/1514240246/pid_control.o ../src/pid_controller/pid_control.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1155226525/printf.o: ../src/printf_custom/printf.c  .generated_files/flags/default/8e69bd69b1760e855459ef1d9d2296a75adcb31 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1155226525" 
	@${RM} ${OBJECTDIR}/_ext/1155226525/printf.o.d 
	@${RM} ${OBJECTDIR}/_ext/1155226525/printf.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1155226525/printf.o.d" -o ${OBJECTDIR}/_ext/1155226525/printf.o ../src/printf_custom/printf.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1155226525/uart_setup.o: ../src/printf_custom/uart_setup.c  .generated_files/flags/default/276196f30048dccc722f4d3f1759cd799ae00ed9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1155226525" 
	@${RM} ${OBJECTDIR}/_ext/1155226525/uart_setup.o.d 
	@${RM} ${OBJECTDIR}/_ext/1155226525/uart_setup.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1155226525/uart_setup.o.d" -o ${OBJECTDIR}/_ext/1155226525/uart_setup.o ../src/printf_custom/uart_setup.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o: ../src/push_pull_control/push_pull_ctrl.c  .generated_files/flags/default/3fe315e1f5fc3cb0634362bf42ebc88d422144ae .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1915239442" 
	@${RM} ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o.d 
	@${RM} ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o.d" -o ${OBJECTDIR}/_ext/1915239442/push_pull_ctrl.o ../src/push_pull_control/push_pull_ctrl.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1580483562/leds.o: ../src/system_mornitor_n_leds/leds.c  .generated_files/flags/default/cf6d1c5d23da39abe585f6150d034d75c12c01d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1580483562" 
	@${RM} ${OBJECTDIR}/_ext/1580483562/leds.o.d 
	@${RM} ${OBJECTDIR}/_ext/1580483562/leds.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1580483562/leds.o.d" -o ${OBJECTDIR}/_ext/1580483562/leds.o ../src/system_mornitor_n_leds/leds.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1580483562/system_mornitor.o: ../src/system_mornitor_n_leds/system_mornitor.c  .generated_files/flags/default/b08234ec814df61439f14fa71f7eab55be4d6316 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1580483562" 
	@${RM} ${OBJECTDIR}/_ext/1580483562/system_mornitor.o.d 
	@${RM} ${OBJECTDIR}/_ext/1580483562/system_mornitor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1580483562/system_mornitor.o.d" -o ${OBJECTDIR}/_ext/1580483562/system_mornitor.o ../src/system_mornitor_n_leds/system_mornitor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
${OBJECTDIR}/_ext/1360937237/main.o: ../src/main.c  .generated_files/flags/default/62d6ca4f9cf1439687512ac74e307fff7515b2d7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/1360937237" 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1360937237/main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -ffunction-sections -fdata-sections -O1 -fno-common -I"../src" -I"../src/config/default" -I"../src/packs/CMSIS/" -I"../src/packs/CMSIS/CMSIS/Core/Include" -I"../src/packs/CMSIS/CMSIS/DSP/Include/" -I"../src/packs/PIC32CM1216MC00048_DFP" -I"../src/gcode_parser" -I"../src/sine_wave" -Wall -MP -MMD -MF "${OBJECTDIR}/_ext/1360937237/main.o.d" -o ${OBJECTDIR}/_ext/1360937237/main.o ../src/main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}/PIC32CM1216MC00048" ${PACK_COMMON_OPTIONS} 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/pic32cm_pwm.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../Demo_code/src/config/default/PIC32CM1216MC00048.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/pic32cm_pwm.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/PIC32CM1216MC00048"
	
else
${DISTDIR}/pic32cm_pwm.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../Demo_code/src/config/default/PIC32CM1216MC00048.ld
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -mno-device-startup-code -o ${DISTDIR}/pic32cm_pwm.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=512,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}/PIC32CM1216MC00048"
	${MP_CC_DIR}\\xc32-bin2hex ${DISTDIR}/pic32cm_pwm.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
