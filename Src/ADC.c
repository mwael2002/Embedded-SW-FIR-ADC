/*
 * ADC.c
 *
 *  Created on: Sep 1, 2023
 *      Author: mwael
 */
#define STM32F446xx  1
#include <stm32f4xx.h>
#include "bit_calc.h"
#include "STD_Types.h"
#include "ADC.h"


void pa1_adc_init(void){

set_bit(RCC->AHB1ENR,0);
GPIOA->MODER |= (3<<2);
set_bit(RCC->APB2ENR,8);

set_bit(ADC1->SQR3,0);
ADC1->SQR1=0;

//clear_bit(ADC1->CR1,25);
//clear_bit(ADC1->CR1,24);

set_bit(ADC1->CR2,0);

}

void start_conversion(void){


	set_bit(ADC1->CR2,1);
	set_bit(ADC1->CR2,30);


}

uint16_t ADC_read(void){

   //wait until end of conversion
	while(!get_bit(ADC1->SR,1));

	return (U16)ADC1->DR;

}
