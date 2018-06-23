/*----------------------------------------------------------------------------
LAB EXERCISE - UART interface
SERIAL COMMUNICATION
 ----------------------------------------
	Print text to the PC via UART protocol
	
	Input: None
	Output: PC

	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "pindef.h"

// Serial tx, rx connected to the PC via an USB cable
Serial device(UART_TX, UART_RX, "COM1");

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
  /*
  Set the baudrate to 9600 bps
  Print "Hello mbed" to the PC serial monitor
  */
	if (device.writeable())
		device.printf("Hello mbed");
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
