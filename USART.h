#define F_CPU 8000000UL
#define BAUD 9600
#include <avr/io.h>
#include <util/setbaud.h>

void USART_init(void);
uint8_t USART_receive(void);
void USART_transmit(uint8_t data);
