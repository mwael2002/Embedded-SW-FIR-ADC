/*
 * FIFO.c
 *
 *  Created on: Feb 22, 2024
 *      Author: mwael
 */

#include "FIFO.h"

rx_fifo_type RX_FIFO[RX_FIFO_SIZE];

volatile rx_fifo_type * rx_put_ptr;
volatile rx_fifo_type * rx_get_ptr;


void RX_FIFO_init(void){

	rx_get_ptr=rx_put_ptr=&RX_FIFO[0];

}


uint8_t RX_FIFO_put(rx_fifo_type data){

	volatile rx_fifo_type * rx_next_put_ptr;

	rx_next_put_ptr=rx_put_ptr+1;

	if(rx_put_ptr == &RX_FIFO[RX_FIFO_SIZE-1]){

		rx_next_put_ptr=&RX_FIFO[0];
		(*rx_put_ptr)=data;
		rx_put_ptr=&RX_FIFO[0];

	}

	if (rx_next_put_ptr==rx_get_ptr)
	{
		return RX_FIFO_FULL;
	}


	else{

		(*rx_put_ptr)=data;
		rx_put_ptr+=1;
	}

	return RX_FIFO_NOT_FULL;

}

uint8_t RX_FIFO_get(volatile rx_fifo_type* data_ptr){

	volatile rx_fifo_type * rx_next_get_ptr;

	rx_next_get_ptr=rx_get_ptr+1;


	if(rx_get_ptr == &RX_FIFO[RX_FIFO_SIZE-1]){

		rx_next_get_ptr=&RX_FIFO[0];
		(*data_ptr)=(*rx_get_ptr);
		rx_get_ptr=&RX_FIFO[0];

	}

	if(rx_next_get_ptr==rx_put_ptr){

		return RX_FIFO_EMPTY;
	}

	else
	{
	(*data_ptr)=(*rx_get_ptr);
	rx_get_ptr+=1;
	}

	return RX_FIFO_NOT_EMPTY;

}
