//Functions and macros for setup and operating rotary encoder
#include <avr/io.h>
#include <util/delay.h>

//Time in miliseconds that must past to read the encoder state again (it should be not longer than 255 ms because it is stored as uint8_t type)
#define IGNORE_TIME 5

//Default connection of encoder
#define ENCODER_A PB0
#define ENCODER_B PB1
#define ENCODER_DDR DDRB
#define ENCODER_PORT PORTB
#define ENCODER_PIN PINB

//Initialization of encoder
void Encoder_init(void);

//Reading the encoder state (returns -1, 0 or 1 depending on movement of encoder)
int8_t Encoder_read(void);
