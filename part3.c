#include <msp430.h>

#define RS0 P2OUT &= ~BIT0
#define RS1 P2OUT |= BIT0

#define RW0 P2OUT &= ~BIT1
#define RW1 P2OUT |= BIT1

#define E0 P2OUT &= ~BIT2
#define E1 P2OUT |= BIT2


//Enable signal
void enable(){
    E1;
    __delay_cycles(1600);
    E0;
}
void enable_l(){
    E0;
    __delay_cycles(1600);
    E1;
}
//Verify busy flag and wait until it is cleared
void busy_check(){
    P1DIR &= ~BIT7;
    while((P1IN & BIT7) == 1)
        enable_l();
    P1DIR |= BIT7;
}
//Pass a command to the LCD module
void command(unsigned char com){
    busy_check();
    RS0;
    RW0;
    P1OUT = (0x00 & P1OUT) | (com);
    enable();
}
//Write data to the LCD module
void data(unsigned char data){
    busy_check();
    RS1;
    RW0;
    P1OUT = (0x00 & P1OUT) | (data);
    enable();
}
//Clear the display
void clear(){
    command(0x01);
}
//Change the cursor's position
void change_pos(unsigned char pos){
    command(0x80 | pos);
}
//Send a character array to the LCD
void send_string(char *s){
    while(*s){
        data(*s);
        s++;
    }
}
//LCD initialization sequence
void init_lcd(){
    P1DIR |= 0xFF;
    P2DIR |= 0xFF;
    P1OUT &= 0x00;
    P2OUT &= 0x00;
    command(0x38); //Function set
    command(0x0E); //Display on/off
    clear();
    command(0x06); //Entry mode set
    change_pos(0x00); //Initial pos to 0x00
}

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    init_lcd();
    send_string("Hello World!");
    while(1);
}
