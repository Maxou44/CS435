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
#include "rtos.h"
#include "pindef.h"

// Button
DigitalIn  button(D4);

//Define output bus for the RGB LED
DigitalOut led_r(D6);
DigitalOut led_g(D7);
DigitalOut led_b(D8);

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

AnalogIn volume(A0);
AnalogIn pitch(A1);
PwmOut speaker(D5);

Thread thread1;
Thread thread2;
Thread thread3;
Thread thread4;

int audio(){
	speaker = 0;
	speaker.period(0);
	while(1){
		speaker = volume / 10;
		speaker.period((3.125 - (3 * pitch)) / 1000);
		wait_ms(1);
	}
}

int light(){
	led_r = !led_r;
	led_g = !led_g;
	led_b = !led_b;
	 wait(1);
}

int temp(){
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
		pc.printf("Temp: %f\r\n", temp);
}

int counter() {
	int nb = 0;
	while(1){
		if (!button)
		{
			nb++;
			if (pc.writeable())
				pc.printf("Button: %d\r\n", nb);
			wait(1);
		}
	}
}

int main(){
	/*Thread thread1(audio);
	Thread thread2(light);
	Thread thread3(temp);
	Thread thread4(counter);*/
	
	
	thread1.start(audio);
	thread2.start(light);
	thread3.start(temp);
	thread4.start(counter);
	
	while(1);
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
