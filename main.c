#include "stm32f10x.h"
#include "gp_driver.h"
#include "systick_timer.h"
#include "Usart.h"
#include <string.h>

char ch[5] = "HELLO";
unsigned short Usart1_Signal = 0;; 
unsigned short   Usart1_Counter = 0; 
unsigned short usart_1_mgr[7] = {0, 0, 0, 0, 0, 0, 0};
char Usart1_str[10];

unsigned short Usart2_Signal = 0; 
unsigned short Usart2_Counter = 0; 
unsigned short usart_2_mgr[7] = {0, 0, 0, 0, '0', 0, 0};
char Usart2_str[10];

unsigned short Usart3_Signal = 0; 
unsigned short Usart3_Counter = 0; 
unsigned short usart_3_mgr[7] = {0, 0, 0, 0, '0', 0, 0};
char Usart3_str[]="";

char chr;
int main(void)
{
	systick_init();
	USART_init(2, 9600);
	USART_init(3, 9600);
	DelayMs(100);
	Send_Data(2, ch);
	Send_Data(3, ch);
	while(1){
		if (usart_2_mgr[1] == 1){
			Send_Data(3, Usart2_str);
			usart_2_mgr[1] = 0;
			Empty_Str(Usart2_str);
		}
		if (usart_3_mgr[1] == 1){
			Send_Data(2, Usart3_str);
			usart_3_mgr[1] = 0;
			Empty_Str(Usart3_str);
		}
	}
}


void USART2_IRQHandler(void){
	USART_ISR(2, usart_2_mgr, Usart3_str);

}

void USART3_IRQHandler(void){
	USART_ISR(3, usart_3_mgr, Usart3_str);
}

void SysTick_Handler(void)
{
	systick_int(usart_1_mgr, usart_2_mgr, usart_3_mgr);
}


















