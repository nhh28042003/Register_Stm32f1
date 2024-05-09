
#define RCC_APB2ENR (*((volatile unsigned long*) 0x40021018))


#define GPIO_A 		(*((volatile unsigned long*) 0x40010800))
#define GPIO_B 		(*((volatile unsigned long*) 0x40010C00))
#define GPIO_C 		(*((volatile unsigned long*) 0x40011000))


// List ports
#define PA 		1
#define PB		2
#define PC		3

// Directions
#define IN				0
#define OUT_10		1
#define OUT_2			2
#define OUT_50		3

// Option Directions
// Input
#define I_AN 				0
#define I_FI				1
#define I_PP_PU			2

// Output
#define O_PP				0
#define O_OD				1
#define O_AF_PP			2
#define O_AF_OD			3

// Status definition
#define LOW 0
#define HIG 1

void init_GP(unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt);

int IDR_GP(unsigned short port, unsigned short pin);

void ODR_GP(unsigned short port, unsigned short pin, unsigned short state);

void toggle_GP(unsigned short port, unsigned short pin);
