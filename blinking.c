#include "stm32f4xx.h"
volatile uint64_t x;
void blink_init()
{
__disable_irq();
	RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;
	GPIOG->MODER|=(1<<26)|~(1<<27);
	SysTick->LOAD=72000-1;
	SysTick->VAL=0;
	SysTick->CTRL=7; //0b00000111;
	__enable_irq();

}
void SysTick_Handler(void){
x++;
if(x%1000==0)
{
GPIOG->ODR^=(1<<13);
}
}