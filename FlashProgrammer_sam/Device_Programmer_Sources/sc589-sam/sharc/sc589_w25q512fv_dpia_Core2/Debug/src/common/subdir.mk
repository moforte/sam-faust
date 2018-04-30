################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/common/flash.c \
C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/common/gpio_simple.c \
C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/common/simple_sysctrl.c \
C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/common/spi.c 

SRC_OBJS += \
./src/common/flash.doj \
./src/common/gpio_simple.doj \
./src/common/simple_sysctrl.doj \
./src/common/spi.doj 

C_DEPS += \
./src/common/flash.d \
./src/common/gpio_simple.d \
./src/common/simple_sysctrl.d \
./src/common/spi.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/flash.doj: C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/common/flash.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="w25ql512fv_dpia_SC589_SHARC_Core2" -proc ADSP-SC589 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -I"C:\Users\Dan\Dropbox\Projects\ADI002 - SS Frameworks\Software\New Frameworks\utilities\FlashProgrammer_SAM\Device_Programmer_Sources\sc589-sam\sharc\sc589_w25q512fv_dpia_Core2\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -absolute-path-dependencies -gnu-style-dependencies -MD -Mo "src/common/flash.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/common/gpio_simple.doj: C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/common/gpio_simple.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="w25ql512fv_dpia_SC589_SHARC_Core2" -proc ADSP-SC589 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -I"C:\Users\Dan\Dropbox\Projects\ADI002 - SS Frameworks\Software\New Frameworks\utilities\FlashProgrammer_SAM\Device_Programmer_Sources\sc589-sam\sharc\sc589_w25q512fv_dpia_Core2\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -absolute-path-dependencies -gnu-style-dependencies -MD -Mo "src/common/gpio_simple.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/common/simple_sysctrl.doj: C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/common/simple_sysctrl.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="w25ql512fv_dpia_SC589_SHARC_Core2" -proc ADSP-SC589 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -I"C:\Users\Dan\Dropbox\Projects\ADI002 - SS Frameworks\Software\New Frameworks\utilities\FlashProgrammer_SAM\Device_Programmer_Sources\sc589-sam\sharc\sc589_w25q512fv_dpia_Core2\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -absolute-path-dependencies -gnu-style-dependencies -MD -Mo "src/common/simple_sysctrl.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/common/spi.doj: C:/Users/Dan/Dropbox/Projects/ADI002\ -\ SS\ Frameworks/Software/New\ Frameworks/utilities/FlashProgrammer_SAM/Device_Programmer_Sources/common/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore SHARC C/C++ Compiler'
	cc21k.exe -c -file-attr ProjectName="w25ql512fv_dpia_SC589_SHARC_Core2" -proc ADSP-SC589 -flags-compiler --no_wrap_diagnostics -si-revision any -g -DCORE2 -D_DEBUG -I"C:\Users\Dan\Dropbox\Projects\ADI002 - SS Frameworks\Software\New Frameworks\utilities\FlashProgrammer_SAM\Device_Programmer_Sources\sc589-sam\sharc\sc589_w25q512fv_dpia_Core2\system" -structs-do-not-overlap -no-const-strings -no-multiline -warn-protos -double-size-32 -char-size-8 -swc -absolute-path-dependencies -gnu-style-dependencies -MD -Mo "src/common/spi.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


