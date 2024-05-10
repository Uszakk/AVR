#define F_CPU 8000000UL
#define BAUD 9600
#include <avr/io.h>
#include <util/setbaud.h>

void USART_init(void){
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE; //Setting the UBRR register value
    UCSRB = _BV(TXEN)|_BV(RXEN); //Enabling transmitter and reciver
    UCSRC = _BV(URSEL)|_BV(UCSZ1)|_BV(UCSZ0)|_BV(USBS); //Setting frame format as 8 bits of data and 2 stop bits
}

uint8_t USART_receive(void){
    loop_until_bit_is_set(UCSRA, RXC); //Waiting for reception complete
    return UDR; //Returning UDR register content
}

void USART_transmit(uint8_t data){
    loop_until_bit_is_set(UCSRA, UDRE); //Waiting for emptying transmitt buffer
    UDR = data; //Writing data to UDR register
}


