/*
 * LCD.c
 *
 * Created: 8/25/2023 11:59:06 AM
 * Author: yusuf
 */ 
#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
#include "MATH.h"
#include "STD_TYPES.h"
#include "LCD_interface.h"

#define EN 3
#define RS 1
#define RW 2
#define D_prot PORTA
#define C_Port PORTB
#define D_DDR DDRA // data
#define C_DDR DDRB

void LCD_Send_Data(u8 data) {
    // Set RS to 1 to indicate data transmission
    SET_BIT(C_Port, RS);

    // Set RW to 0 for write mode
    CLR_BIT(C_Port, RW);

    // Load data to PORTA
    PORTA = data;

    // Pulse EN to send the data
    SET_BIT(C_Port, EN);
    _delay_ms(1);
    CLR_BIT(C_Port, EN);

    // Wait for the LCD to process the data
    _delay_ms(20);
}

void LCD_Send_CMD(u8 cmd) {
    // Set RS to 0 to indicate command transmission
    CLR_BIT(C_Port, RS);

    // Set RW to 0 for write mode
    CLR_BIT(C_Port, RW);

    // Load command to PORTA
    PORTA = cmd;

    // Pulse EN to send the command
    SET_BIT(C_Port, EN);
    _delay_ms(1);
    CLR_BIT(C_Port, EN);

    // Wait for the LCD to process the command
    _delay_ms(20);
}

void LCD_vInit() {
    // Set data lines as output
    DDRA = 0xFF;

    // Set R/W, RS, and EN pins as output
    SET_BIT(C_DDR, RW);
    SET_BIT(C_DDR, RS);
    SET_BIT(C_DDR, EN);
	//wait for lcd
	_delay_ms(15);
    // Initialize the LCD module
    LCD_Send_CMD(0x38);  // Initialize LCD in 8-bit mode
    LCD_Send_CMD(0x0C);  // Turn on display, cursor off
    LCD_Send_CMD(0x06);  // Set entry mode to auto-increment
    LCD_Send_CMD(0x01);  // Clear the screen
    LCD_Send_CMD(0x02);  // Move cursor to the home position
    _delay_ms(15);
}
void LCD_Send_StringData(u8 *data){
	u8 i = 0;
	while (data[i] != '\0'){
		LCD_Send_Data(data[i]);
		i++;
	}
}


void LCD_Send_Data_4BIT(u8 data) {
	// Set RS to 1 to indicate data transmission
	SET_BIT(C_Port, RS);

	// Set RW to 0 for write mode
	CLR_BIT(C_Port, RW);

	// Load data to PORTA upper
	PORTA = (PORTA & 0x0F) | (data & 0xF0);

	// Pulse EN to send the data
	SET_BIT(C_Port, EN);
	_delay_ms(1);
	CLR_BIT(C_Port, EN);
	
	_delay_ms(1);
	
	// Load data to PORTA lower
	PORTA = (PORTA & 0x0F) | ((data << 4));
	SET_BIT(C_Port, EN);
	_delay_ms(1);
	CLR_BIT(C_Port, EN);

	// Wait for the LCD to process the data
	_delay_ms(20);
}

void LCD_Send_CMD_4BIT(u8 cmd) {
	// CLR RS to 0 to indicate data transmission
	CLR_BIT(C_Port, RS);

	// Set RW to 0 for write mode
	CLR_BIT(C_Port, RW);

	// Load data to PORTA upper
	PORTA = (PORTA & 0x0F) | (cmd & 0xF0);

	// Pulse EN to send the data
	SET_BIT(C_Port, EN);
	_delay_ms(1);
	CLR_BIT(C_Port, EN);
	
	_delay_ms(1);
	
	// Load data to PORTA lower
	PORTA = (PORTA & 0x0F) | (cmd << 4);
	SET_BIT(C_Port, EN);
	_delay_ms(1);
	CLR_BIT(C_Port, EN);

	// Wait for the LCD to process the data
	_delay_ms(20);
}

void LCD_vInit_4Bit() {
	// Set data lines as output
	DDRA |= 0xF0;

	// Set R/W, RS, and EN pins as output
	SET_BIT(C_DDR, RW);
	SET_BIT(C_DDR, RS);
	SET_BIT(C_DDR, EN);
	//wait for lcd
	_delay_ms(15);

	// Initialize the LCD module
	LCD_Send_CMD_4BIT(0x02);  // Move cursor to the home position	
	LCD_Send_CMD_4BIT(0x28);  // Initialize LCD in 4-bit mode
	LCD_Send_CMD_4BIT(0x0C);  // Turn on display, cursor off
	LCD_Send_CMD_4BIT(0x06);  // Set entry mode to auto-increment
	LCD_Send_CMD_4BIT(0x01);  // Clear the screen
}
void LCD_Send_StringData_4bit(u8 *data){
	u8 i = 0;
	while (data[i] != '\0'){
		LCD_Send_Data_4BIT(data[i]);
		i++;
	}
}
void LCD_CLR_SCREEN_4BIT(){
	LCD_Send_CMD_4BIT(0x01); //clear screen
	LCD_Send_CMD_4BIT(0x02); //home position
}
void LCD_CLR_SCREEN(){
	LCD_Send_CMD(0x01); //clear screen
	LCD_Send_CMD(0x02); //home position
}

void LCD_NEW_LINE_4BIT(){
	LCD_Send_CMD_4BIT(0xC0); //new line
}
void LCD_NEW_LINE(){
	LCD_Send_CMD(0xC0); //new line
}