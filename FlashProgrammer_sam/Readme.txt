To make this work:

#1 - Add "C:\Analog Devices\CrossCore Embedded Studio 2.5.0\" to windows path so elfloader can be called without the path (windows 10 balks at this)
#2 - Append a .exe to the end of the core 0/ARM executable
#3 - Copy your DXE/EXE files into the sam_Input_DXE_Files directory
#4 - Run this Prog_sam_flash command with the root name of your DXE/EXE files as the argument.
     For example, if your DXE is SHARC_App_Core0 the root name is SHARC_App


