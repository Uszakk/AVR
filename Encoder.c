//Functions for operating the encoder (without encoder switch)

#include <avr/io.h>

//Default connection of encoder
#define ENCODER_A PB0
#define ENCODER_B PB1
#define ENCODER_DDR DDRB
#define ENCODER_PORT PORTB
#define ENCODER_PIN PINB

//Initialization of encoder
void Encoder_init(void){
    ENCODER_DDR &= ~(_BV(ENCODER_A) | _BV(ENCODER_B));
    ENCODER_PORT |= _BV(ENCODER_A) | _BV(ENCODER_B);
}

//Reading the encoder state (returns -1, 0 or 1 depending on movement of encoder)
int8_t Encoder_read(void){
    static uint8_t last_position;
    static uint8_t counter;
    uint8_t current_position;
    int8_t delta_position;
    
    switch(ENCODER_PIN & (_BV(ENCODER_A) | _BV(ENCODER_B))){
        case 0b10: current_position = 3;
                   break;
        case 0b11: current_position = 2;
                   break;
        case 0b01: current_position = 1;
                   break;
        default:   current_position = 0;
                   break;
    }
    delta_position = last_position - current_position;
    last_position = current_position;
    if(delta_position != 0){
        if(delta_position == -1 || delta_position == 3){
            counter++;
            if(counter % 4 == 0){
                counter = 0;
                return 1;
            }
        }
    }
        if(delta_position == 1 || delta_position == -3){
            counter--;
            if(counter % -4 == 0){
                counter = 0;
                return -1;
            }
        }
    }
    return 0;
}
