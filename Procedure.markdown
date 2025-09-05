# How to set up working environment for IERG3810  
## Step 1. Install **ARM-MDK v5.15** (Compiler and Development Tool)  
- Download website [ARM-MDK]("https://personal.ie.cuhk.edu.hk/~whsiu/Downloads/MDK515.EXE")  
- Set Destination Folders  
- Enter information and press "Next"  
- Start Installation  
- Finally, a Pack Installer will be open automatically.  

## Step 2. Import **Keil.STM32F1xx_DFP.2.4.0** (Device Patch)
- Download "Keil.STM32F1xx_DFP.2.4.0.pack" from blackboard-Reference Folder-Program and Drivers  
- Click File-Import on the left upper corner, Select the downloaded file and wait.  
- Ignore the errors during downloading. When downloading finished, you can find 
STM32F103ZE in STMicroelectronics (you will find a lot more Devices)  

## Step 3. Download Firmware library  
Firmware Libraries are a set of pre-written code specifically provided for microcontrollers (MCUs) or embedded systems. They simplify the use of hardware peripherals, allowing you to control various chip functions without having to directly manipulate complex registers.
<br><br>
- Download **STSW-STM32054.zip** from [Firmware Library]("http://www.st.com/web/en/catalog/tools/FM147/CL1794/SC961/SS1743/LN1734/PF257890?s_searchtype=keyword")   
- You need to select version 3.5.0 and use your email to download as guest.  
- An verify email will be sent to your email address. Click download botton in that email and get the zip file.  
- decompress the library file  

## Step 4. Create Empty Local Project File  
To  manage the files, it is recommended to put all experience files in User (refer to Page 68 choice two in the Tool-slide)  
<br><br>
- Create a folder with **Board**, **Core**, **Fw_lib**, **Listings**, **Objects**, **User** folders.  
-  Copy the basic files from STM32F10x_StdPeriph_Driver to your project.
- Copy the following files to "Your File"\Core\
 ```..\Libraries\CMSIS\CM3\CoreSupport\core_cm3.c
 ..\Libraries\CMSIS\CM3\CoreSupport\core_cm3.h
 ..\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\stm32f10x.h
 ..\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\system_stm32f10x.h
 ..\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\system_stm32f10x.c
 ..\Libraries\CMSIS\CM3\DeviceSupport\ST\STM32F10x\startup\arm\startup_stm32f10x_hd.s
```
- Copy both folders 'inc' and  'src' that are under STM32F10x_StdPeriph_Driver to "Your File"\Fw_lib\.  
- Create a file named Exp0.c under lab-1\User\.  
- Copy three files, stm32f10x_conf.h, stm32f10x_it.c, stm32f10x_it.h
 from ..\STM32F10x_StdPeriph_Lib_V3.5.0\Project\STM32F10x_StdPeriph_Template to 
"Your File"\User\.  

## Step 5. Start the project on KEIL uVision  
### a. create an empty project  
- Open KEIL uVision on desktop  
- Click **Project** in Menu -> new uVision Project -> go into "Your File" -> set file name to **st12345** -> save -> find **STM32F103ZE** in left bottom window -> select and click OK -> Click OK and ignore the warning message -> Click OK  
- Click the three colors squares on the second line of icons -> create "Fw_lib","Core","Board","User" folders in group 
- Add all .c files from Fw_lib to Fw_lib
- Include .c and .s files into Core separately (need to change the Files of type to Asm Source file(\*.s\*,\*.src;\*.a\*) and C Source file(\*.c)) 
- Include stm32f10x_it.c and Exp0.c in User
- Click OK

### b. change target options 
- Click the icon right on the right side of **Target 1** in Menu
- Set Xtal to 8MHz
- In Output tab, click 'Select Folder for Object...' select 'Objects' folder that your created.
- Keil will generate a lot of files during compiling. Let them stored into your 'Objects' folder.
- Modify the executable file name with a prefix '_'. It will help you find the file easier.
- Tick 'Create HEX File'. This is the executable file of your project
- In Listing tab, click 'Select Folder for Objects...' select 'Listings' folder that your created
- Enter "USE_STDPERIPH_DRIVER, STM32F10X_HD" in Define 
- Enter ".\Board",".\Core",".\Fw_lib\inc",".\User"
- Click OK

### c. Start coding
```c
#include "stm32f10x.h"
int main(void)
{
    while(1)
    ;
}
// copy code in Exp0.c
```
- click the **build** icon (second one on the second line of icons)  
- should have 0 errors and 0 warnings 
- When you do Exp-1.1; Keep Exp0.c; Copy Exp0.c to Exp1.1.c; Modify Exp1.1.c 

