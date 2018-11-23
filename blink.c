#include <avr/io.h>
#include "MrLCDATmega32.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#define F_CPU 1000000

static volatile int pulse = 0;
static volatile int i = 0;

int main(void)
{
  int16_t count_a = 0; 
  char show_a[16];
  Initialise();
  DDRD = 0b11111011;
  DDRB= 0b11111111;
  _delay_ms(50);

  Initialise();

  GICR |= 1<<INT0;
  MCUCR |= 1<<ISC00;

  sei();
 
  while(1)
  { 
    PORTD |= 1<<PIND0;
    _delay_us(15);

    PORTD &= ~(1<<PIND0);
    count_a = pulse/58;

    if(count_a<30){
	PORTB=0b00000001;
	
    }
    else if(count_a<40){
	PORTB=0b00000001;
	_delay_ms(50);
        PORTB=0b00000000;
	//_delay_ms(50);
    }

    else if(count_a<50){
	PORTB=0b00000001;
	_delay_ms(100);
        PORTB=0b00000000;
	//_delay_ms(100);
    }

    else if(count_a<60){
	PORTB=0b00000001;
	_delay_ms(150);
        PORTB=0b00000000;
	//_delay_ms(150);
    }

   /* else if(count_a<70){
	PORTB=0b00000001;
	_delay_ms(200);
        PORTB=0b00000000;
	//_delay_ms(200);
    }

    else if(count_a<80){
	PORTB=0b00000001;
	_delay_ms(300);
        PORTB=0b00000000;
	//_delay_ms(300);
    }
    else if(count_a<90){
	PORTB=0b00000001;
	_delay_ms(400);
        PORTB=0b00000000;
	//_delay_ms(400);
    }
    else if(count_a<100){
	PORTB=0b00000001;
	_delay_ms(500);
        PORTB=0b00000000;
	//_delay_ms(500);
    }*/
    else if(count_a>=60){
	PORTB=0b00000000;
    }
else{
		PORTB=0b00000000;
	}    /*if(count_a<50){
	PORTB=0b00000001;
        
    }
    else{
	PORTB=0b00000000;
    }*/
    
    Send_A_String("Distance Sensor");
    GoToMrLCDLocation(1,2);
    Send_A_String("D =");
    itoa(count_a,show_a,10);
    Send_A_String(show_a);
    _delay_ms(200);
    Send_A_String(" ");
    GoToMrLCDLocation(13,2);
    Send_A_String("cm");
    GoToMrLCDLocation(1,1);
  }
}

ISR(INT0_vect)
{
  if(i == 1)
  {
    TCCR1B = 0;
    pulse = TCNT1;
    TCNT1 = 0;
    i = 0;
    
  }

  if(i==0)
  {
    TCCR1B |= 1<<CS10;
    i = 1;

  }
}
