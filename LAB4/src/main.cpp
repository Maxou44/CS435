/*----------------------------------------------------------------------------
LAB EXERCISE - Analog input and PWM
 ----------------------------------------
	Use two potentiometers to adjust the volume and pitch of the output sound wave.

	Inputs: potentiometers 1 and 2
	Output: speaker, PC

	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "pindef.h"

//Define variables
AnalogIn volume(A0);
AnalogIn pitch(A1);
PwmOut speaker(D6);

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	speaker = 0;
	speaker.period(0);
	while(1){
		speaker = volume / 10;
		speaker.period((3.125 - (3 * pitch)) / 1000);
		wait_ms(1);
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************
