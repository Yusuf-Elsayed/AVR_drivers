/*
 * GPIO.c
 *
 * Created: 8/18/2023 11:06:43 AM
 *  Author: Yusuf-Elsayed
 */ 
#include<avr/io.h>
#include "MATH.h"
#include "STD_TYPES.h"
#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "GPIO_private.h"


void GPIO_voidConfigureBinInputOrOutput(u8 copy_portName, u8 copy_pinNum, u8 pinStateHorL){
	switch (copy_portName)
	{
		case A:
			if(pinStateHorL == output)
				SET_BIT(DDRA, copy_pinNum);
			else if(pinStateHorL == input)
				CLR_BIT(DDRA, copy_pinNum);
			break;
		case B:
		if(pinStateHorL == output)
			SET_BIT(DDRB, copy_pinNum);
		else if(pinStateHorL == input)
			CLR_BIT(DDRB, copy_pinNum);
		break;
		case C:
		if(pinStateHorL == output)
			SET_BIT(DDRC, copy_pinNum);
		else if(pinStateHorL == input)
			CLR_BIT(DDRC, copy_pinNum);		
		break;
		case D:
		if(pinStateHorL == output)
			SET_BIT(DDRD, copy_pinNum);
		else if(pinStateHorL == input)
			CLR_BIT(DDRD, copy_pinNum);		
		break;
		default:
		/* Your code here */
		break;
	}
}

void GPIO_voidConfigurePortInput(u8 copy_portName){
	switch (copy_portName)
	{
		case A:
			DDRA = 0;
		break;
		case B:
			DDRB = 0;
		break;
		case C:
			DDRC = 0;
		break;
		case D:
			DDRD = 0;
		break;
		default:
		/* Your code here */
		break;
	}
}
void GPIO_voidConfigurePortOutput(u8 copy_portName){
	switch (copy_portName)
	{
		case A:
		DDRA = 0xFF;
		break;
		case B:
		DDRB = 0xFF;
		break;
		case C:
		DDRC = 0xFF;
		break;
		case D:
		DDRD = 0xFF;
		break;
		default:
		/* Do nothing */
		break;
	}
}

u8 GPIO_voidReadBin(u8 copy_portName, u8 copy_pinNum){
	u8 value = - 1;
	switch (copy_portName)
	{
		case A:
		value = GET_BIT(PINA, copy_pinNum);
		break;
		case B:
		value = GET_BIT(PINB, copy_pinNum);
		break;
		case C:
		value = GET_BIT(PINC, copy_pinNum);
		break;
		case D:
		value = GET_BIT(PIND, copy_pinNum);
		break;
		default:
		/* Do nothing */
		break;
	}
	return value;
}

void GPIO_voidTGLBin(u8 copy_portName, u8 copy_pinNum){
	switch (copy_portName)
	{
		case A:
		TGL_BIT(PORTA, copy_pinNum);
		break;
		case B:
		TGL_BIT(PORTB, copy_pinNum);
		break;
		case C:
		TGL_BIT(PORTC, copy_pinNum);
		break;
		case D:
		TGL_BIT(PORTD, copy_pinNum);
		break;
		default:
		/* Your code here */
		break;
	}
}

void GPIO_voidWriteBin(u8 copy_portName, u8 copy_pinNum, u8 copy_writeStatus){
	switch (copy_portName)
	{
		case A:
		if(copy_writeStatus == h)
			SET_BIT(PORTA, copy_pinNum);
		else if(copy_writeStatus == l)
			CLR_BIT(PORTA, copy_pinNum);
		break;
		case B:
		if(copy_writeStatus == h)
			SET_BIT(PORTB, copy_pinNum);
		else if(copy_writeStatus == l)
			CLR_BIT(PORTB, copy_pinNum);
		break;
		case C:
		if(copy_writeStatus == h)
			SET_BIT(PORTC, copy_pinNum);
		else if(copy_writeStatus == l)
			CLR_BIT(PORTC, copy_pinNum);
		break;
		case D:
		if(copy_writeStatus == h)
			SET_BIT(PORTD, copy_pinNum);
		else if(copy_writeStatus == l)
			CLR_BIT(PORTD, copy_pinNum);
		break;
		default:
		/* Your code here */
		break;
	}
}
u8 GPIO_voidReadAllPIN(u8 copy_portName){
	u8 result = 0;
	switch (copy_portName){
			case A:
				result = PINA;
				break;
			case B:
				result = PINB;
				break;
			case C:
				result = PINC;
				break;
			case D:
				result = PIND;
				break;
			default:
				/* Do nothing */
				break;	
		}
		return result;
}
void GPIO_voidWriteAllPort(u8 copy_portName, u8 copy_u8Value){
	switch (copy_portName){
		case A:
		PORTA = copy_u8Value;
		break;
		case B:
		PORTB = copy_u8Value;
		break;
		case C:
		PORTC = copy_u8Value;
		break;
		case D:
		PORTD = copy_u8Value;
		break;
		default:
		/* Do nothing */
		break;
	}
}