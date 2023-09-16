/*
 * keypad.c
 *
 * Created: 9/1/2023 9:09:11 AM
 *  Author: yusuf
 */ 
#include "F:\Atmel\Drivers\LIB\MATH.h"
#include "F:\Atmel\Drivers\LIB\STD_TYPES.h"

#include <avr/io.h>
#include <util/delay.h>

#include "keybad_interface.h"
#include "keybad_private.h"



void kEYBAD_vInit(void){
	/* SET 4 inputs */
	CLR_BIT(KEYPAD_INPUT_DDR, IN0);
	CLR_BIT(KEYPAD_INPUT_DDR, IN1);
	CLR_BIT(KEYPAD_INPUT_DDR, IN2);
	CLR_BIT(KEYPAD_INPUT_DDR, IN3);
	/* Pull up 4 input pins --> defualt to read is 1*/
	SET_BIT(KEYPAD_INPUT_PORT, IN0);
	SET_BIT(KEYPAD_INPUT_PORT, IN1);
	SET_BIT(KEYPAD_INPUT_PORT, IN2);
	SET_BIT(KEYPAD_INPUT_PORT, IN3);
	/* SET 4 outputs */
	SET_BIT(KEYPAD_OUTPUT_DDR, OUT0);
	SET_BIT(KEYPAD_OUTPUT_DDR, OUT1);
	SET_BIT(KEYPAD_OUTPUT_DDR, OUT2);
	SET_BIT(KEYPAD_OUTPUT_DDR, OUT3);
	/* SET 4 outputs ports to high*/
	SET_BIT(KEYPAD_OUTPUT_PORT, OUT0);
	SET_BIT(KEYPAD_OUTPUT_PORT, OUT1);
	SET_BIT(KEYPAD_OUTPUT_PORT, OUT2);
	SET_BIT(KEYPAD_OUTPUT_PORT, OUT3);
}

u8 kEYBAD_u8Getkey(){
	u8 key = 'x';								// return x case of no press
	CLR_BIT(KEYPAD_OUTPUT_PORT, OUT0);			// output 0 column 0
	if(!GET_BIT(KEYPAD_INPUT_PIN, IN0)){		// "!" see which input be 0
		key = '1';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN0));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN1)){	// "!" see which input be 0
		key = '4';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN1));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN2)){	// "!" see which input be 0
		key = '7';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN2));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN3)){	// "!" see which input be 0
		key = '*';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN3));
	}
	_delay_ms(1);								// delay between set and clear
	SET_BIT(KEYPAD_OUTPUT_PORT, OUT0);			// not in column 0
	
	CLR_BIT(KEYPAD_OUTPUT_PORT, OUT1);			// output 0 column 1
	if(!GET_BIT(KEYPAD_INPUT_PIN, IN0)){		// "!" see which input be 0
		key = '2';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN0));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN1)){	// "!" see which input be 0
		key = '5';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN1));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN2)){	// "!" see which input be 0
		key = '8';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN2));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN3)){	// "!" see which input be 0
		key = '0';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN3));
	}
	_delay_ms(1);								// delay between set and clear
	SET_BIT(KEYPAD_OUTPUT_PORT, OUT1);			// not in column 1
	
	CLR_BIT(KEYPAD_OUTPUT_PORT, OUT2);			// output 0 column 2
	if(!GET_BIT(KEYPAD_INPUT_PIN, IN0)){		// "!" see which input be 0
		key = '3';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN0));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN1)){	// "!" see which input be 0
		key = '6';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN1));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN2)){	// "!" see which input be 0
		key = '9';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN2));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN3)){	// "!" see which input be 0
		key = '#';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN3));
	}
	_delay_ms(1);								// delay between set and clear
	SET_BIT(KEYPAD_OUTPUT_PORT, OUT2);			// not in column 2
	
	CLR_BIT(KEYPAD_OUTPUT_PORT, OUT3);			// output 0 column 3
	if(!GET_BIT(KEYPAD_INPUT_PIN, IN0)){		// "!" see which input be 0
		key = 'A';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN0));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN1)){	// "!" see which input be 0
		key = 'B';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN1));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN2)){	// "!" see which input be 0
		key = 'C';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN2));
		}else if(!GET_BIT(KEYPAD_INPUT_PIN, IN3)){	// "!" see which input be 0
		key = 'D';
		while(!GET_BIT(KEYPAD_INPUT_PIN, IN3));
	}
	_delay_ms(1);								// delay between set and clear
	SET_BIT(KEYPAD_OUTPUT_PORT, OUT3);			// not in column 3
	
	return key;
}