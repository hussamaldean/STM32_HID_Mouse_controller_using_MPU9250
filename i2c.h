#ifndef __i2c__h
#define __i2c__h

#include "stm32f4xx.h"                  // Device header

void I2C3_Init(void);
char i2c_readByte(char saddr,char maddr, char *data);
void i2c_writeByte(char saddr,char maddr,char data);
void i2c_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length);
void i2c_ReadMulti(char saddr,char maddr, int n, char* data);

#endif
