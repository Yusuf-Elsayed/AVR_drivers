/*
 * GPIO_interface.h
 *
 * Created: 8/18/2023 11:09:48 AM
 *  Author: Yusuf-Elsayed
 */ 


#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_
typedef enum{
	A,
	B,
	C,
	D
}Port_t;
typedef enum{
	input,
	output
}PinState_t;

typedef enum{
	h,
	l
}State_t;

#define led0C 2
#define led1C 7
#define led3D 3

#define sw0B 0
#define sw1D 6
#define sw2D 2

void GPIO_voidConfigureBinInputOrOutput(u8 copy_portName, u8 copy_pinNum, u8 pinStateHorL);
u8 GPIO_voidReadBin(u8 copy_portName, u8 copy_pinNum);
void GPIO_voidTGLBin(u8 copy_portName, u8 copy_pinNum);
void GPIO_voidWriteBin(u8 copy_portName, u8 copy_pinNum, u8 copy_writeStatus);

u8 GPIO_voidReadAllPIN(u8 copy_portName);
void GPIO_voidWriteAllPort(u8 copy_portName, u8 copy_u8Value);
#endif /* GPIO_INTERFACE_H_ */