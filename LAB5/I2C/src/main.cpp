/*----------------------------------------------------------------------------
LAB EXERCISE - I2C interface
SERIAL COMMUNICATION
 ----------------------------------------
	Access the temperature sensor via I2C interface, print the current temperature
	to the PC via UART
	
	Input: temperature sensor
	Output: PC
	
	GOOD LUCK!
 *----------------------------------------------------------------------------*/
#include "mbed.h"
#include "pindef.h"

//I2C interface
I2C temp_sensor(I2C_SDA, I2C_SCL);
Serial pc(UART_TX, UART_RX);

//I2C address of temperature sensor DS1631
const int temp_addr = 0x90;

char cmd[] = {0x51, 0xAA};
char read_temp[2];

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
	while(1){

		// Start Convert T command to the sensor
		temp_sensor.write(temp_addr, &cmd[0], 1, 0);
		wait_ms(1000);
		temp_sensor.write(temp_addr, &cmd[1], 1, 1);
		
		// Read the 16-bit temperature data
		temp_sensor.read(temp_addr, read_temp, 2, 0);
		
		// Convert temperature to Celsius
		float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);
		
		// Send data
		if (pc.writeable())
			pc.printf("%f\r\n", temp);
	}
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
