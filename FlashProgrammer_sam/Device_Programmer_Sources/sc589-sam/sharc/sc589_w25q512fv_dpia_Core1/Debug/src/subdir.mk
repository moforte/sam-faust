################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/sc589_mt25ql512fv_dpia.c 

SRC_OBJS += \
./src/sc589_mt25ql512fv_dpia.doj 

C_DEPS += \
./src/sc589_mt25ql512fv_dpia.d 


# Each subdirectory must supply rules for building sources it contributes
src/sc589_mt25ql512fv_dpia.doj: C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/sc589_mt25ql512fv_dpia.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="w25ql512fv_dpia_SC589_SHARC_Core1" -proc ADSP-SC589 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE1 -D_DEBUG -I"C:\Users\Dan\Dropbox\Projects\ADI002 - SS Frameworks\Software\New Frameworks\utilities\FlashProgrammer_SAM\Device_Programmer_Sources\sc589-sam\sharc\sc589_w25q512fv_dpia_Core1\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -absolute-path-dependencies -gnu-style-dependencies -MD -Mo "src/sc589_mt25ql512fv_dpia.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


