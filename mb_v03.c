    /*****************************************************
This program was produced by the
CodeWizardAVR V1.25.7 beta 5 Professional
Automatic Program Generator
© Copyright 1998-2007 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 17.12.2009
Author  : F4CG                            
Company : F4CG                            
Comments: 


Chip type           : ATmega88
Program type        : Application
Clock frequency     : 18,432000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 256
*****************************************************/

#include <mega88.h>
#include <spi.h>
#include <delay.h> 
#include <stdlib.h>

#include "mb_graph.c"


#define ENABLE6   PORTB.0   
#define ENABLE8   PORTB.1   
#define ENABLE1   PORTB.2   

#define ENABLE13  PORTD.0   
#define ENABLE14  PORTD.1   
#define ENABLE15  PORTD.2   
#define ENABLE2   PORTD.3   
#define ENABLE3   PORTD.4
#define ENABLE7   PORTD.5
#define ENABLE4   PORTD.6
#define ENABLE5   PORTD.7   

#define ENABLE0   PORTC.0
#define ENABLE9   PORTC.2
#define ENABLE10  PORTC.3   
#define ENABLE11  PORTC.4   
#define ENABLE12  PORTC.5   

#define LATCH     PORTC.1

#define OFF 1
#define ON  0

unsigned char counter;
unsigned char timerflag;
unsigned int  timercounter;
unsigned int led;  

unsigned char seccounter;
unsigned char secflag;
   
unsigned char r;
unsigned char c;

unsigned int megacounter;
unsigned char mode;

unsigned char plusminus;

#define PLUS  0
#define MINUS 1

unsigned char phasecounter;


////////////////////////////////
// functions  

void SetChannel(unsigned char ch);

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void){
// Place your code here
   timercounter ++;
	if (timercounter == 3){
		timercounter = 0;
		//SetChannel(counter);
		counter ++;  
		if (counter == 16) counter = 0;
	}

}           

// Timer 2 overflow interrupt service routine
interrupt [TIM2_OVF] void timer2_ovf_isr(void){
// Place your code here
   seccounter++;
   if (seccounter == r){
      seccounter = 0;
      secflag = 1;
   }
}


// Declare your global variables here
void SetChannel(unsigned char ch){
	switch(ch){
		case 0:
			ENABLE0 = ON; ENABLE12  = OFF; 
			break;
		case 1:        
			ENABLE1 = ON; ENABLE13  = OFF; 
			break;
		case 2:
			ENABLE2 = ON; ENABLE14  = OFF; 
			break;
		case 3:
			ENABLE3 = ON; ENABLE15  = OFF; 
			break;
		case 4:
			ENABLE4 = ON; ENABLE0  = OFF; 
			break;               
		case 5:
			ENABLE5 = ON; ENABLE1  = OFF; 
			break;
		case 6:
			ENABLE6 = ON; ENABLE2  = OFF; 
			break;
		case 7:
			ENABLE7 = ON; ENABLE3  = OFF; 
			break;
		case 8:
			ENABLE8 = ON; ENABLE4  = OFF; 
			break;
		case 9:
			ENABLE9 = ON; ENABLE5  = OFF; 
			break;
		case 10:
			ENABLE10 = ON; ENABLE6 = OFF; 
			break;
		case 11:
			ENABLE11 = ON; ENABLE7 = OFF; 
			break;
		case 12:
			ENABLE12 = ON; ENABLE8 = OFF; 
			break;
		case 13:
			ENABLE13 = ON; ENABLE9 = OFF; 
			break;
		case 14:
			ENABLE14 = ON; ENABLE10 = OFF; 
			break;
		case 15:
			ENABLE15 = ON; ENABLE11 = OFF; 
			break;
		default:
			break;         
	}
}








void main(void){
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTB=0x00;
DDRB=0xFF;

// Port C initialization
// Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTC=0x00;
DDRC=0x7F;

// Port D initialization
// Func7=Out Func6=Out Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out 
// State7=0 State6=0 State5=0 State4=0 State3=0 State2=0 State1=0 State0=0 
PORTD=0x00;
DDRD=0xFF;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 22000,000 kHz
// Mode: Normal top=FFh
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x01;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer 1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: 85,938 kHz
// Mode: Normal top=FFh
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x06;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-14: Off
// Interrupt on any change on pins PCINT16-23: Off
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x01;
// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x00;
// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=0x01;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;

// SPI initialization
// SPI Type: Master
// SPI Clock Rate: 1375,000 kHz
// SPI Clock Phase: Cycle Half
// SPI Clock Polarity: Low
// SPI Data Order: MSB First
SPCR=0x51;
SPSR=0x00;

timerflag = 0;
timercounter = 0;

//ENABLE0 = OFF; ENABLE1 = OFF; ENABLE2 = OFF; ENABLE3 = OFF; ENABLE4 = OFF; ENABLE5 = OFF; ENABLE6 = OFF; ENABLE7 = OFF; ENABLE8 = OFF; ENABLE9 = OFF; ENABLE10 = OFF; ENABLE11 = OFF; ENABLE12 = OFF; ENABLE13 = OFF; ENABLE14 = OFF; ENABLE15 = OFF;

ENABLE0 = ON;
ENABLE1 = ON;
ENABLE2 = ON;
ENABLE3 = ON;
ENABLE4 = ON;
ENABLE5 = ON;
ENABLE6 = ON;
ENABLE7 = ON;
ENABLE8 = ON;
ENABLE9 = ON;
ENABLE10 = ON;
ENABLE11 = ON;
ENABLE12 = ON;
ENABLE13 = ON;
ENABLE14 = ON;
ENABLE15 = ON;

//ENABLE6 = ON;
//ENABLE3 = ON;
           
counter = 0;
seccounter = 0;
secflag = 0;
r = 15;
led = 0;
megacounter =0;
mode = 3;

plusminus = PLUS;
phasecounter = 0;
                        

#asm("sei")
	while (1){ 
		#asm("wdr")
		if (secflag){
         secflag = 0;  

			#define EFFECTS        4

			#define EFFECT_CHAIN   0
			#define EFFECT_RANDOM  1
			#define EFFECT_LINES   2
			#define EFFECT_SIN     3

			megacounter ++;
	      if (megacounter == 0xff){
	         megacounter = 0;
	         phasecounter = 0;
	         mode ++;          \
	         led = 0;
	         if (mode == EFFECTS){
	            mode = 0;
	         }
	      }
			
			switch (mode){
			   case EFFECT_CHAIN:
			      r = 16;
			      Effect_Chain();
			      break;
			   case EFFECT_RANDOM:   
			      r = 20;
			      Effect_Random();
			      break;
			   case EFFECT_LINES:   
			      r = 16;
			      Effect_Lines();
			      break;
			   case EFFECT_SIN:   
			      r = 16;
			      Effect_Sin();
			      break;
			   default:
			      mode = 0;
			      break;
			}
		}
	}
}
