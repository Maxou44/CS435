/*----------------------------------------------------------------------------
LAB EXERCISE - LOW LEVEL DIGITAL IO
 ----------------------------------------
Digital input: switches on a breadboard
Digital output: RGB LED on the board
Function: Use the GPIO peripheral to control LEDs

GOOD LUCK!
 *----------------------------------------------------------------------------*/
#include "leds.h"
#include "switches.h"

//Simple software debouncing
void delay(float time){
	volatile int i;
	for(i=0; i<1000000*time; i++);
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	//Initialise switches and LEDs
	init_RGB();
	
	init_switches();

	//Infinite loop
	while(1){
		
		// Button 1 => Red
		if(!(GPIOA->IDR >> SWITCH_1 & 0x1)){
			toggle_r();
			delay(1);
		}
		// Button 2 => Green
		if(!(GPIOB->IDR >> SWITCH_2 & 0x1)){
			toggle_g();
			delay(1);
		}
		// Button 3 => Blue
		if(!(GPIOB->IDR >> SWITCH_3 & 0x1)){
			toggle_b();
			delay(1);
		}
		// Button 4 => All
		if(!(GPIOB->IDR >> SWITCH_4 & 0x1)){
			toggle_all();
			delay(1);
		}
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
