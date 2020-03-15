#ifndef __IO_H
#define __IO_H

#ifndef NOP
#define NOP __asm__ __volatile__ ("nop")
#endif

// The n00bs at avr-libc decided to change
// PC5 to PORTC5 and such with the 328P...
// which
// 1) breaks compatibility with old code, and
// 2) breaks with the official ATmega328P datasheet conventions
//    for pin labels and C code examples!!!
// So we have to go to the trouble of all this.

#ifndef PB0
#define PB0 0
#define PB1 1
#define PB2 2
#define PB3 3
#define PB4 4
#define PB5 5
#define PB6 6
#define PB7 7
#define PC0 0
#define PC1 1
#define PC2 2
#define PC3 3
#define PC4 4
#define PC5 5
#define PC6 6
#define PC7 7
#define PD0 0
#define PD1 1
#define PD2 2
#define PD3 3
#define PD4 4
#define PD5 5
#define PD6 6
#define PD7 7
#endif

#endif
