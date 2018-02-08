#define ISR
#define F_CPU 8000000
#define cli()
#define sei()
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>







 enum etat_t {
  INIT = 0,
  S1 = 1,
  S2 = 2,

};

etat_t etat;
enum Couleur {ambre, rouge, vert};
Couleur couleur;

void afficherCouleur(Couleur couleur);
void allumerLED(Couleur couleur);
void afficherAmbre();
void changerSate();

const int DELAI_LONG = 30;
const int DELAI_COURT = 10;
const uint8_t ROUGE = 0x01;
const uint8_t VERT = 0x02;


const uint8_t SORTIE = 0xFF;
const uint8_t ENTREE = 0x00;
const uint8_t ETEINT = 0x00;
volatile uint8_t counter = 0; 

void initialisation(void) {

	  cli();
	  
	  DDRB = SORTIE;
	  DDRD = ENTREE;
	  
	  EIMSK |= (1 << INTF0); // enable INT0
	  EICRA |= (1 << ISC00) | (1 << ISC01); // int0 REGISTER 11 FOR RISING EDGE 
	  
	  sei();

}




ISR (INT0_vect) {

	// laisser un delai avant de confirmer la réponse du

	// bouton-poussoir: environ 30 ms (anti-rebond)

	_delay_ms(20);

	// se souvenir ici si le bouton est pressé ou relâché
	
	if (PIND & 0x04) {

		counter++;
		
	}
      
       
     

	// changements d'états tels que ceux de la

	// semaine précédente
	
	
	
	
	// Voir la note plus bas pour comprendre cette instruction et son rôle

	EIFR |= (1 << INTF0) ;

}








int main() {
	
	initialisation();
	
  etat = INIT;
		
	
	for (;;) {
		
		

		switch (etat) {

       case INIT:
      {
		   
		PORTB = ROUGE;  
        allumerLED(ambre);
        changerSate();
        break;
      }

    case S1:
      {
		
		PORTB = VERT;  
        allumerLED(rouge);
        changerSate()   ;
        break;
      }

    case S2:
      {
		  
		PORTB = ETEINT;  
        allumerLED(vert);
        changerSate() ;
        break;

      }

    };
    
    
		
		
	
	}
	
	
	
	
}
	
	



void allumerLED(Couleur couleur) {
  
  
    _delay_ms(30); //prendre en compte le debounce
    while (PIND & 0x04) {
      afficherCouleur(couleur);
    }
    
  
}



void afficherAmbre() {
	 PORTB = VERT;
      _delay_ms(DELAI_COURT);
      PORTB = ROUGE;
      _delay_ms(DELAI_COURT);
  }

void afficherCouleur(Couleur couleur){
	if(couleur == ambre)
		afficherAmbre();
		
	if(couleur == rouge)
		PORTB = ROUGE;
	if(couleur == vert)
		PORTB = VERT;
}

void changerSate() {
	
	switch (counter){
		
		case 1: { etat= S1; break;}
		case 2: { etat= S2; break;}
		case 3: { counter = 0; break;}
		case 0: {etat = INIT; break;}
	};
	
	
}
	
	
	/*
	
	if (counter == 1 ) {
		
		etat = S1;
	}
	
	if (counter == 2 ) {
		
		etat = S2;
		counter = 0;
	}
	
	
	if (counter ==0){
		
		etat = INIT;
		
	}
	
	
		
  
}
		
		*/
	
