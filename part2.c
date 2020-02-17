#include <msp430.h>


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    P1DIR |= BIT0;
    P1DIR &= ~BIT3;
    P1OUT &= ~BIT0;
    while(1){
        if((P1IN & BIT3) == BIT3){
            P1OUT |= BIT0;
        }
        else{
            P1OUT &= ~BIT0;
        }
    }
    return 0;
}
