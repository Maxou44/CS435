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

/*
Define the PWM speaker output
Define analog inputs
*/

//Define variables
AnalogIn volume(A0);
AnalogIn pitch(A1);
PwmOut speaker(D6);

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	speaker = 1;
	float lastPitch = 0;
	float newPitch = 0;
	float lastVolume = 0;
	float newVolume = 0;
	
	while(1){
		
		// Pitch
		newPitch = pitch.read();
		if (lastPitch != newPitch)
		{
			lastPitch = newPitch;
			speaker.period(newPitch);
			wait(0.5);
			
		}
		
		// Volume
		newVolume = volume.read();
		if (lastVolume != newVolume)
		{
			lastVolume = newVolume;
			speaker = newVolume;
			wait(0.5);
		}
		
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************
