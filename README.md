# Embedded SW implementation of FIR interfaced with ADC
## This project aims to test both lowpass and highpass FIR filter by an input signal comes from ADC.
#### The FIR coefficients is generated from Matlab then saved in an array.
#### The external analog signal then converted into digital signal by ADC, then output signal of ADC is convoluted with the FIR coeffecients (Impulse response of FIR).
#### The output signal of the filter is sent through UART to PC and displayed by Arduino serial plotter.
### Microcontroller used: STM32 Nucleo board
### Drivers: FPU, ADC, UART, clk (freq. configuration), timer, FIFO and fir filter.
