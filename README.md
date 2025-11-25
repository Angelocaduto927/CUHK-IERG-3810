# CUHK-IERG-3810
Microprocessor and Embedded System Lab

This repository contains the lab materials and resources for the CUHK IERG 3810 course on Microprocessor and Embedded Systems.

The file structure is organized as follows:
```
- lab/
    - Board/  # Libraries for the lab
        - IERG3810_Buzzer.c
        - IERG3810_Buzzer.h
        - ...
    - Core/
    - DebugConfig/
    - Fw_lib/
    - Listenings/
    - Project/  # Codes for the final project
        - main.c
        - usart_test.c
        - ...
    - User/  # Codes for the lab experiments. Each code is independently executable with Board folder
        - Exp1.1.c
        - Exp1.2.c
        - ...
- Procedure.markdown
- README.md
```

## To start with
User should first follow the instructions in `Procedure.markdown` to download the necessary software tools (e.g. Keil uVision5) and set up the development environment.

## Lab Experiments
The `lab/User/` folder contains the code for various lab experiments. Each experiment code is self-contained and can be executed independently using the libraries in the `lab/Board/` folder.   

the lab topics are as follows:
1. GPIO(General Purpose Input Output): LED, KEY, BUZZER   
    - To study the setting of GPIOs as inputs and outputs.   
    - To study the project in C language with Standard Firmware Library for registers’ settings.  
    - Create own libraries for project board.
2. USART(Universal Synchronous Asynchronous Receiver Transmitter): USART1 and USART2    
    - To study the clock tree of Cortex-M3.  
    - To study the settings of USART transmitting. (USART1, USART2, TXE bit)  
    - Create own library for USART
3. LCD (Liquid Crystal Display): 240x320 TFT LCD  
    - To study the interfacing of Flexible Static Memory Controller of Cortex-M3.   
    - To study address decoding of FSMC.   
    - To interface a TFT-LCD with FSMC.   
    - To study the control of TFT-LCD.   
    - To study displaying alphabet and Chinese characters on TFT-LCD
4. Interrupts: External Interrupts and Timer Interrupt    
    - To study the External Interrupt setting of Cortex-M3.   
    - To study the behavior of different priority  
    - To study Synchronous protocol with PS2 keyboard.   
    - Using interrupt to receive key stroke data from a PS2 keyboard and drive LED
5. Timers: General Purpose Timers and PWM (Pulse Width Modulation)  
    - To study the Timersetting of Cortex-M3.   
    - To compare the response time of read-modify-write and direct modification of a register.    
    - To compare the overhead and the switching time of interrupt handler and subroutines.    
    - To study SYSTICK setting of Cortex-M3.    
    - To study the generation of a PWM signal.  
    - To study remapping of cortex-M3 Alternate Function.   
    - To learn the use of a timer and its multiple-channel outputsto drive a tri-color LED.


## Final Project
The `lab/Project/` folder contains the code for the final project of the course.

### Project Introduction
Project Description:  
1. Game Type: PvP (1v1) shooting game built on STM32
2. Background Story: The day has come. Two enemies meet in the wild desert, both 
chasing the same treasure. The wind is hot, the ground dry, and silence fills the air. 
They raise their guns, eyes sharp with hate and hope. Only one can win. The other 
will fall and be lost to the sand forever.
3. Game Feature:
    - Fighting platform: A three-level desert arena with gravity, where health packs appear randomly.  
    - Weapon: Vandal with 10 damage per bullet and 2 bullets/sec fire rate.   
    - Heal packs: Restore character’s HP. Randomly appeared at the platform.
    - Character: Equipped with a weapon. Has 5 movements (move 
left/right, jump up/down, shoot). Initial and maximum HP is 100.
4. Game Control: Two players use their own keypads to control their in-game role.  
    - Press “kp 9”: The character starts shooting at the current direction.
    - Press “kp 4”: The character moves left.
    - Press “kp 2”: The character jumps down from current level (three-level arena).
    - Press “kp 6”: The character moves right.
    - Press “kp 8”: The character jumps up.

### Hardware requirements
- 2 x STM32F103 Development Board (with IERG3810 project board)  
- 2 x PS2 Keypad   
- 1 x Serial Communication Cable (for USART connection between two boards)

### Software Setup
For the main board (Player 1):
- Download the code from `lab/Project/` and `lab/Board/` and open it in Keil uVision5. 
- Delete the usart_test.c file from the Project folder.
- Connect the USART1 pins (TX, RX, GND) to the computer
- Compile and upload the code to the STM32 board.

For the sub board (Player 2):
- Download the code from `lab/Project/` and `lab/Board/` and open it in Keil uVision5.
- Delete the main.c file from the Project folder.
- Connect the USART1 pins (TX, RX, GND) to the computer
- Compile and upload the code to the STM32 board.

Connect the two boards via USART2 (TX to RX, RX to TX, GND to GND).

### Gameplay Instructions
Refer to the info page on the LCD screen.

## License

This project is licensed under a custom non-commercial, non-academic-use license.  
See [LICENSE](LICENSE) for details.

## 🙏 Acknowledgements

Thanks to the instructors and teaching team of **IERG3810** at The Chinese University of Hong Kong for their inspiring course on **Microcontrollers and Embedded System** . This project is a personal study effort based on concepts learned in the course.

Also, I sincerely thank my parter Kaixin for his collaboration and support throughout the development of this project.

❗ This code is for **personal learning only** — **not for homework submission or commercial use**.