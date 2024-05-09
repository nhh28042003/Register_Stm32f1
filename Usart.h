#include <stdint.h>

void USART_init(uint8_t type_USART, unsigned long speed_Baud);
uint16_t fraction_USART(uint8_t type_USART,unsigned long speed_Baud);
unsigned long mantissa_USART(uint8_t type_USART,unsigned long speed_Baud);
char RX_USART(uint8_t USART);
void TX_USART(uint8_t USART, char ch);
void USART_ISR(unsigned short usart, unsigned short usart_mgr[], char str[]);
void Send_Data(unsigned short usart, char str[]);
void Empty_Str(char str[]);
void USART_msg(unsigned short usart, char str[], unsigned short str_mgr[]);
