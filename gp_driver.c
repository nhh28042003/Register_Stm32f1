#include "gp_driver.h"


void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt){
	volatile unsigned long * CR;
	unsigned short tPIN = pin;
	unsigned short offset = 0x00;
	if (pin > 7){
		tPIN -= 8;
		offset = 0x01;
	}
	if (port == 1){
		// Enable GPIOA
		RCC_APB2ENR |= (1<<2);
		CR = (volatile unsigned long *)(&GPIO_A + offset);
	}
	else if (port == 2){
		// Enable GPIOB
		RCC_APB2ENR |= (1<<4);
		CR = (volatile unsigned long *)(&GPIO_B + offset);
	}
	else{
		// Enable GPIOC
		RCC_APB2ENR |= (1<<6);
		CR = (volatile unsigned long *)(&GPIO_C + offset);
	}
	*CR &= (unsigned long)~(0xf <<(tPIN)*4);
	*CR |= ((unsigned long)(dir << (tPIN *4 )) | (unsigned long)(opt << (tPIN*4+2)));
}

int IDR_GP(unsigned short port, unsigned short pin){
	volatile unsigned long *IDR;
	unsigned int offset = 0x08;
	int state = 0 ;
	if (port == 1){
		IDR = (volatile unsigned long *)(&GPIO_A + offset);
	}
	else if (port == 2){
		IDR = (volatile unsigned long *)(&GPIO_B + offset);
	}
	else{
		IDR = (volatile unsigned long *)(&GPIO_C + offset);
	}
	state = (int)((*IDR & (1<<pin))>>pin);
	return state;
}
void ODR_GP(unsigned short port, unsigned short pin, unsigned short state){
	volatile unsigned long * ODR;
	unsigned int offset = 0x0C;
	if (port == 1){
		ODR = (volatile unsigned long *)(&GPIO_A + offset);
	}
	else if (port == 2){
		ODR = (volatile unsigned long *)(&GPIO_B + offset);
	}
	else{
		ODR = (volatile unsigned long *)(&GPIO_C + offset);
	}
	if (state == 1){
		*ODR |= (1<<pin);
	}
	else {
		*ODR &= ~(1<<pin);
	}
}

void toggle_GP(unsigned short port, unsigned short pin){
	if (IDR_GP(port, pin)){
		ODR_GP(port, pin, 0);
	}else {
		ODR_GP(port, pin, 1);
	}
}
