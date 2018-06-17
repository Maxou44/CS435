/*----------------------------------------------------------------------------
 Switches C file
 *----------------------------------------------------------------------------*/
#include "switches.h"

void init_switches(void){
	//Start clocks for ports A and D
	RCC->AHB1ENR |= RCC_PORTA_MASK | RCC_PORTB_MASK;

	//Set pins to pull-up mode
	GPIOA->PUPDR |= PUPDR_0(SWITCH_1);
	GPIOB->PUPDR |= PUPDR_0(SWITCH_2) | PUPDR_0(SWITCH_3) | PUPDR_0(SWITCH_4);
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2016*************************************
