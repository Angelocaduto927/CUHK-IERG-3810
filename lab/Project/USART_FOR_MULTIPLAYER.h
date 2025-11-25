#pragma once
#include "stm32f10x.h"


#define TX_BUFFER_SIZE 2
#define RX_BUFFER_SIZE 2
#define RX_AVAILABLE (rx_head != rx_tail)
#define TX_EMPTY (tx_head == tx_tail)

extern volatile uint8_t tx_buf[TX_BUFFER_SIZE];
extern volatile uint8_t tx_head;
extern volatile uint8_t tx_tail;

extern volatile uint8_t rx_buf[RX_BUFFER_SIZE];
extern volatile uint8_t rx_head;
extern volatile uint8_t rx_tail;

void usart2exti_init(u32 pclkl, u32 baud);
void USART2_SendByte(u8 data);

//Below are codes for receiving, adjust if needed
/*
if(RX_AVAILABLE)
    {
				u8 instruction;
        u8 val = rx_buf[rx_tail];
        rx_tail = (rx_tail + 1) % RX_BUFFER_SIZE;

        if(val ==  0x32  ) instruction=1;
        if(val ==  0x38  ) instruction=2;
				if(val ==  0x34  ) instruction=3;
        if(val ==  0x36  ) instruction=4;
				if(val ==  0x39  ) instruction=5;
    }
		*/
