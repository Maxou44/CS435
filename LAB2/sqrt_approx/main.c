/*----------------------------------------------------------------------------
LAB EXERCISE 5.2 - SQUARE ROOT APPROXIMATION
 ----------------------------------------
Write an assembly code subroutine to approximate the square root of an 
argument using the bisection method. All math is done with integers, so the 
resulting square root will also be an integer

GOOD LUCK!
 *----------------------------------------------------------------------------*/

__asm int my_sqrt(int x){
	
// R1 = x
// R2 = done
// R3 = a
// R4 = b
// R5 = c
// R6 = c_old	
	
SQRT_INIT
	LDR r1, [r0] // x in R1
	LDR r2, =0 // done = 0
	LDR r3, =0 // a = 0
	LDR r4, =0xFFFF // b = 0
	LDR r5, =0xFFFFFFFF // c = 0

SQRT_LOOP
	MOV r6, r5 // c_old = c
	ADDS r7, r3, r4 // a + b
	ASRS r7, r7, #1 // R7 >> 1 => Divide
	MOV r5, r7 // c = R7
	MOV r8, r7 // R8 = R7
	MUL r8, r5, r8 // R8 = c * c
	CMP r8, r1 // Compare c*c and x
	BEQ SQRT_DONE // Biger or equal => SQRT_DONE
	BLT SQRT_LESS // Less than => SQRT_LESS
	MOV r4, r5 // b = c
	B SQRT_END // GoTo SQRT_END
	
SQRT_LESS
	MOV r3, r5 // a = c
	B SQRT_END // GoTo SQRT_END

SQRT_DONE
	LDR r2, =1 // done = 1
	B SQRT_END ; // GoTo SQRT_END
 
SQRT_END
	CMP r2, #1 // Compare done and 1
	BEQ SQRT_RETURN // Bigger or equal => SQRT_RETURN
	BNE SQRT_CMP // 

SQRT_CMP
	CMP r6, r5 // Compare c_old and c
	BNE SQRT_LOOP
	BEQ SQRT_RETURN

SQRT_RETURN
	MOV r0, r5 // Put result in r0
	BX LR // End
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
int main(void){
	volatile int r, j=0;
	int i;
  r = my_sqrt(0);     // should be 0
  r = my_sqrt(25);    // should be 5
	r = my_sqrt(133); 	// should be 11
  for (i=0; i<10000; i++){
		r = my_sqrt(i);
    j+=r;
  }
	while(1)
		;
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2014*************************************
