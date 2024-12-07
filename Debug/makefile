################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./ECU_Layer/DC_MOTOR/DC_MOTOR.obj" \
"./ECU_Layer/LCD/LCD.obj" \
"./ECU_Layer/LM35/LM35.obj" \
"./ECU_Layer/PUSH_BUTTONS/PUSH_BUTTONS.obj" \
"./MCAL_Layer/ADC/ADC.obj" \
"./MCAL_Layer/EEPROM/EEPROM.obj" \
"./MCAL_Layer/GPIO/GPIO.obj" \
"./MCAL_Layer/INTERRUPT/INTERRUPT.obj" \
"./MCAL_Layer/SYSTICK_TIMER/SYSTICK_TIMER.obj" \
"./MCAL_Layer/UART/UART.obj" \
"../tm4c123gh6pm.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include ECU_Layer/DC_MOTOR/subdir_vars.mk
-include ECU_Layer/LCD/subdir_vars.mk
-include ECU_Layer/LM35/subdir_vars.mk
-include ECU_Layer/PUSH_BUTTONS/subdir_vars.mk
-include MCAL_Layer/ADC/subdir_vars.mk
-include MCAL_Layer/EEPROM/subdir_vars.mk
-include MCAL_Layer/GPIO/subdir_vars.mk
-include MCAL_Layer/INTERRUPT/subdir_vars.mk
-include MCAL_Layer/SYSTICK_TIMER/subdir_vars.mk
-include MCAL_Layer/UART/subdir_vars.mk
-include subdir_rules.mk
-include ECU_Layer/DC_MOTOR/subdir_rules.mk
-include ECU_Layer/LCD/subdir_rules.mk
-include ECU_Layer/LM35/subdir_rules.mk
-include ECU_Layer/PUSH_BUTTONS/subdir_rules.mk
-include MCAL_Layer/ADC/subdir_rules.mk
-include MCAL_Layer/EEPROM/subdir_rules.mk
-include MCAL_Layer/GPIO/subdir_rules.mk
-include MCAL_Layer/INTERRUPT/subdir_rules.mk
-include MCAL_Layer/SYSTICK_TIMER/subdir_rules.mk
-include MCAL_Layer/UART/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Vehicle_Fault_Detection_and_Logging_System.out 

EXE_OUTPUTS__QUOTED += \
"Vehicle_Fault_Detection_and_Logging_System.out" 


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Vehicle_Fault_Detection_and_Logging_System.out"

# Tool invocations
Vehicle_Fault_Detection_and_Logging_System.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Vehicle_Fault_Detection_and_Logging_System.map" --heap_size=0 --stack_size=512 -i"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" -i"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Vehicle_Fault_Detection_and_Logging_System_linkInfo.xml" --rom_model -o "Vehicle_Fault_Detection_and_Logging_System.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c123gh6pm_startup_ccs.obj" "ECU_Layer\DC_MOTOR\DC_MOTOR.obj" "ECU_Layer\LCD\LCD.obj" "ECU_Layer\LM35\LM35.obj" "ECU_Layer\PUSH_BUTTONS\PUSH_BUTTONS.obj" "MCAL_Layer\ADC\ADC.obj" "MCAL_Layer\EEPROM\EEPROM.obj" "MCAL_Layer\GPIO\GPIO.obj" "MCAL_Layer\INTERRUPT\INTERRUPT.obj" "MCAL_Layer\SYSTICK_TIMER\SYSTICK_TIMER.obj" "MCAL_Layer\UART\UART.obj" 
	-$(RM) "main.d" "tm4c123gh6pm_startup_ccs.d" "ECU_Layer\DC_MOTOR\DC_MOTOR.d" "ECU_Layer\LCD\LCD.d" "ECU_Layer\LM35\LM35.d" "ECU_Layer\PUSH_BUTTONS\PUSH_BUTTONS.d" "MCAL_Layer\ADC\ADC.d" "MCAL_Layer\EEPROM\EEPROM.d" "MCAL_Layer\GPIO\GPIO.d" "MCAL_Layer\INTERRUPT\INTERRUPT.d" "MCAL_Layer\SYSTICK_TIMER\SYSTICK_TIMER.d" "MCAL_Layer\UART\UART.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

