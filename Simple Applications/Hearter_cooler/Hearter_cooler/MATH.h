#ifndef Macros_H_
#define Macros_H_

//Macros
#define CLR_BIT(ADDR,BIT) ADDR &= ~(1<<BIT)
#define SET_BIT(ADDR,BIT) ADDR |= (1<<BIT)
#define TGL_BIT(ADDR,BIT) ADDR ^= (1<<BIT)
#define GET_BIT(ADDR,BIT) ((ADDR>>BIT) & 1) 
//zero or one then >>bit is back to chech numb 0 or 1

#endif