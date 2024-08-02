# Embedded SW implementation of FIR interfaced with ADC
## This project aims to test FIR filter by an input signal comes from ADC.
#### The FIR coefficients is generated from Matlab then saved in an array.
#### The external analog signal then converted into digital signal by ADC, then output signal of ADC is convoluted with the FIR coeffecients (Impulse response of FIR).
#### The output signal of the filter is sent through UART to PC and displayed by Arduino serial plotter 
