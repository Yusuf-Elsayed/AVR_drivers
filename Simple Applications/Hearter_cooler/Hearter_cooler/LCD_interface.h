/*
 * interface.h
 *
 * Created: 8/26/2023 9:13:23 AM
 *  Author: yusuf
 */ 
#ifndef interface
#define interface
void LCD_vInit();
void LCD_Send_CMD(u8 cmd);
void LCD_Send_Data(u8 data);
void LCD_Send_StringData(u8 *data);

// 4 bit mode
void LCD_vInit_4Bit();
void LCD_Send_CMD_4BIT(u8 cmd);
void LCD_Send_Data_4BIT(u8 data);
void LCD_Send_StringData_4BIT(u8 *data);

#endif