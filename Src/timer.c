/*
 * timer.c
 *
 *  Created on: Jun 14, 2024
 *      Author: mwael
 */

#define STM32F446xx  1
#include <stm32f4xx.h>
#include "bit_calc.h"
#include "timer.h"

void timer2_1_hz_int_enable(void){

	// enable clk on APB1
	set_bit(RCC->APB1ENR,TIMER2_EN);

	// set prescaler value of timer frequency to have 1Hz
	TIM2->PSC = (9000 -1 ); // frequency of timer= 90 MHz /9 KHz = 10 KHz

	TIM2->ARR = (10-1);    // frequency of one tick = 10000/10 = 1 /kHz

	// Clear the counter
	TIM2->CNT =0;

	// enable interrupt
	set_bit(TIM2->DIER,DIER_UIE);

	// enable NVIC
	NVIC_EnableIRQ(TIM2_IRQn);

	// enable timer2
	set_bit(TIM2->CR1,CR1_EN);
}
