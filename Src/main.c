#define STM32F446xx  1
#include <stm32f4xx.h>
#include <stdio.h>
#include "arm_math.h"
#include "bit_calc.h"
#include "FPU.h"
#include "USART.h"
#include "systick.h"
#include "timer.h"
#include "clk.h"
#include "signals.h"
#include "ADC.h"
#include "fir_filter.h"
#include "FIFO.h"

#define DSP_SAMPLE 1
#define DSP_NO_SAMPLE 0
#define LENGTH_INPUT_SIG	RX_FIFO_SIZE


rx_fifo_type rx_data[RX_FIFO_SIZE];
uint8_t fifo_write_flag = RX_FIFO_NOT_FULL, process_flag=DSP_NO_SAMPLE;

float32_t output_FIR [LENGTH_INPUT_SIG+LENGTH_FIR_LOWPASS_RESPONSE-1];


extern float32_t impulse_response[LENGTH_IMPULSE_RESPONSE];
extern float32_t FIR_lowpass_response[LENGTH_FIR_LOWPASS_RESPONSE];
extern float32_t FIR_highpass_response[LENGTH_FIR_HIGHPASS_RESPONSE];


void convolution(rx_fifo_type * input_sig,float32_t * impulse_response_sig,float32_t * output_sig,
		         uint16_t length_input_sig, uint16_t length_impulse_response);


void plot_signal_UART(float32_t* sig,uint32_t length_signal);
void pseuodo_delay(uint64_t delay);
void tim2_call_back(void);
void clear_data_buf(void);

int main(void)
{

	set_bit(RCC->AHB1ENR,0);
	set_bit(GPIOA->MODER,16);

	 FPU_init();
	 clk_configure_180_MHZ();

	 pa1_adc_init();

	 RX_FIFO_init();

	 USART_TX_init();

	 pa1_adc_init();
	 start_conversion();

	 timer2_1_hz_int_enable();
      while(1){

    	if (process_flag==DSP_SAMPLE){
    		uint8_t read_flag=RX_FIFO_NOT_EMPTY;

    		clear_data_buf();

    		for(int32_t i =0; i<RX_FIFO_SIZE ; i++){


    			if(read_flag==RX_FIFO_NOT_EMPTY)
    			{

    			read_flag=RX_FIFO_get(rx_data+i);
    			}

    			else if(read_flag==RX_FIFO_EMPTY){
    				fifo_write_flag=RX_FIFO_NOT_FULL;
    			}

    		}

    		convolution(rx_data,FIR_lowpass_response,output_FIR,LENGTH_INPUT_SIG,LENGTH_FIR_LOWPASS_RESPONSE);
    		//arm_conv_f32((float32_t *) rx_data,LENGTH_INPUT_SIG,FIR_lowpass_response,LENGTH_FIR_LOWPASS_RESPONSE,output_FIR);

    		plot_signal_UART( output_FIR, (LENGTH_INPUT_SIG+LENGTH_FIR_LOWPASS_RESPONSE-1) );

    		process_flag=DSP_NO_SAMPLE;
    		fifo_write_flag=RX_FIFO_NOT_FULL;
    	}

      }
}

void clear_data_buf(void){

	for(uint16_t i=0; i<LENGTH_INPUT_SIG; i++){
		rx_data[i]=0;
	}

}
void convolution(rx_fifo_type * input_sig,float32_t * impulse_response_sig,float32_t * output_sig,
		         uint16_t length_input_sig, uint16_t length_impulse_response){


	 uint16_t length_output_sig=length_impulse_response+length_input_sig-1;
	 int32_t i;
	 int32_t j;


	 for(i=0;i<length_output_sig;i++){
	 	 output_sig[i]=0;
	 }


	 for(i=0;i<length_input_sig;i++){

	 	 for(j=0;j<length_impulse_response;j++){

	 		 output_sig[i+j]=output_sig[i+j]+input_sig[i]*impulse_response[j];

		 }

	 }

}



void plot_signal_UART(float32_t* sig,uint32_t length_signal){
	for(uint32_t counter=0; counter<length_signal;counter++){
			printf("%ld\r\n",(int32_t) sig[counter]);
			pseuodo_delay(20000);
			}
}

void pseuodo_delay(uint64_t delay){

	for(uint64_t counter=0; counter<delay;counter++);
}

void tim2_call_back(void){

	if(fifo_write_flag == RX_FIFO_NOT_FULL){
		fifo_write_flag=RX_FIFO_put(ADC_read());
	}

	else{
		process_flag=DSP_SAMPLE;
	}
}

void TIM2_IRQHandler(void){

	// clear interrupt flag
	clear_bit(TIM2->SR,SR_UIF);

	tim2_call_back();
}
