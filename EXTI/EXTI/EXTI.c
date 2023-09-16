/*
 * EXTI.c
 *
 * Created: 9/2/2023 9:49:09 AM
 * Author: yusuf
 */

/* Include necessary header files */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "F:\Atmel\Drivers\AVR_drivers\LIB\MATH.h"
#include "F:\Atmel\Drivers\AVR_drivers\LIB\STD_TYPES.h"
#include "F:\Atmel\Drivers\AVR_drivers\EXTI\EXTI\EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/* Function to initialize external interrupt INT0 */
void EXTI_vInt0_Init(){
	/* Configure INT0 based on INTERRUPT_REQUEST_STATE */
	#if INTERRUPT_REQUEST_STATE == LOW_LEVEL 
		CLR_BIT(MCUCR, ISC00);     /* Set INT0 to trigger on low level */
		CLR_BIT(MCUCR, ISC01);
	#elif INTERRUPT_REQUEST_STATE == ANY_CHANGE
		SET_BIT(MCUCR, ISC00);     /* Set INT0 to trigger on any logical change */
		CLR_BIT(MCUCR, ISC01);
	#elif INTERRUPT_REQUEST_STATE == FALLING
		CLR_BIT(MCUCR, ISC00);     /* Set INT0 to trigger on falling edge */
		SET_BIT(MCUCR, ISC01);
	#elif INTERRUPT_REQUEST_STATE == RISING
		SET_BIT(MCUCR, ISC00);     /* Set INT0 to trigger on rising edge */
		SET_BIT(MCUCR, ISC01);
	#endif
	
	/* Enable external interrupt INT0 */
	SET_BIT(GICR, INT0);
	
	/* Enable global interrupt */
	sei();
}

/* Function to initialize external interrupt INT1 */
void EXTI_vInt1_Init(){
	/* Configure INT1 based on INTERRUPT_REQUEST_STATE */
	#if INTERRUPT_REQUEST_STATE == LOW_LEVEL
		CLR_BIT(MCUCR, ISC10);     /* Set INT1 to trigger on low level */
		CLR_BIT(MCUCR, ISC11);
	#elif INTERRUPT_REQUEST_STATE == ANY_CHANGE
		SET_BIT(MCUCR, ISC10);     /* Set INT1 to trigger on any logical change */
		CLR_BIT(MCUCR, ISC11);
	#elif INTERRUPT_REQUEST_STATE == FALLING
		CLR_BIT(MCUCR, ISC10);     /* Set INT1 to trigger on falling edge */
		SET_BIT(MCUCR, ISC11);
	#elif INTERRUPT_REQUEST_STATE == RISING
		SET_BIT(MCUCR, ISC10);     /* Set INT1 to trigger on rising edge */
		SET_BIT(MCUCR, ISC11);
	#endif
	
	/* Enable external interrupt INT1 */
	SET_BIT(GICR, INT1);
	
	/* Enable global interrupt */
	sei();
}
