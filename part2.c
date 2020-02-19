#include <msp430.h>


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    //Set 2.5 as output, and 2.3 as input
    P2DIR |= BIT5;
    P2DIR &= ~BIT3;
    while(1){
        if((P2IN & BIT3) == 0){ //2.3 button is pressed
            P2OUT |= BIT5; //LED on
        }
        else{
            P2OUT &= ~BIT5; //LED off
        }
    }
    return 0;
}
