/*
 * Hearter_cooler.c
 *
 * Created: 9/15/2023 9:46:32 AM
 * Author : yusuf
 */ 

#define F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "MATH.h"
#include "STD_TYPES.h"

#include "EXTI_interface.h"
#include "GPIO_interface.h"
#include "LCD_interface.h"
#include "ADC.h"
u8 flag = 0;

ISR(INT0_vect){
	flag = 1;
}

ISR(INT1_vect){
	flag = 0;
}
int main(void)
{
	// Configure a GPIO pin for LM35 sensor input
	GPIO_voidConfigureBinInputOrOutput(A, 0, input);
	
	//int0 , 1
	GPIO_voidConfigureBinInputOrOutput(D, 2, input);
	GPIO_voidConfigureBinInputOrOutput(D, 3, input);
	//internal pullup
	GPIO_voidWriteBin(D, 2, h);
	GPIO_voidWriteBin(D, 3, h);

	GPIO_voidConfigureBinInputOrOutput(D, 0, output);
	GPIO_voidConfigureBinInputOrOutput(D, 1, output);
	GPIO_voidConfigureBinInputOrOutput(D, 4, output);


	// Initialize the ADC
	adc_init();

	// Initialize the LCD
	LCD_vInit_4Bit();
	
	EXTI_vInt0_Init();
	EXTI_vInt1_Init();
	// Set PORTD as output for displaying temperature

	while (1)
	{
		if(flag){
			// Read ADC value from channel 0 (LM35 sensor)
			uint16_t adcValue = adc_read(0);
			
			// Convert ADC value to temperature in degrees Celsius
			// Formula: temperature = (adcValue / 1024.0) * 500.0
			float temperature = ((float)adcValue*5000.0) / 1024.0;
			u8 temp = temperature / 10.0 ;

			// Clear LCD screen
			LCD_Send_CMD_4BIT(0x01);

			// Set cursor to home position
			LCD_Send_CMD_4BIT(0x02);


			// Display temperature on LCD
			LCD_Send_StringData_4bit( "Temp: " );
			LCD_Send_Data_4BIT(temp / 10 + '0');
			LCD_Send_Data_4BIT(temp % 10 + '0');

			LCD_Send_CMD_4BIT(0xC0); //2nd line
			// Output temperature on PORTD (for debugging or other purposes)
			if(temp >= 24 && temp <= 26){
				GPIO_voidWriteBin(D,0,h);
				GPIO_voidWriteBin(D,1,l);
				GPIO_voidWriteBin(D,4,l);
				LCD_Send_StringData_4bit("Everything is OK");
			}
			else if(temp < 24) {
				GPIO_voidWriteBin(D,0,l);
				GPIO_voidWriteBin(D,1,h);
				GPIO_voidWriteBin(D,4,l);
				LCD_Send_StringData_4bit("Cool");
				}else{
				GPIO_voidWriteBin(D,0,l);
				GPIO_voidWriteBin(D,1,l);
				GPIO_voidWriteBin(D,4,h);
				LCD_Send_StringData_4bit("Hot");
			}
			_delay_ms(500); // Delay for stability
		}else{
			LCD_CLR_SCREEN_4BIT();
			GPIO_voidWriteBin(D,0,l);
			GPIO_voidWriteBin(D,1,l);
			GPIO_voidWriteBin(D,4,l);
		}
	}
}

