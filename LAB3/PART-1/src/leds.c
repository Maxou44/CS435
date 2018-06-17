/*----------------------------------------------------------------------------
 LED C file
 *----------------------------------------------------------------------------*/
#include "leds.h"

void init_RGB(void){
	//Start clocks for Port A, Port B and Port C
	RCC->AHB1ENR |= RCC_PORTA_MASK | RCC_PORTB_MASK | RCC_PORTC_MASK;

	//Set the pins to output mode
	GPIOB->MODER &= ~MODER(RED_LED);
	GPIOA->MODER &= ~MODER(GREEN_LED) | ~MODER(BLUE_LED);

	GPIOB->MODER |= MODER_0(RED_LED);
	GPIOA->MODER |= MODER_0(GREEN_LED) | MODER_0(BLUE_LED);

	//Set pins to push-pull output state
	GPIOB->OTYPER &= ~OTYPER(RED_LED);
	GPIOA->OTYPER &= ~OTYPER(GREEN_LED) | ~OTYPER(BLUE_LED);

	//Set pins to pull-down mode
	GPIOB->PUPDR &= ~PUPDR(RED_LED);
	GPIOA->PUPDR &= ~PUPDR(GREEN_LED) | ~PUPDR(BLUE_LED);

	GPIOB->PUPDR |= PUPDR_1(RED_LED);
	GPIOA->PUPDR |= PUPDR_1(GREEN_LED) | PUPDR_1(BLUE_LED);

	//Set pins to 50MHz
	GPIOB->OSPEEDR &= ~OSPEEDR(RED_LED);
	GPIOA->OSPEEDR &= ~OSPEEDR(GREEN_LED) | ~OSPEEDR(BLUE_LED);

	GPIOB->OSPEEDR |= OSPEEDR_1(RED_LED);
	GPIOA->OSPEEDR |= OSPEEDR_1(GREEN_LED) | OSPEEDR_1(BLUE_LED);

	//Set outputs high
	GPIOB->ODR |= ODR(RED_LED);
	GPIOA->ODR |= ODR(GREEN_LED) | ODR(BLUE_LED);
}

//Toggle state of red LED
void toggle_r(void){

	GPIOB->ODR ^= ODR(RED_LED);
}

//Toggle state of green LED
void toggle_g(void){

	//Write your code here
	GPIOA->ODR ^= ODR(GREEN_LED);
}

//Toggle state of blue LED
void toggle_b(void){

	//Write your code here
	GPIOA->ODR ^= ODR(BLUE_LED);
}

//Toggle state of all LEDs
void toggle_all(void){

	//Write your code here
	GPIOB->ODR ^= ODR(RED_LED);
	GPIOA->ODR ^= ODR(GREEN_LED);
	GPIOA->ODR ^= ODR(BLUE_LED);
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
