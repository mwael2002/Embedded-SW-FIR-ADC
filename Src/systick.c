/*
 * systick.c
 *
 *  Created on: Jun 18, 2023
 *      Author: mwael
 */
#define STM32F446xx
#include <stm32f4xx.h>
#include "bit_calc.h"
#include "systick.h"

void systick_init(void){

	clear_bit(SysTick->CTRL,0);

	set_bit(SysTick->CTRL,2);

    SysTick->LOAD=0x00FFFFFF;

    set_bit(SysTick->CTRL,0);

}

uint32_t systick_current_value(void){

	return (SysTick->VAL);

}

