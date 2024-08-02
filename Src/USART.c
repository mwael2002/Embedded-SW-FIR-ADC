/*
 * UART.c
 *
 *  Created on: Jan 31, 2023
 *      Author: mwael
 */
#define STM32F446xx  1
#include <stm32f4xx.h>
#include "bit_calc.h"
#include "USART.h"


int __io_putchar(uint8_t ch){
	USART_transmit_char(ch);
	return ch;
}

void USART_TX_init(void){

	set_bit(RCC	->AHB1ENR,0);

	clear_bit(GPIOA->MODER,4);
	set_bit(GPIOA->MODER,5);

	set_bit(GPIOA->AFR[0],8);
	set_bit(GPIOA->AFR[0],9);
	set_bit(GPIOA->AFR[0],10);
	clear_bit(GPIOA->AFR[0],11);


	set_bit(RCC	->APB1ENR,17);

	USART2->BRR=4687;  //1667;  //2604;
	set_bit(USART2->CR1,3);
    set_bit(USART2->CR1,13);


}

void USART_transmit_char(uint8_t data){
while(get_bit(USART2->SR,7)==0);
USART2->DR=data;
}
