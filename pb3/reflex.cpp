#define ISR
#define F_CPU 8000000
#define cli()
#define sei()
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>




const uint8_t SORTIE = 0xFF;
const uint8_t ENTREE = 0x00;
const uint8_t ROUGE = 0x01;
const uint8_t VERT = 0x02;



// &= ~(1 << cs1) change to  0 

void initialisation(void) {

  cli();

  DDRD = SORTIE;
  TCNT1 = 0;
  EIMSK |= (1 << INTF0); // enable INT0
  EICRA |= (1 << ISC00) | (1 << ISC01); // int0 REGISTER 11 FOR RISING EDGE 
  sei();

}





void setPWM(uint16_t right , uint16_t left ) {

 

  // mode CTC du timer 1 avec horloge divisée par 1024

  // interruption après la durée spécifiée

  
  OCR1A = right;
  OCR1B = left;
  
  
  TCCR1A |= ( 1 << WGM12) | (1 << COM1A1) | (1 << COM1B1) ;  // CKEAR IB CINOARE NATCH WHEN UP COUNTING
  TCCR1B |= ( 1 << CS11)  ; // 173, divide clock by 8 
  


  
  
  // enable outcompar ebmatch interrupt flag on both 

}

int main() {
	
	
	
	

	initialisation();
	
	 
	
	for(;;) {
		
		setPWM( 255 , 255);
		_delay_ms(2000);
		setPWM( 120 , 120);
		
		
	}

	
	
		


 

  

}
