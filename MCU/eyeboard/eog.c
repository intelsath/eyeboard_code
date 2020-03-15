//EOG monitoring system
//Decodes (with ADC) EOG potentials amplified and filtered by the circuit
//Luis Cruz

//Version with op amp follower

#define F_CPU 14745600

#include <stdio.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#include "../libnerdkits/delay.h"
#include "../libnerdkits/lcd.h"
#include "../libnerdkits/uart.h"
#include "../libnerdkits/io_328p.h"

// PIN DEFINITIONS:
// PC0 -- EOG input

volatile int32_t X; //info to serial
volatile int32_t z;

void adc_init() {
  // set analog to digital converter to read PC0 (ADC0)
  ADMUX = 0;

  //Setting ADEN and ADCSRA will start ADC
  // Prescaler is 1/128 => 14745600/128 115200Hz
  // Therefore the ADC clock runs at 115.2kHz.
  ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);

  // fire the first ADC conversion, writes a logical one to ADSC in ADCSRA
  ADCSRA |= (1<<ADSC);

  sei();
}

volatile uint16_t adc_read() {

  // read from the ADCL/ADCH registers, and combine the result
  // Note: ADCL must be read first (datasheet pg. 259)
  volatile uint16_t result = ADCL;
  volatile uint16_t temp = ADCH;
  result = result + (temp<<8);

  // set ADSC bit to get the *next* conversion started
  ADCSRA |= (1<<ADSC);

  return result;
}


volatile int right = 0;
volatile int left = 0;
volatile int center = 0;

volatile int centerTimer;//decides wheter or not the timer should be triggered according to the ADC received, if slope == 0 then timer is triggered
volatile int32_t centerThe_time; //time at center

ISR(ADC_vect)   //ADC interrupt
{

     //Center: Due to the capacitor ability to remove the DC and the resistors dividers, the constant (V2-V1) voltage without slope should be ~2.5V
     // I = C * dv/dt, the derivative of a constant is cero; therefore if I(current) equals cero, voltage equals cero because V = IR
      if( adc_read() >= 475 && adc_read() <= 483 ){ center = 1; left = 0; right = 0; }

      if( center == 1 )
      {
          //set pins to high, +5V, do not send any info to other micro
          X = 1;
          z = 0;
          centerTimer = 1;
      }


   //Detect eye movements if the timer is running. if timer is running the derivative of the signal is cero
   if( centerThe_time >= 50 ){
      //left: Slope should be positive at ~ +12 in adc units, then it will decrease, negative val shall be ignored.
      if( adc_read() >= 490 ){ left = 1; center = 0; right = 0; }

      //right: Slope should be negative at ~ -50 in adc units. positive val shall be ignored.
      if( adc_read() <= 450 ){ right = 1; left = 0; center = 0; }


      if( right == 1 )
      {
          X = 0;
          z = 0;
          centerTimer = 0;

      }


      if( left == 1 )
      {
          X = 2;
          z = 0;
          centerTimer = 0;

      }

   }




}

void realtimeclock_setup() {
  // setup Timer0:
  // CTC (Clear Timer on Compare Match mode)
  // TOP set by OCR0A register
  TCCR0A |= (1<<WGM01);
  // clocked from CLK/1024
  // which is 14745600/1024, or 14400 increments per second
  TCCR0B |= (1<<CS02) | (1<<CS00);
  // set TOP to 143
  // because it counts 0, 1, 2, ... 142, 143, 0, 1, 2 ...
  // so 0 through 143 equals 144 events
  OCR0A = 143;
  // enable interrupt on compare event
  // (14400 / 144 = 100 per second)
  TIMSK0 |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect)  {
  // when Timer0 gets to its Output Compare value,
  // one one-hundredth of a second has elapsed (0.01 seconds).

  //If the MCU detects a slope in the signal according to the ADC, the timer will be stopped
  //depending on the time, the user is free to move the eyes again; The time
  if( centerTimer == 1 )
  {
    centerThe_time++;
  }

      if( centerTimer == 0 )
    centerThe_time = 0;

  if( centerThe_time >= 100) centerThe_time = 100;
}


int main() {

    // init serial port
  uart_init();
  FILE uart_stream = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
  stdin = stdout = &uart_stream;

//adc
DDRC &= ~(1<<PC0);
PORTC &= ~(1<<PC0);

delay_ms(1000); //waits to capacitor until it discharges

  // start up the Analog to Digital Converter
  adc_init();


  while(1){

if ( centerTimer == 1 ) realtimeclock_setup(); //Activates timer <=> (if) time is equals one (That is, the MCU detected an eye movement)
if( z == 0 ){
      printf_P(PSTR("%d\r\n"), X ); //send info to serial port
z = 1;
}


  }

  return 0;
}
