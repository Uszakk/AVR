//Functions and macros for setup and operating rotary encoder
#include <avr/io.h>
#include <util/delay.h>
#include "Encoder.h"

//Initializtion of encoder (should be placed later in code for prevent overwrite)
void Encoder_init(void){
	ENCODER_DDR &= ~(_BV(ENCODER_A) | _BV(ENCODER_B)); //Setting pins as inputs
	ENCODER_PORT |= (_BV(ENCODER_A) | _BV(ENCODER_B)); //Setting pull-ups
}

//Function for decoding the Gray's code
//Returns coresponding integer value to the binary input Gray's code 
inline uint8_t decode(uint8_t grays_code){
	switch(grays_code){
		case 0b01 : return 1;
		case 0b11 : return 2;
		case 0b10 : return 3;
		default : return 0;
	}
}

//Function for reading the encoder state
//Returns -1, 0 or 1 depending on movement of encoder
uint8_t Encoder_read(void){
	static uint8_t delay_counter[2]; //Two counters (one for each input) that must be equal to zero to read the state again 
	uint8_t delay_flag; //Permission for making delay in reading the state
	static uint8_t last_state; //Last state (in Gray's code) of the encoder
	uint8_t input_state; //State of encoder checked at the beginning of the function
	static uint8_t current_state; //Latched 'input_state' that is prevent form changing by 'delay_counter'
	int8_t diff_state; //Diffirence in positions of encoder (based on this variable function calculates direction of movement)
	static int8_t position_counter; //Counter of position changes (every 4 changes function returns non zero value) that is incremented or decremented based on movemnt
	
	input_state = ENCODER_PIN & (_BV(ENCODER_A) | _BV(ENCODER_B)); //Reading the input state of encoder
	if((delay_counter[0] == 0) && (input_state ^ last_state & _BV(ENCODER_A))){ //Checking if 'delay_counter' is zero and if state of encoder A input changed since last function call
		delay_counter[0] = IGNORE_TIME; //Setting up the 'delay_counter' with IGNORE_TIME macro
		current_state &= ~_BV(ENCODER_A); // Writing the current state of the encoder (only A input state here)
		current_state |= (input_state & _BV(ENCODER_A));
	}
	if((delay_counter[1] == 0) && (input_state ^ last_state & _BV(ENCODER_B))){ //Checking if 'delay_counter' is zero and if state of encoder B input chnged since last function call
		delay_counter[1] = IGNORE_TIME; //Setting up the 'delay_counter' with IGNORE_TIME macro
		current_state &= ~_BV(ENCODER_B); //Writing the current state of the encoder (only B input here)
		current_state |= (input_state & _BV(ENCODER_B));
	}

	delay_flag = 0; //Setting up the delay permission to 0 (no permission)
	if(delay_counter[0] != 0){ //Checking up if the 'delay_counter' of A input is non-zero value
		delay_flag = 1; //If the 'delay_counter' is non-zero the delay will be activated
		delay_counter[0]--; //Counting down the IGNORE_TIME
	}
	if(delay_counter[1] != 0){ //Checking up if the 'delay_counter' of B input is non-zero value
		delay_flag = 1; //If the 'delay_counter' is non-zero the delay will be activated
		delay_counter[1]--; //Counting down the IGNORE_TIME
	}
	if(delay_flag == 1) _delay_ms(1); //If delay permission flag is set input 1 ms delay

	diff_state = decode(current_state) - decode(last_state); //Calculating the difference in positions (position codes are decoded by inline function decode())
	last_state = current_state; //Saving the current state in static variable 'last_state' to be able to read it in next function call
	if(diff_state == 1 || diff_state == -3){ //Checking if encoder rotated clockwise
		position_counter++; //If encoder rotated clockwise 'position_counter' increments
		if(position_counter % 4 == 0){ //Every 4 state changes in one direction (clockwise here) the function returns 1 
			position_counter = 0; //Resetting 'position_counter'
			return 1; //Function returns 1 if encoder rotated clockwise
		}
	}
	if(diff_state == -1 || diff_state == 3){ //Checking if encoder rotated counter-clockwise
		position_counter--; //If encoder rotated counter_clockwise 'position_counter' decrements
		if(position_counter % -4 == 0){ //Every 4 state changes in one direction (counter-clockwise here) function returns -1
			position_counter = 0; //Resetting 'postion_counter'
			return -1; //Function returns 1 if encoder rotated counter-clockwise
		}
	}
	return 0; //Function returns 0 if there was no change in position or if encoder did not end the rotation cycle
}
