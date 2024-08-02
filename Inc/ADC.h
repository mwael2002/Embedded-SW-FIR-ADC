/*
 * ADC_interface.h
 *
 *  Created on: Sep 1, 2023
 *      Author: mwael
 */

#ifndef ADC_H_
#define ADC_H_

void pa1_adc_init(void);
void start_conversion(void);
uint16_t ADC_read(void);

#endif /* ADC_H_ */
