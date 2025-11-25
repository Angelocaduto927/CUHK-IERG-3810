#pragma once
#include "stm32f10x.h"

void usart2_init(u32 pclkl, u32 baud);
void usart1_init(u32 pclk2, u32 baud);
void usart_print_txe(u8 USARTport, char *st);
void usart_print(u8 USARTport, char *st);

