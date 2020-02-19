#include <msp430.h>

#define RS0 P2OUT &= ~BIT0
#define RS1 P2OUT |= BIT0

#define RW0 P2OUT &= ~BIT1
#define RW1 P2OUT |= BIT1

#define E0 P2OUT &= ~BIT2
#define E1 P2OUT |= BIT2



void enable(){
    E1;
    __delay_cycles(1000);
    E0;
}
void enable_l(){
    E0;
    __delay_cycles(1000);
    E1;
}

void busy_check(){
    P1DIR &= ~BIT7;
    while((P1IN & BIT7) == 1)
        enable_l();
    P1DIR |= BIT7;
}

void command(unsigned char com){
    busy_check();
    RS0;
    RW0;
    P1OUT = (0x00 & P1OUT) | (com);
    enable();
}

void data(unsigned char data){
    busy_check();
    RS1;
    RW0;
    P1OUT = (0x00 & P1OUT) | (data);
    enable();
}

void clear(){
    command(0x01);
}

void change_pos(unsigned char pos){
    command(0x80 | pos);
}

void send_string(char *s){
    while(*s){
        data(*s);
        s++;
    }
}

void init_lcd(){
    P1DIR |= 0xFF;
    P2DIR |= 0xFF;
    P1OUT &= 0x00;
    P2OUT &= 0x00;
    command(0x38);
    command(0x0E);
    clear();
    command(0x06);
    change_pos(0x00);
}

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    init_lcd();
    P2DIR &= ~(BIT3);
    P2DIR &= ~(BIT4);

    int index = 0, next = 1, length = 16;
    char * list[] = {"arroz", "bizcocho", "carne", "donas", "egg roll", "farina", "galletas",
                     "hortalizas", "icee", "jalea", "kiwi", "limon", "manzana", "naranja", "pasteles",
                     "quenepa"};
    send_string(list[index]);
    change_pos(0x40);
    send_string(list[next]);
    while(1){
        if((P2IN & BIT3) == 0){ //UP
            __delay_cycles(100000);
            next = index;
            index -= 1;
            if(index < 0){
                index = 15;
            }
            clear();
            change_pos(0x00);
            send_string(list[index]);
            change_pos(0x40);
            send_string(list[next]);

        }
        else if((P2IN & BIT4) == BIT4){ //DOWN
            __delay_cycles(100000);
            index = next;
            next += 1;
            if(next > length - 1){
                next = 0;
            }
            clear();
            change_pos(0x00);
            send_string(list[index]);
            change_pos(0x40);
            send_string(list[next]);

        }


    }
}
