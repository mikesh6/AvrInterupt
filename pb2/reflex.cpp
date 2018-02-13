#define ISR
#define F_CPU 8000000
#define cli()
#define sei()
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

const uint8_t SORTIE = 0xFF;
const uint8_t ENTREE = 0x00;
const uint8_t ROUGE = 0x01;
const uint8_t VERT = 0x02;



// &= ~(1 << cs1) change to  0 

void initialisation(void) {

  cli();
  DDRB = SORTIE;
  DDRD = ENTREE;
  EIMSK |= (1 << INTF0); // enable INT0
  EICRA |= (1 << ISC00) | (1 << ISC01); // int0 REGISTER 11 FOR RISING EDGE 
  sei();

}

ISR(TIMER1_COMPA_vect) {
	
	minuterieExpiree = 1;
	PORTB = ROUGE; 
	
	
}

ISR(INT0_vect) {



             _delay_ms(10);
  if (PIND & 0x04)   {
	boutonPoussoir = 1;
	  }
	  
				
    
  
  
  EIFR |= (1 << INTF0);

}

void partirMinuterie(uint16_t duree) {

  minuterieExpiree = 0;

  // mode CTC du timer 1 avec horloge divisée par 1024

  // interruption après la durée spécifiée

  TCNT1 = 0;
  OCR1A = duree;
  TCCR1A = 0;
  TCCR1B |= (1 << CS12) | ( 1 << CS10) | ( 1 << WGM12); // 173, divide clock by 1024 
  TCCR1C = 0;
  TIMSK1 |= (1 << 1);
  
  
  // enable outcompar ebmatch interrupt flag on both 

}

int main() {
	
	
	
	

	initialisation();
	
	   _delay_ms(10000);
		PORTB = ROUGE;
	
		 _delay_ms(100);
		 PORTB = 0x00;
		
		 partirMinuterie(8000);			
		 
		 
		do {
			
		
	 


	
	} while ( minuterieExpiree == 0 && boutonPoussoir == 0 );


	// Une interruption s'est produite. Arrêter toute

	// forme d'interruption. Une seule réponse suffit.

		
		

	// Verifier la réponse
	
	
	cli();
	
	
	if (boutonPoussoir == 1 ) {
		
		PORTB = VERT;
		
	}
    
	
	

	
	
		


 

  

}
