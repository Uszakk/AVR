//Functions for operating the encoder (without encoder switch)

#include <avr/io.h>

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
