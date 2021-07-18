#include "i2c.h"

void I2C3_Init(void){
/* Enable port A, I2C3 and C clocks  */
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN);
	RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
  /* Select Alternate function mode */
	
	GPIOA->MODER |= (1<<17);
	GPIOC->MODER |= (1<<19);
	  /* Select output type open drain */

	GPIOA->OTYPER|= (1<<8);
	GPIOC->OTYPER|= (1<<9);
	
	GPIOA->PUPDR |= (1<<16);
	GPIOC->PUPDR |= (1<<18);

  /* Select output speed very high */

	GPIOA->OSPEEDR|= (1<<16)|(1<<17);
	GPIOC->OSPEEDR|= (1<<19)|(1<<18);

	GPIOA->AFR[1]=(1<<2);
	GPIOC->AFR[1]=(1<<6);
		
	I2C3->CR1=I2C_CR1_SWRST;
	I2C3->CR1&=~I2C_CR1_SWRST;
	I2C3->CR1=I2C_CR1_SWRST;
	I2C3->CR1&=~I2C_CR1_SWRST;	
	I2C3->CR2|=16;
	I2C3->CCR=80; 
	I2C3->TRISE=17; //output max rise 
	I2C3->CR1|=I2C_CR1_PE;
	
}


char i2c_readByte(char saddr,char maddr, char *data)
{

volatile int tmp;
while(I2C3->SR2&I2C_SR2_BUSY){;}
I2C3->CR1|=I2C_CR1_START;
while(!(I2C3->SR1&I2C_SR1_SB)){;}
I2C3->DR=saddr<<1;
while(!(I2C3->SR1&I2C_SR1_ADDR)){;}
tmp=I2C3->SR2;
while(!(I2C3->SR1&I2C_SR1_TXE)){;}
I2C3->DR=maddr;
while(!(I2C3->SR1&I2C_SR1_TXE)){;}
I2C3->CR1|=I2C_CR1_START;
while(!(I2C3->SR1&I2C_SR1_SB)){;}	
I2C3->DR=saddr<<1|1;
while(!(I2C3->SR1&I2C_SR1_ADDR)){;}
I2C3->CR1&=~I2C_CR1_ACK;
tmp =I2C3->SR2;
I2C3->CR1|=I2C_CR1_STOP;
while(!(I2C3->SR1&I2C_SR1_RXNE)){;}
*data++=I2C3->DR;
return 0;
}

void i2c_writeByte(char saddr,char maddr,char data){

while (I2C3->SR2 & 2);                               //wait until bus not busy
I2C3->CR1 |= 0x100;                                 //generate start
while (!(I2C3->SR1 & 1)){;}
	
	volatile int Temp;
I2C3->DR = saddr<< 1;                 	 // Send slave address
while (!(I2C3->SR1 & 2)){;}                            //wait until address flag is set
Temp = I2C3->SR2; 
	
while (!(I2C3->SR1 & 0x80));                          //Wait until Data register empty
I2C3->DR = maddr;                      // send memory address
while (!(I2C3->SR1 & 0x80));                         //wait until data register empty
I2C3->DR = data; 	
while (!(I2C3->SR1 & 4));                             //wait until transfer finished
I2C3->CR1 |= 0x200;
}

void i2c_WriteMulti(char saddr,char maddr,char *buffer, uint8_t length){

	
	while (I2C3->SR2 & 2);                               //wait until bus not busy
I2C3->CR1 |= 0x100;                                 //generate start
while (!(I2C3->SR1 & 1)){;}
	
	volatile int Temp;
I2C3->DR = saddr<< 1;                 	 // Send slave address
while (!(I2C3->SR1 & 2)){;}                            //wait until address flag is set
Temp = I2C3->SR2; 
	
while (!(I2C3->SR1 & 0x80));                          //Wait until Data register empty
I2C3->DR = maddr;                      // send memory address
while (!(I2C3->SR1 & 0x80));                         //wait until data register empty

for (uint8_t i=0;i<length;i++)
 { 
 I2C3->DR=buffer[i]; //filling buffer with command or data
	while (!(I2C3->SR1 & 4));
 }	
                             //wait until transfer finished
I2C3->CR1 |= 0x200;

}


void i2c_ReadMulti(char saddr,char maddr, int n, char* data)
{
	volatile int temp;
	while (I2C3->SR2 & 2){;}
	I2C3->CR1|=I2C_CR1_START;
	while(!(I2C3->SR1 & I2C_SR1_SB)){;}
	I2C3->DR=saddr<<1;
	while(!(I2C3->SR1 & I2C_SR1_ADDR)){;}
	temp=I2C3->SR2;
	while(!(I2C3->SR1&I2C_SR1_TXE)){;}
	I2C3->DR = maddr;
	while(!(I2C3->SR1&I2C_SR1_TXE)){;}
	I2C3->CR1|=I2C_CR1_START;
	while(!(I2C3->SR1 & I2C_SR1_SB)){;}
	I2C3->DR=saddr<<1|1;
	while(!(I2C3->SR1 & I2C_SR1_ADDR)){;}
	temp=I2C3->SR2;
		
	I2C3->CR1|=I2C_CR1_ACK;
	while(n>0U)
		{
		if(n==1U)
				{
				I2C3->CR1&=~I2C_CR1_ACK;
					I2C3->CR1|=I2C_CR1_STOP;
					while(!(I2C3->SR1&I2C_SR1_RXNE)){;}
					*data++=I2C3->DR;
						break;
				}
			else
					{
					
					while(!(I2C3->SR1&I2C_SR1_RXNE)){;}
						(*data++)=I2C3->DR;
							n--;
					
					}	
				
			
		}	
		
}
