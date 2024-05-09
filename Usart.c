#include "stm32f10x.h" 
#include "Usart.h" 
#include "gp_driver.h"
#include "systick_timer.h"

void USART_init(uint8_t type_USART, unsigned long speed_Baud){
	// Enable AF function for PIN
	unsigned long mantissa;
	unsigned long fraction;
	mantissa = mantissa_USART(type_USART,speed_Baud);
	fraction = fraction_USART(type_USART,speed_Baud);
	if (type_USART == 2){
		__disable_irq();
		RCC -> APB2ENR |= 1|(1<<2);
		RCC -> APB1ENR |= (1<<17);
		init_GP(PA, 2, OUT_50, O_AF_PP);
		init_GP(PA, 3, IN, I_PP_PU);
		USART2 -> BRR |= (mantissa<<4)|(fraction<<0);
		USART2 -> CR1 |= (1<<2)|(1<<3)|(1<<13);
		USART2 -> CR1 |= (1<<5);
		//USART2 -> CR1 |= (1<<7);
		NVIC_EnableIRQ(USART2_IRQn);
		__enable_irq();
	}else if (type_USART == 1){
		__disable_irq();
		RCC -> APB2ENR |= 1|(1<<2);
		RCC -> APB2ENR |= (1<<14);
		init_GP(PA, 9, OUT_50, O_AF_PP);
		init_GP(PA, 10, IN, I_PP_PU);
		USART1 -> BRR |= (mantissa<<4)|(fraction<<0);
		USART1 -> CR1 |= (1<<2)|(1<<3)|(1<<13);
		USART1 -> CR1 |= (1<<5);
		//USART1 -> CR1 |= (1<<7);
		NVIC_EnableIRQ(USART1_IRQn);
		__enable_irq();
	}else if (type_USART == 3){
		__disable_irq();
		RCC -> APB2ENR |= 1|(1<<3);
		RCC -> APB1ENR |= (1<<18);
		init_GP(PB, 10, OUT_50, O_AF_PP);
		init_GP(PB, 11, IN, I_PP_PU);
		USART3 -> BRR |= (mantissa<<4)|(fraction<<0);
		USART3 -> CR1 |= (1<<2)|(1<<3)|(1<<13);
		USART3 -> CR1 |= (1<<5);
		//USART3 -> CR1 |= (1<<7);
		NVIC_EnableIRQ(USART3_IRQn);
		__enable_irq();
	}
}

uint16_t fraction_USART(uint8_t type_USART,unsigned long speed_Baud){
	unsigned long f_CK = 36000000;
	double f_CK_float = 36000000.00;
	unsigned long Mantissa ;
	double Mantissa_float;
  uint16_t Fraction;
	float Fraction_float;
	
	if (type_USART == 1){
		f_CK = 72000000;
		f_CK_float = 72000000.00;
	}
	Mantissa_float = f_CK_float/(16* (double)speed_Baud);
	Mantissa = f_CK/(16*speed_Baud);
	Fraction_float = (Mantissa_float - Mantissa)*100;
	if (Fraction_float > 50){
		Fraction = (unsigned long)(Fraction_float*16/100) + 1;
	}else{
		Fraction = (unsigned long)(Fraction_float*16/100);
	}
	return Fraction;
}

unsigned long mantissa_USART(uint8_t type_USART,unsigned long speed_Baud){
	unsigned long f_CK = 36000000;
	unsigned long Mantissa;
	if (type_USART == 1){
		f_CK = 72000000;
	}
	Mantissa = f_CK/(16*speed_Baud);
	return Mantissa;
}

char RX_USART(uint8_t USART){
	char ch;
	if (USART == 1)
	{
		while((USART1 -> SR & (0x20)) == 0)
		{};
		ch = USART1 -> DR ;
	}
	else if (USART == 2)
	{
		while((USART2 -> SR & (0x20)) == 0)
		{};
		ch = USART2 -> DR ;
	}
	else if (USART == 3)
	{
		while((USART3 -> SR & (0x20)) == 0)
		{};
		ch = USART3 -> DR ;
	}
	return ch;
}

void TX_USART(uint8_t USART, char ch){
	if (USART == 1){
		while((USART1 -> SR & (1<<6)) == 0)
		{};
		USART1 -> DR = ch;
	}else if (USART == 2){
		while((USART2 -> SR & (1<<6)) == 0)
		{};
		USART2 -> DR = ch;
	}else if (USART == 3){
		while((USART3 -> SR & (1<<6)) == 0)
		{};
		USART3 -> DR = ch;
	}
}

void USART_ISR(unsigned short usart, unsigned short usart_mgr[], char str[])
{
	if (usart_mgr[2] == 0){
			str[usart_mgr[0]] = RX_USART(usart);
			if (usart_mgr[3]){
				if (str[usart_mgr[0]] == usart_mgr[4]){
					usart_mgr[1] = 1;
					usart_mgr[0] = 0;
				}
				else {
					usart_mgr[0] += 1;
				}
			}
			else{
				// Time strategy
				usart_mgr[0] ++;
				usart_mgr[6] = usart_mgr[5];
				systick_int_start();
			}
	}
	else {
		TX_USART(usart_mgr[2], RX_USART(usart));
	}
}	

void Send_Data(unsigned short usart, char str[]){
	uint8_t i = 0;
	while (str[i] != '\0'){
		TX_USART(usart, str[i]);
		i ++;
		DelayMs(1);
	}
}

void Empty_Str(char str[]){
	uint8_t i = 0;
	while (str[i] != '\0'){
		str[i] = '\n';
		i ++;
	}
}

void USART_msg(unsigned short usart, char str[], unsigned short str_mgr[]){
	unsigned long timeOut = 72000000;
	Send_Data(usart, str);
	while(str_mgr[1] == 0 && timeOut != 0)
	{
		timeOut --;
	}
	str_mgr[1] = 0;
}

