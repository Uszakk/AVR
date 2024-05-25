//Basic functions for operating USART transmition
#include <avr/io.h>
#include <util/setbaud.h>

//Default baudrate
#define BAUD 9600

//Initializaton of USART comunication
void USART_init(void);

//Function for reciving one frame (setted in initialization) of data by USART
//Returns one byte of data from UDR register
uint8_t USART_receive(void);

//Function for transmiting one frame (setted in initialization) of data by USART
void USART_transmit(uint8_t data);
