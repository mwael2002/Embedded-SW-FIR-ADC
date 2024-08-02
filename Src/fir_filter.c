/*
 * fir_filter.c
 *
 *  Created on: Feb 22, 2024
 *      Author: mwael
 */
#include "fir_filter.h"


void fir_filter_init(fir_filter * fir_filter0,float32_t * fir_kernel){

	for(uint8_t i=0;i<FIR_BUF_LENGTH;i++){

		fir_filter0->buff[i]=0;

	}

	fir_filter0->buff_index=0;
	fir_filter0->out=0;
	fir_filter0->kernel=fir_kernel;


}

float32_t fir_filter_update(fir_filter * fir_filter0,float64_t fir_sample){

	fir_filter0->buff[fir_filter0->buff_index]=fir_sample;
	fir_filter0->buff_index++;

	if(fir_filter0->buff_index==FIR_BUF_LENGTH){
		fir_filter0->buff_index=0;
	}

	uint16_t sum_index=FIR_BUF_LENGTH;
	fir_filter0->out=0;

	for(uint16_t i=0; i< FIR_BUF_LENGTH;i++){

		sum_index--;

		fir_filter0->out+=fir_filter0->buff[i]*fir_filter0->kernel[sum_index];
	}

	return fir_filter0->out;

}
