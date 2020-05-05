/*
 * testnaja.c
 *
 * Created: 5/2/2020 12:11:49 PM
 * Author : darkl
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRD = 0x00;	
	DDRC = 0xFF;
	PCICR = 0x04;
	PCMSK2 = 0b11111100;
	initial_read_sw_and_display();
	sei();
	while (1){}
}

void initial_read_sw_and_display(void){
	unsigned char a,b,c,temp;
	temp = PIND;
	a = (temp>>2) & 0x03;
	b = (temp>>4) & 0x03;
	c = (temp>>6) & 0x03;
	if (a > c){
		temp = a;
		a = c;
		c = temp;
	}

	if (a > b){
		temp = a;
		a = b;
		b = temp;
	}

	if (b > c){
		temp = b;
		b = c;
		c = temp;
	}
	b = (b<<2);
	c = (c<<4);
	temp = a | b | c;
	PORTC = temp;
}

ISR(PCINT2_vect){
	initial_read_sw_and_display();
}