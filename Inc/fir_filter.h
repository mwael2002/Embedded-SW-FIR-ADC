/*
 * fir_filter.h
 *
 *  Created on: Feb 22, 2024
 *      Author: mwael
 */

#ifndef FIR_FILTER_H_
#define FIR_FILTER_H_

#include <stdint.h>
#include "arm_math.h"

#define FIR_BUF_LENGTH	103

typedef struct{

float32_t buff[FIR_BUF_LENGTH];
float32_t * kernel;
uint8_t buff_index;
float32_t out;

}fir_filter;


void fir_filter_init(fir_filter * fir_filter0,float32_t * fir_kernel);
float32_t fir_filter_update(fir_filter * fir_filter0,float64_t fir_sample);

#endif /* FIR_FILTER_H_ */
