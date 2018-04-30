To make this work:

#1 - Add "C:\Analog Devices\CrossCore Embedded Studio 2.5.0\" to windows path so elfloader can be called without the path (windows 10 balks at this)
#2 - Append a .exe to the end of the core 0/ARM executable
#3 - Paste this command the command line

elfloader.exe -proc ADSP-SC589 -core0=SS_App_Core0.exe -init ezkitSC589_initcode_core0_v10 -core1=SS_App_Core1.dxe  -core2=SS_App_Core2.dxe  -NoFinalTag=SS_App_Core0.exe -NoFinalTag=SS_App_Core1.dxe -b SPI -f BINARY -Width 8 -bcode 0x1 -verbose -o SS_App-SC589.ldr

Flash_ADSPSC5xx.bat 589 2000 SAM_DXEs\SS_App-SC589.ldr