/*
 * ADC.h
 *
 * Created: 9/15/2023 11:48:13 AM
 *  Author: yusuf
 */ 


#ifndef ADC_H_
#define ADC_H_


void adc_init();

uint16_t adc_read(uint8_t _ch);

#endif /* ADC_H_ */