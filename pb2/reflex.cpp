#define ISR
#define F_CPU 8000000
#define cli()
#define sei()
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



const uint8_t ROUGE = 0x01;
const uint8_t VERT = 0x02;



volatile uint8_t timerExpired;
volatile uint8_t pushbutton;




void initialisation(void) {

	  cli();
	  
	  DDRB = SORTIE;
	  DDRD = ENTREE;
	  
	  EIMSK |= (1 << INTF0); // enable INT0
	  EICRA |= (1 << ISC00) | (1 << ISC01); // int0 REGISTER 11 FOR RISING EDGE 
	  
	  sei();

}


ISR (INT0_vect) {

timerExpired = 1;

}


ISR ('edit here') {

pushbutton = 1;

// debounce

'edit here'

}


