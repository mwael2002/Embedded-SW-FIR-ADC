/*
 * FIFO.h
 *
 *  Created on: Feb 22, 2024
 *      Author: mwael
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdint.h>

#define RX_FIFO_SIZE 300
#define RX_FIFO_FULL 0
#define RX_FIFO_EMPTY 1
#define RX_FIFO_NOT_FULL 2
#define RX_FIFO_NOT_EMPTY 2

typedef uint32_t rx_fifo_type;

void RX_FIFO_init(void);
uint8_t RX_FIFO_put(rx_fifo_type data);
uint8_t RX_FIFO_get(volatile rx_fifo_type* data_ptr);


#endif /* FIFO_H_ */
