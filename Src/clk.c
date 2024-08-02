/*
 * clk.c
 *
 *  Created on: Jun 30, 2023
 *      Author: mwael
 */

#define STM32F446xx  1
#include <stm32f4xx.h>
#include "bit_calc.h"
#include "clk.h"

void clk_configure_180_MHZ(void){

set_bit(RCC->CR,RCC_CR_HSEON_Pos);    //HSE enable
while(get_bit(RCC->CR,RCC_CR_HSERDY_Pos)==0);

RCC->CFGR &= (~RCC_CFGR_HPRE);
RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

RCC->CFGR &= (~RCC_CFGR_PPRE1);
RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

RCC->CFGR &= (~RCC_CFGR_PPRE2);
RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

RCC->PLLCFGR=0;
RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ_1;
RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_2;
RCC->PLLCFGR |= (180<<RCC_PLLCFGR_PLLN_Pos);
RCC->PLLCFGR |= RCC_PLLCFGR_PLLR_1;
RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;

set_bit(RCC->CR,RCC_CR_PLLON_Pos);
while((RCC->CR & RCC_CR_PLLRDY)==0);

FLASH->ACR &= (~FLASH_ACR_LATENCY);
FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

RCC->CFGR &= (~RCC_CFGR_SW);
RCC->CFGR |= RCC_CFGR_SW_PLL;

while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);


}
