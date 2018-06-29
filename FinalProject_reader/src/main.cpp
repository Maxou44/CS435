#include "mbed.h"
#include "pindef.h"

// Button
DigitalIn  button(PB_5);

// Serial debug connection
Serial pc(UART_TX, UART_RX);

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int send_long(){
		/*if (pc.writeable())
			pc.printf("-");*/
}

int send_short(){
		/*if (pc.writeable())
			pc.printf(".");*/
}

int main(){
	int pressed = 1;
	int timer = 0;
	while(1){
		
		if (button && !pressed)
		{
			pc.printf("KEY UP (T=%d)\r\n", timer);
			pressed = 1;
			if (timer > 1200)
				send_long();
			else
				send_short();
			
			timer = 0;
			
		}
		if (!button && pressed)
		{
			pc.printf("KEY DOWN\r\n");
			pressed = 0;
		}
		if (!pressed)
			timer++;
		
		wait(0.0001);
	}
}