### d. Download CH341SER
- Download [CH341SER.ZIP]("https://blackboard.cuhk.edu.hk/bbcswebdav/pid-6184550-dt-content-rid-96358896_1/xid-96358896_1") from blackboard-Reference Folder-Program
- decompress the .zip file
- Find **\CH341SER\CH341SER\SETUP.EXE**, double click to install
<br><br>
**Important:** you will not see the USB-SERIAL CH340 (COM3) immediately on your PC. You can see this only after you connect your PC to the device (After connect to the device, a window of "finding new device" will pop up and then click that window and next step to finish the installation) 

### e. Download FlyMcu (this is the software to download binary file to the board)
- Download [FlyMcu.rar]("https://blackboard.cuhk.edu.hk/bbcswebdav/pid-6184550-dt-content-rid-96358898_1/xid-96358898_1") from blackboard-Reference Folder-Program  
- Click EnumPort to discover available serial ports and select the correct serial port.
- Select the location that stores the binary file. E.g. "_st12345.hex"
- Select 'Reset@DTR Low(<-3V), ISP@RTS High'  (4th option)
- tick "Auto Reload Before Program" on the top of right window
- Press 'Start ISP' for 'downloading'
-  Press the 'RESET' key on your project board to start your program that you have 
downloaded

## Some reminders
### Keep the hex file for hardware checking
- Copy the hex file (e.g. _st12345.hex) to Exp0.hex for Exp0 (Exp0.hex is a folder I guess)
- Copy the hex file (e.g. _st12345.hex) to Exp1.1.hex for Exp1.1.

### procedure between different labs
**Lab-0**  
Empty project  
Prove complier/tools OK  
Know procedures, compiling, download.  
<br>
**Copy Lab-0 and rename to Lab-1**  
<br>
**Lab-1**  
Study GPIO.  
Create libraries for your project board.  

### version control 
Replace main.c with 
experiment versions (eg. Exp0.c, Exp1.1.c ...)  
In each file, there is a `void main(){}` 

## A simple Assembly program (create a assembly project)
 For Assembly language, you only need one file named '.s' in your project folder. E.g
 'MyFirstAsm.s'.  
 <br>
- Open KEIL uVision and create a new project.  
- Project >> New uVision Project
- Select the device you are going to use. (eg. TM32F103ZE)
- Click the "three color box" icon -> Use text editor to create an empty text Assembly file locally (e.g. MyFirstAsm.s) and add it into "Source Group 1" **(Make sure the file suffix is '.s', not '.s.txt'. Windows hides known suffix (.txt) by default.)** 
- Key in the following assembly program "MyFirstAsm.s". 
```
    AREA RESET, DATA, READONLY
    EXPORT __Vectors
    DCD 0x20002000
    DCD Reset_Handler
__Vectors
    AREA AFTER_RESET, CODE
    EXPORT Reset_Handler
Reset_Handler
    movr8 , #-5
loop
    ADDS r8, r8, #5
    b loop
    END
 ```
- Click "Options for Target" icon -> go to Linker -> **Use Memory Layout from Target Dialog** must not be ticked -> **Scatter File** must be empty
- go to Debug -> tick **Use Simulator** -> OK
- Press build icon to compile the program
- Press "Debug" icon. There is 32K code size 
limitation for evaluation project (non-paid 
license)
- You can see Registers shown on the left second row of icons. Disassembly codes are shown on the top of the right.  
<br><br>
- Press the icon 'RST' for reset. Registers R0 to R12 should be zero. R13 stack 
pointer should point at 0x20002000. R15 program counter should point at 
0x08000008. 
- Press F11 once, you can see an arrow on Disassembly window that points to next 
step. The new registers' data will be shown on the register window and be 
turned to blue.
- Expand the register 'xPSR'. You can see some flags N, Z, C, V, Q, T, IT and ISR. We 
are interested in Z flag. Press F11 a few times; check the flag Z and C after each 
pressing.
- The function of the program adds 5 each, starting from -5. When the result is 
equal to zero, the Z flag will be equal to '1'.  
- The Assembly instruction 'ADDS' adds register (number) and updates flags. The 
instruction 'ADD' adds register (number) but the flags will not be updated.
- Depending on the flags’ status, microprocessor can make conditional jump to 
redirect the program flow for different behaviors. This is the basic function why 
microprocessor can make decisions. 