/*
 * LCD.c
 *
 * Created: 8/25/2023 11:57:19 AM
 * Author : yusuf
 */ 
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "MATH.h"
#include "STD_TYPES.h"
#include "interface.h"
#include "GPIO_interface.h"


int main(void)
{
	/*LCD_vInit();
	LCD_Send_Data('Y');
	LCD_Send_Data('o');
	
	LCD_Send_StringData("Youssef");*/
	GPIO_voidConfigureBinInputOrOutput(A, sw0B, input);
	GPIO_voidConfigureBinInputOrOutput(A, sw1D, input);

	LCD_vInit_4Bit();
	u8 i = 0;
    /* Replace with your application code */
	LCD_Send_Data_4BIT(i / 10 + 48); // char start 0 at 48 ASCII
	LCD_Send_Data_4BIT(i % 10 + 48); // char start 0 at 48 ASCII
    while (1) 
    {
		if(GPIO_voidReadBin(B, sw0B)){
			if(i == 99)
				i = 0;
			else 
				i++;
			LCD_Send_CMD(0x01);  // Clear display
			_delay_ms(2);        // Wait for the display to clear
			LCD_Send_CMD(0x02);  // Move cursor to home position
			_delay_ms(2);        // Wait for the cursor to move
			LCD_Send_Data_4BIT(i / 10 + 48); // char start 0 at 48 ASCII
			LCD_Send_Data_4BIT(i % 10 + 48); // char start 0 at 48 ASCII
			while(GPIO_voidReadBin(B, sw0B));
		}else if(GPIO_voidReadBin(D, sw1D)){
			if(i == 0)
				i = 0;
			else
				i--;
			LCD_Send_CMD(0x01);  // Clear display
			_delay_ms(2);        // Wait for the display to clear
			LCD_Send_CMD(0x02);  // Move cursor to home position
			_delay_ms(2);        // Wait for the cursor to move
			LCD_Send_Data_4BIT(i / 10 + 48); // char start 0 at 48 ASCII
			LCD_Send_Data_4BIT(i % 10 + 48); // char start 0 at 48 ASCII
			while(GPIO_voidReadBin(D, sw1D));
		}
		//LCD_Send_Data_4BIT(i / 10 + 48); // char start 0 at 48 ASCII
		//LCD_Send_Data_4BIT(i % 10 + 48); // char start 0 at 48 ASCII
	}
}

