// .h (must be found .c may not)-> interface (functions prototypes) -> implemted in .c
// .c is private for libary (no one include lib see it -> only functions in .h(prototype)seen)
// to make it public -> should put prototype in .h
// Macros no implementation -> in .h only
// "lib" current directory of main .c

//#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "F:\Atmel\Drivers\AVR_drivers\LIB\MATH.h"
#include "F:\Atmel\Drivers\AVR_drivers\LIB\STD_TYPES.h"

#include "F:\Atmel\Drivers\AVR_drivers\ADC\ADC\ADC.h"


//PA is ADC (special perpose)
//1 preipheral mux select which one will enter
// resolution # of bits (1bit -> 2 level)
//levels = 2^#bits -1
//(2^8 -1 = 255) without 0
// (2^10 -1 = 1023) without 0 -> 1023
// Va = Vd*Vref/levels  => levels = 2^n -1

//1) ADMUX
//A) vref:
// REFS1 REFS0 (refrence selection)
//   0     0  -> AREF (external bin) => default
//   0     1  -> AVCC->5v (should be connected to vcc)
//   1     0  -> X reserved
//   1     1  -> 2.65V
// this to decrease sensitivty (better)
//1) dec vref
//2) inc levels
// S at Vd=1 ->5/1023

//B) Mux0->mux4 mux2,1,0 to control ADC0->7

//C) ADLR=0 98 76543210(10bit res) -> level = 2^10 (default)
//ADLR=1 98765432 10(8bit res)  -> level = 2^8
//  ADCH    ADCL
//ADLR=1 (at 8bit) ADCH - ADHL


//2) ADCSRA (ADC Control and status Register A)
//A) ADPS2,1,0(Sampling rate) prescaler selection bits  ADC frequency =F_CPU/? = 1M/8? = 50K ~ 200K -> 8 = 100
//B) ADE bit 7 put to 1 to enable ADC
//C) ADCSC (start of conversion) bit 7 put to 1 -> sampling one time
//ADCSRA |= (1<<ADSC)
//while(ADCSRA & (1<<ADSC))
// return ADC  // 10 bit res
// return ADCH // 8  bit res
//IF NEEDED
//ADIE -> interrupt enable -> end of conversion do ISR


//Steps
//1)(INTIATE)
//1) ADMUX
// REFS1 REFS0 (refrence selection)
//   0     0  -> AREF (external bin) => default
//   0     1  -> AVCC->5v (should be connected to vcc)
//   1     0  -> X reserved
//   1     1  -> 2.65V
//SET_BIT(ADMUX,REFS0);

//2) ADCSRA (ADC Control and status Register A)
//ADPS2,1,0(Sampling rate) prescaler selection bits
//ADC frequency =F_CPU/? = 16M/128 = 50K ~ 200K -> 128 = 111
// CHOOSE DIVISION
// SET_BIT(ADCSRA,ADPS0);
// SET_BIT(ADCSRA,ADPS1);
// SET_BIT(ADCSRA,ADPS2);

//3) ADCSRA -> ADEN =1
// ADEN(ENABLE ADC)
// SET_BIT(ADCSRA,ADEN); //EN



//1) INTIALIZATION
void adc_init(){
	//1) ADMUX
	//A) REFS1 REFS0
	SET_BIT(ADMUX,REFS0); //VREF
	//B) ADLR
	CLR_BIT(ADMUX,ADLAR);

	//2) ADCSRA (Control and status Register A)
	//A)ADPS2,1,0(Sampling rate)
	// F_CPU/? =50k ~ 200K -> = 16M/128-> 128 = 111
	
	SET_BIT(ADCSRA,ADPS0);  // CHOOSE DIVISION
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);

	//B) ADEN(ENABLE ADC)
	SET_BIT(ADCSRA,ADEN); //EN
	
}

//2) READING
uint16_t adc_read(uint8_t _ch){
	u16 read =0;
	//CH 0->7 USING ADMUX (MUX4~MUX0)
	ADMUX &= 0xE0;// 0b1110 0000 (DELETE PAST CAHNNEL CONFIG)
	ADMUX |= _ch; // NOT TO CHANGE REFS0,1

	SET_BIT(ADCSRA,ADSC);  // START ONE SAMPLE
	while (ADCSRA &(1<<ADIF));
	read = (u16)ADCL + ((u16)ADCH<<8) ;
	return read; //or adcw 10 bit - adch 8bit
}
