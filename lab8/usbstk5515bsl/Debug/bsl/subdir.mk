################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsl/usbstk5515.c \
../bsl/usbstk5515_gpio.c \
../bsl/usbstk5515_i2c.c \
../bsl/usbstk5515_led.c 

OBJS += \
./bsl/usbstk5515.obj \
./bsl/usbstk5515_gpio.obj \
./bsl/usbstk5515_i2c.obj \
./bsl/usbstk5515_led.obj 

C_DEPS += \
./bsl/usbstk5515.pp \
./bsl/usbstk5515_gpio.pp \
./bsl/usbstk5515_i2c.pp \
./bsl/usbstk5515_led.pp 

OBJS__QTD += \
".\bsl\usbstk5515.obj" \
".\bsl\usbstk5515_gpio.obj" \
".\bsl\usbstk5515_i2c.obj" \
".\bsl\usbstk5515_led.obj" 

C_DEPS__QTD += \
".\bsl\usbstk5515.pp" \
".\bsl\usbstk5515_gpio.pp" \
".\bsl\usbstk5515_i2c.pp" \
".\bsl\usbstk5515_led.pp" 

C_SRCS_QUOTED += \
"../bsl/usbstk5515.c" \
"../bsl/usbstk5515_gpio.c" \
"../bsl/usbstk5515_i2c.c" \
"../bsl/usbstk5515_led.c" 


# Each subdirectory must supply rules for building sources it contributes
bsl/usbstk5515.obj: ../bsl/usbstk5515.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Texas Instruments/ccsv4/include" --include_path="C:/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --diag_warning=225 --ptrdiff_size=16 --memory_model=small --preproc_with_compile --preproc_dependency="bsl/usbstk5515.pp" --obj_directory="bsl" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

bsl/usbstk5515_gpio.obj: ../bsl/usbstk5515_gpio.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Texas Instruments/ccsv4/include" --include_path="C:/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --diag_warning=225 --ptrdiff_size=16 --memory_model=small --preproc_with_compile --preproc_dependency="bsl/usbstk5515_gpio.pp" --obj_directory="bsl" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

bsl/usbstk5515_i2c.obj: ../bsl/usbstk5515_i2c.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Texas Instruments/ccsv4/include" --include_path="C:/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --diag_warning=225 --ptrdiff_size=16 --memory_model=small --preproc_with_compile --preproc_dependency="bsl/usbstk5515_i2c.pp" --obj_directory="bsl" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

bsl/usbstk5515_led.obj: ../bsl/usbstk5515_led.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files (x86)/Texas Instruments/ccsv4/tools/compiler/c5500/bin/cl55" -vcpu:3.3 -g --include_path="C:/Texas Instruments/ccsv4/include" --include_path="C:/Texas Instruments/ccsv4/tools/compiler/c5500/include" --include_path="C:/Texas Instruments/ccsv4/emulation/boards/usbstk5515_v1/include" --diag_warning=225 --ptrdiff_size=16 --memory_model=small --preproc_with_compile --preproc_dependency="bsl/usbstk5515_led.pp" --obj_directory="bsl" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


