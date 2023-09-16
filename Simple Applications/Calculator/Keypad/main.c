/*
 * Keypad.c
 *
 * Created: 9/1/2023 9:08:49 AM
 * Author : yusuf
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "F:\Atmel\Drivers\LIB\MATH.h"
#include "F:\Atmel\Drivers\LIB\STD_TYPES.h"

#include "keybad_interface.h"
#include "F:\Atmel\Drivers\GPIO\GPIO_interface.h"
#include "F:\Atmel\Drivers\LCD\LCD.interface.h"
#include "F:\Atmel\Drivers\LCD\LCD.c"

// Function to clear the LCD display
void clearDisplay() {
	LCD_Send_CMD_4BIT(0x01);
	LCD_Send_CMD_4BIT(0x02);
}

int main(void) {
	/* Initialize LCD and keypad */
	LCD_vInit_4Bit();
	kEYBAD_vInit();
	u8 key1;
	u8 op;
	u8 key2;
	u8 eq;
	u8 reset = 0;
	s8 res; /* may be signed */

	while (1) {
		/* Get the first key */
		key1 = kEYBAD_u8Getkey();
		op = kEYBAD_u8Getkey();
		key2 = kEYBAD_u8Getkey();

		/* Wait until a valid key is pressed */
		while (key1 == 'x') {
			key1 = kEYBAD_u8Getkey();
		}

		/* Display the first key */
		LCD_Send_Data_4BIT(key1);

		/* Wait until a valid operator key is pressed */
		while (op == 'x') {
			op = kEYBAD_u8Getkey();
		}

		/* Display the operator based on the key */
		if (op == 'A') {
			LCD_Send_Data_4BIT('/');
		} else if (op == 'B') {
			LCD_Send_Data_4BIT('*');
		} else if (op == 'C') {
			LCD_Send_Data_4BIT('-');
		} else if (op == 'D') {
			LCD_Send_Data_4BIT('+');
		} else {
			/* Handle invalid operator input */
			clearDisplay();
			LCD_Send_StringData_4bit("Invalid Entry!");
			op = 'x';
			key1 = 'x';
			_delay_ms(500);
			clearDisplay();
			continue;
		}

		/* Wait until a valid second key is pressed */
		while (key2 == 'x') {
			key2 = kEYBAD_u8Getkey();
		}
		
		/* Display the second key */
		LCD_Send_Data_4BIT(key2);

		/* Handle division by zero when dividing by 0 */
		if (key2 == '0' && op == 'A') {
			LCD_Send_CMD_4BIT(0xC0);
			LCD_Send_StringData_4bit("Invalid Div by 0!");
			op = 'x';
			key1 = 'x';
			key2 = 'x';
			_delay_ms(500);
			clearDisplay();
			continue;
		}

		/* Calculate the result based on the operator */
		if (op == 'A') {
			res = (key1 - '0') / (key2 - '0');
		} else if (op == 'B') {
			res = (key1 - '0') * (key2 - '0');
		} else if (op == 'C') {
			res = (key1 - '0') - (key2 - '0');
		} else if (op == 'D') {
			res = (key1 - '0') + (key2 - '0');
		}

		/* Wait until the equal sign key is pressed */
		eq = kEYBAD_u8Getkey();
		while (eq == 'x') {
			eq = kEYBAD_u8Getkey();
		}

		/* Display the equal sign */
		if (eq == '#') {
			LCD_Send_Data_4BIT('=');
		} else {
			/* Handle invalid equal sign input */
			clearDisplay();
			LCD_Send_StringData_4bit("Invalid Entry!");
			key1 = 'x';
			op = 'x';
			key2 = 'x';
			eq = 'x';
			res = 'x';
			clearDisplay();
			continue;
		}

		/* Handle negative results */
		if (res < 0) {
			LCD_Send_Data_4BIT('-');
			res = -res;
		}

		/* Display the result digits */
		if (res / 10 != 0) {
			LCD_Send_Data_4BIT(res / 10 + '0');
		}
		LCD_Send_Data_4BIT(res % 10 + '0');

		/* Check if the reset key is pressed */
		reset = kEYBAD_u8Getkey();

		/* Enter a loop to handle reset or other options */
		do {
			reset = kEYBAD_u8Getkey();
			if (reset == '*') {
				key1 = 'x';
				op = 'x';
				key2 = 'x';
				eq = 'x';
				res = 'x';
				clearDisplay();
			} else {
				LCD_Send_CMD_4BIT(0xC0);
				LCD_Send_StringData_4bit("ON/C");
				reset == 'x';
			}
		} while (reset != '*');

		reset = 'x';
	}
}

/* 
	-less than 10 as one char 
	
	errors that handeled:
	Invalid Operator Input: When the operator key pressed is not 'A', 'B', 'C', or 'D', the code displays "Invalid Entry!" on the LCD and continues to wait for a valid operator.

	Invalid Equal Sign Input: When the equal sign key pressed is not '#', the code displays "Invalid Entry!" on the LCD and continues to wait for a valid equal sign.

	Division by Zero: If the operator is division ('A') and the second key is '0', the code displays "Invalid Div by 0!" on the LCD and continues to wait for valid input.

	Reset: When the '*' key is pressed, the code clears the display and resets the input values, allowing for a new calculation.
*/