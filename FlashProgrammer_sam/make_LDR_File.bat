@echo off
if [%1]==[] goto usage

IF NOT EXIST sam_Input_DXE_Files\%1_Core0.exe (
@echo The specified input file does not exist: sam_Input_DXE_Files\%1_Core0.exe
@echo. 
@echo Be sure to copy the DXE files into the sam_Input_DXE_Files/ directory
) ELSE (
elfloader.exe -proc ADSP-SC589 -core0=sam_Input_DXE_Files/%1_Core0.exe -init Supporting_Files/ezkitSC589_initcode_core0_v10 -core1=sam_Input_DXE_Files/%1_Core1.dxe  -core2=sam_Input_DXE_Files/%1_Core2.dxe  -NoFinalTag=sam_Input_DXE_Files/%1_Core0.exe -NoFinalTag=sam_Input_DXE_Files/%1_Core1.dxe -b SPI -f BINARY -verbose -Width 8 -bcode 0x1 -o sam_Output_LDR_Files/%1-SC589.ldr

@echo Done!
goto :eof
)

:usage
@echo sam Flash Programming Utility
@echo Copy your 3 DXE files into the sam_Input_DXE_Files directory 
@echo The first argument of this script should be the root name of your DXE (e.g. if your DXE is SHARC_App_Core0 the root name is SHARC_App) 
@echo Example: Prog_sam_flash.bat SS_App_sam
@echo Example: Prog_sam_flash.bat SS_App_sam_Automotive
@echo This script is designed to be used with the ICE 2000


