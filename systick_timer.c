#include "stm32f10x.h"    
#include "systick_timer.h"


void systick_init(void){
	SysTick -> CTRL = 0;
	SysTick -> LOAD = 0x00FFFFFF;
	SysTick -> VAL = 0;
	SysTick -> CTRL |= (1<<0)|(1<<2);
}
 
void DelayMillis(void){
	SysTick -> LOAD = 72000 -1;
	SysTick -> VAL = 0;
	while ((SysTick -> CTRL & (1<<16)) == 0);
}

void DelayMs(unsigned long ms)
{
	while (ms--){
		DelayMillis();
	}
}

void systick_int_start(void){
	__disable_irq();
	SysTick -> CTRL = 0;
	SysTick -> LOAD = 72000-1;
	SysTick -> VAL = 0;
	SysTick -> CTRL |= (1<<0)|(1<<2)|(1<<1);
	__enable_irq();
}

void systick_int(unsigned short usart_1_mgr[], unsigned short usart_2_mgr[], unsigned short usart_3_mgr[])
{
	if (usart_1_mgr[0] != 0)
	{
		if (usart_1_mgr[6] == 0)
		{
			usart_1_mgr[0] = 0;
			usart_1_mgr[1] = 1;
			systick_init();
		}
		else 
		{
			usart_1_mgr[6] --;
		}
	}
	else if (usart_2_mgr[0] != 0)
	{
		if (usart_2_mgr[6] == 0)
		{
			usart_2_mgr[0] = 0;
			usart_2_mgr[1] = 1;
			systick_init();
		}
		else 
		{
			usart_2_mgr[6] --;
		}
	}
	else if (usart_3_mgr[0] != 0)
	{
		if (usart_3_mgr[6] == 0)
		{
			usart_3_mgr[0] = 0;
			usart_3_mgr[1] = 1;
			systick_init();
		}
		else 
		{
			usart_3_mgr[6] --;
		}
	}
}
