#define F_CPU 1000000UL
#define BAUD 9600
#include <avr/io.h>
#include <util/setbaud.h>

//USART initialization
void USART_init(void){
    UBRRH = UBRR_VALUE; //Setting the baud rate
    UBRRL = UBRR_VALUE; //Setting the baud rate
    UCSRC = _BV(URSEL) | _BV(USBS) | _BV(UCSZ1) | _BV(UCSZ0); //8 bits of data, 2 stop bits
    UCSRB = _BV(RXEN) | _BV(TXEN); //Enabling reciver and transmitter
}

//USART data transmission (one frame (up to 8 bits) per function call)
void USART_transmit(unsigned char data){
    loop_until_bit_is_set(UCSRA, UDRE); //Waiting for UDRE flag set (UDRE flag is set when transmit buffer is empty and ready for new data)
    UDR = data; //Writing 8 bits of data to UDR register
}

//USART data reception (one frame (up to 8 bits) per function call)
unsigned char USART_recive(void){
    loop_until_bit_is_set(UCSRA, RXC); //Waiting for RXC flag set (RXC flag is set when recive buffer is empty and ready for new data)
    return UDR; //Returning value of UDR register (recived data)
}
