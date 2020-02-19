#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	P2DIR |= BIT5; //Port 2.5 as output
	while(1){
	    P2OUT |= BIT5; //Turn on LED
	    __delay_cycles(100000); //Delay of 100ms
	    P1OUT &= ~BIT0; //Turn off LED
	    __delay_cycles(100000);
	}



	return 0;
}
