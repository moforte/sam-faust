################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sc589_w25q128fv_dpia_Core0.cpp 

SRC_OBJS += \
./src/sc589_w25q128fv_dpia_Core0.o 

CPP_DEPS += \
./src/sc589_w25q128fv_dpia_Core0.d 


# Each subdirectory must supply rules for building sources it contributes
src/sc589_w25q128fv_dpia_Core0.o: ../src/sc589_w25q128fv_dpia_Core0.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore ARM Bare Metal C++ Compiler'
	arm-none-eabi-g++ -g -gdwarf-2 -ffunction-sections -fdata-sections -DCORE0 -D_DEBUG -I"C:\Users\Dan\Dropbox\Projects\ADI002 - SS Frameworks\Software\New Frameworks\utilities\FlashProgrammer_SAM\Device_Programmer_Sources\sc589-sam\sharc\sc589_w25q512fv_dpia_Core0\system" -Wall -c -mproc=ADSP-SC589 -msi-revision=any -MMD -MP -MF"src/sc589_w25q128fv_dpia_Core0.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


