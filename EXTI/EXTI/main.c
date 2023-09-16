/*
 * EXTI.c
 *
 * Created: 9/2/2023 9:48:43 AM
 * Author : yusuf
 */

/* Include necessary header files */
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include "F:\Atmel\Drivers\AVR_drivers\LIB\MATH.h"
#include "F:\Atmel\Drivers\AVR_drivers\LIB\STD_TYPES.h"

#include "F:\Atmel\Drivers\AVR_drivers\EXTI\EXTI\EXTI_interface.h"
#include "F:\Atmel\Drivers\AVR_drivers\Keypad\Keypad\keybad_interface.h"
#include "F:\Atmel\Drivers\AVR_drivers\GPIO\GPIO.c"
#include "F:\Atmel\Drivers\AVR_drivers\LCD\LCD.interface.h"
#include "F:\Atmel\Drivers\AVR_drivers\LCD\LCD.c"


/* Define a variable i and initialize it to 0 */
u8 i = 0;


/* Interrupt Service Routine for external interrupt INT0 */
ISR(INT0_vect){
	/* Increment the value of i, wrapping around to 0 if it reaches 99 */
	if(i == 99)
		i = 0;
	else
		i++;
	GPIO_voidTGLBin(C,led0C);
	while(GPIO_voidReadBin(D, sw2D));
	_delay_ms(20);
}




int main(void)
{
    /* Configure GPIO pins A and D as inputs */
    GPIO_voidConfigureBinInputOrOutput(D, sw2D, input);
    GPIO_voidConfigureBinInputOrOutput(C, led0C, output);

    /* Initialize the LCD module in 4-bit mode */
    LCD_vInit_4Bit();
	
    /* Initialize external interrupts INT0 and INT1 */
    EXTI_vInt0_Init();
    EXTI_vInt1_Init();

    /* Replace with your application code */
    /* Display the initial value of i on the LCD */
    LCD_Send_Data_4BIT(i / 10 + 48); /* char start 0 at 48 ASCII */
    LCD_Send_Data_4BIT(i % 10 + 48); /* char start 0 at 48 ASCII */

    while (1) 
    {
        /* Clear the LCD display and move the cursor to the home position */
        LCD_Send_CMD(0x01);  /* Clear display */
        _delay_ms(2);        /* Wait for the display to clear */
        LCD_Send_CMD(0x02);  /* Move cursor to home position */
        _delay_ms(2);        /* Wait for the cursor to move */

        /* Display the updated value of i on the LCD */
        LCD_Send_Data_4BIT(i / 10 + 48); /* char start 0 at 48 ASCII */
        LCD_Send_Data_4BIT(i % 10 + 48); /* char start 0 at 48 ASCII */

        /* Wait while the button associated with INT0 is pressed */
		
    }
}
