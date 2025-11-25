/*#pragma once
#include "stm32f10x.h"

extern u32 ps2count;
extern u16 full_data;
extern u8 key_data;
extern u8 last_one_data;
extern u8 last_two_data;
extern u8 ones;
extern u8 parity_check_index;

#define kp0_pressed ((key_data == 0x70) && (last_one_data != 0XF0))
#define kp0_released ((key_data == 0x70) && (last_one_data == 0xF0))
#define kp1_pressed ((key_data == 0x69) && (last_one_data != 0XF0))
#define kp1_released ((key_data == 0x69) && (last_one_data == 0xF0))
#define kp2_pressed ((key_data == 0x72) && (last_one_data != 0XF0))
#define kp2_released ((key_data == 0x72) && (last_one_data == 0xF0))
#define kp3_pressed ((key_data == 0x7A) && (last_one_data != 0XF0))
#define kp3_released ((key_data == 0x7A) && (last_one_data == 0xF0))
#define kp4_pressed ((key_data == 0x6B) && (last_one_data != 0XF0))
#define kp4_released ((key_data == 0x6B) && (last_one_data == 0xF0))
#define kp5_pressed ((key_data == 0x73) && (last_one_data != 0XF0))
#define kp5_released ((key_data == 0x73) && (last_one_data == 0xF0))
#define kp6_pressed ((key_data == 0x74) && (last_one_data != 0XF0))
#define kp6_released ((key_data == 0x74) && (last_one_data == 0xF0))
#define kp7_pressed ((key_data == 0x6C) && (last_one_data != 0XF0))
#define kp7_released ((key_data == 0x6C) && (last_one_data == 0xF0))
#define kp8_pressed ((key_data == 0x75) && (last_one_data != 0XF0))
#define kp8_released ((key_data == 0x75) && (last_one_data == 0xF0))
#define kp9_pressed ((key_data == 0x7D) && (last_one_data != 0XF0))
#define kp9_released ((key_data == 0x7D) && (last_one_data == 0xF0))
#define kpnum_pressed ((key_data == 0x77) && (last_one_data != 0XF0))
#define kpnum_released ((key_data == 0x77) && (last_one_data == 0xF0))
#define kpdiv_pressed ((key_data == 0x4A) && (last_one_data == 0XE0))
#define kpdiv_released ((key_data == 0x4A) && (last_one_data == 0xF0) && (last_two_data == E0))
#define kpmul_pressed ((key_data == 0x7C) && (last_one_data != 0XF0))
#define kpmul_released ((key_data == 0x7C) && (last_one_data == 0xF0))
#define kpminus_pressed ((key_data == 0x7B) && (last_one_data != 0XF0))
#define kpminus_released ((key_data == 0x7B) && (last_one_data == 0xF0))
#define kpplus_pressed ((key_data == 0x79) && (last_one_data != 0XF0))
#define kpplus_released ((key_data == 0x79) && (last_one_data == 0xF0))
#define kpenter_pressed ((key_data == 0x5A) && (last_one_data == 0XE0))
#define kpenter_released ((key_data == 0x5A) && (last_one_data == 0xF0) && (last_two_data == 0xE0))
#define kpdel_pressed ((key_data == 0x71) && (last_one_data != 0XF0))
#define kpdel_released ((key_data == 0x71) && (last_one_data == 0xF0))
#define kpbackspace_pressed ((key_data == 0x66) && (last_one_data != 0XF0))
#define kpbackspace_released ((key_data == 0x66) && (last_one_data == 0xF0))

void EXTI15_10_IRQHandler(void);
u8 parity_check(u16 data);
*/
#pragma once
#include "stm32f10x.h"


extern u8 ps2key;
extern u32 ps2count;
extern u8 ps2dataReady;
//u8 key_data = 0;

//#define kp0_pressed key_data == 0x70
//#define kp0_released ((key_data == 0x70) && (last_one_data == 0xF0))
//#define kp1_pressed ((key_data == 0x69) && (last_one_data != 0XF0))
//#define kp1_released ((key_data == 0x69) && (last_one_data == 0xF0))
#define kp2_pressed key_data == 0x72 
//#define kp2_released ((key_data == 0x72) && (last_one_data == 0xF0))
#define kp3_pressed key_data == 0x7A
//#define kp3_released ((key_data == 0x7A) && (last_one_data == 0xF0))
#define kp4_pressed key_data == 0x6B
//#define kp4_released ((key_data == 0x6B) && (last_one_data == 0xF0))
#define kp5_pressed key_data == 0x73
//#define kp5_released ((key_data == 0x73) && (last_one_data == 0xF0))
#define kp6_pressed key_data == 0x74
//#define kp6_released ((key_data == 0x74) && (last_one_data == 0xF0))
#define kp7_pressed key_data == 0x6C
//#define kp7_released ((key_data == 0x6C) && (last_one_data == 0xF0))
#define kp8_pressed key_data == 0x75
//#define kp8_released ((key_data == 0x75) && (last_one_data == 0xF0))
#define kp9_pressed key_data == 0x7D
//#define kp9_released ((key_data == 0x7D) && (last_one_data == 0xF0))
//#define kpnum_pressed ((key_data == 0x77) && (last_one_data != 0XF0))
//#define kpnum_released ((key_data == 0x77) && (last_one_data == 0xF0))
//#define kpdiv_pressed ((key_data == 0x4A) && (last_one_data == 0XE0))
//#define kpdiv_released ((key_data == 0x4A) && (last_one_data == 0xF0) && (last_two_data == E0))
//#define kpmul_pressed ((key_data == 0x7C) && (last_one_data != 0XF0))
//#define kpmul_released ((key_data == 0x7C) && (last_one_data == 0xF0))
//#define kpminus_pressed ((key_data == 0x7B) && (last_one_data != 0XF0))
//#define kpminus_released ((key_data == 0x7B) && (last_one_data == 0xF0))
//#define kpplus_pressed ((key_data == 0x79) && (last_one_data != 0XF0))
//#define kpplus_released ((key_data == 0x79) && (last_one_data == 0xF0))
//#define kpenter_pressed ((key_data == 0x5A) && (last_one_data == 0XE0))
//#define kpenter_released ((key_data == 0x5A) && (last_one_data == 0xF0) && (last_two_data == 0xE0))
//#define kpdel_pressed ((key_data == 0x71) && (last_one_data != 0XF0))
//#define kpdel_released ((key_data == 0x71) && (last_one_data == 0xF0))
//#define kpbackspace_pressed ((key_data == 0x66) && (last_one_data != 0XF0))
//#define kpbackspace_released ((key_data == 0x66) && (last_one_data == 0xF0))

void EXTI15_10_IRQHandler(void);

