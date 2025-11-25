#ifndef __IERG3810_LCD_Asset_H
#define __IERG3810_LCD_Asset_H
#pragma once
#include "stm32f10x.h"




void Draw_Countdown(u8 min, u8 sec);
void Draw_HPValue1(u8 HP_value1);
void Draw_HPValue2(u8 HP_value1);
void Draw_ARENA(void);
void Draw_Character(u16 x, u16 y, u8 which, s8 d, u8 weapon); // d directtion can be 1 (right) or -1 (left)
void Draw_Bullet(u16 x, u16 y, u16 color);
void Draw_WeaponPack(u16 x, u16 y);
void Draw_HealPack(u16 x, u16 y);
void Draw_front_page(void);
void Draw_info_page(void);
void Draw_player1_win(void);
void Draw_player2_win(void);
void Draw_overtime(void);
void Draw_pause(void);
void end_page(u8 which); //(1 = player1, 2=player2)
void start_page(void);
#endif
