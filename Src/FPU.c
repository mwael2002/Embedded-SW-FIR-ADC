/*
 * FPU.c
 *
 *  Created on: Jun 18, 2023
 *      Author: mwael
 */

#define STM32F446xx  1
#include <stm32f4xx.h>
#include "FPU.h"
#include "bit_calc.h"

void FPU_init(void){
set_bit(SCB->CPACR,20);
set_bit(SCB->CPACR,21);
set_bit(SCB->CPACR,22);
set_bit(SCB->CPACR,23);
}
