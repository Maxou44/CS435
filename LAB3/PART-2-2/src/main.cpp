/*----------------------------------------------------------------------------
LAB EXERCISE - DIGITAL INPUTS AND OUTPUTS
PROGRAMMING USING MBED API
 ----------------------------------------
 In this exercise you need to use the mbed API functions to:
 
	1) Define BusIn, BusOut interfaces for inputs and outputs
	2) The RGB LED is controlled by the buttons:
			+ Button 1 - light RED
			+ Button 2 - light BLUE
			+ Button 3 - light GREEN
			+ Button 4 - light WHITE (RED, GREEN and BLUE at the same time)
			
	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"

//Define input bus
DigitalIn  button_1(D2);
DigitalIn  button_2(D3);
DigitalIn  button_3(D4);
DigitalIn  button_4(D5);

//Define output bus for the RGB LED
DigitalOut led_r(D6);
DigitalOut led_g(D7);
DigitalOut led_b(D8);

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	int i = 0;
	while(1){
		
		//Check which button was pressed and light up the corresponding LEDs
		//Write your code here
		if (!button_1 || !button_2 || !button_3 || !button_4) {
			i++;			
			if (i == 30) // 30 => blue
					led_b = !led_b;
			else if (i == 20) // 20 => green
					led_g = !led_g;
			else if (i == 10) // 10 => red
					led_r = !led_r;
			wait(0.25);
		}
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
