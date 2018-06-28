#include "mbed.h"

// Button
DigitalIn  button(PB_5);

//Define output bus for the RGB LED
DigitalOut led_r(PB_10);
DigitalOut led_g(PA_8);
DigitalOut led_b(PA_9);

//I2C interface
I2C temp_sensor(I2C_SDA, I2C_SCL);
Serial pc(PA_2, PA_3);

//I2C address of temperature sensor DS1631
const int temp_addr = 0x90;
 
char cmd[] = {0x51, 0xAA};
char read_temp[2];

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

AnalogIn volume(PA_0);
AnalogIn pitch(PA_1);
PwmOut speaker(PB_4);

Thread thread1;
Thread thread2;
Thread thread3;

void audio(){
    while(1){
        speaker = volume / 10;
        speaker.period((3.125 - (3.0 * (float)pitch)) / 1000.0);
        wait_ms(1);
    }
}

void light(){
    while(1) {
        led_r = !led_r;
        led_g = !led_g;
        led_b = !led_b;
        wait(1);
     }
}

void temp(){
    // Start Convert T command to the sensor
   while(1) {
    temp_sensor.write(temp_addr, &cmd[0], 1, 0);
    wait(1);
    temp_sensor.write(temp_addr, &cmd[1], 1, 1);
    
    // Read the 16-bit temperature data
    temp_sensor.read(temp_addr, read_temp, 2, 0);
    
    // Convert temperature to Celsius
    float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);
    
    // Send data
    if (pc.writeable())
        pc.printf("Temp: %f\r\n", temp);
    }
}

void counter() {
    int nb = 0;
    while(1){
        if (!button)
        {
            nb++;
            if (pc.writeable())
                pc.printf("Button: %d\r\n", nb);
            wait(500);
        }
    }
}

int main(){
    thread1.start(light);
    thread2.start(temp);
    thread3.start(counter);
    audio();
}