# Embedded SW implementation of FIR interfaced with ADC
## This project aims to test both lowpass and highpass FIR filter by an input signal comes from ADC.
#### The FIR coefficients is generated from Matlab by fdatool then saved in an array.
#### The external analog signal then converted into digital signal by ADC (12-bit) resolution, then output signal of ADC is convoluted with the FIR coeffecients (Impulse response of FIR).
#### The output signal of the filter is sent through UART to PC and displayed by Arduino serial plotter.
### Microcontroller used: STM32 Nucleo board
### Drivers: FPU, ADC, UART, clk (freq. configuration), timer, FIFO and fir filter.
## 2 input examples:
### a) DC signal with 3.3V amplitude (It's configured to be max. value of ADC input)
![Alt text]()
### b) DC signal with zero Amplitude
![Alt text]()
