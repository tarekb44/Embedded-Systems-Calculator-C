#ifndef LCD_INIT_H
#define LCD_INIT_H

#include "PLL.h"

// Clock for GPIO ports
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *) 0x400FE108))

/* Pin Defines
  Take the base address + bit constant
*/

// Port A -> 
//     - PA3 : Register Select (RS)
//     - PA2 : Enable Pin (E)
#define GPIO_PORTA_DATA_R      (*((volatile unsigned long*) 0x400043FC))
#define GPIO_PORTA_DIR_R       (*((volatile unsigned long*) 0x40004400))
#define GPIO_PORTA_AFSEL_R     (*((volatile unsigned long*) 0x40004420))
#define GPIO_PORTA_PUR_R       (*((volatile unsigned long*) 0x40004510))
#define GPIO_PORTA_DEN_R       (*((volatile unsigned long*) 0x4000451C))
#define GPIO_PORTA_CR_R        (*((volatile unsigned long*) 0x40004524))
#define GPIO_PORTA_AMSEL_R     (*((volatile unsigned long*) 0x40004528))
#define GPIO_PORTA_PCTL_R      (*((volatile unsigned long*) 0x4000452C))
#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))

// define the register select (PA3) and Enable (PA2)
#define ENPin (*((volatile unsigned long *) 0x40004010))  // PA2 
#define RSPin (*((volatile unsigned long *) 0x40004020))  // PA3 

// PORT B -> Control the data pins of the LCD
//     - PB3 : D7
//     - PB2 : D6
//     - PB1 : D5
//     - PB0 : D4
#define GPIO_PORTB_DATA_R      (*((volatile unsigned long *) 0x400053FC))
#define GPIO_PORTB_DIR_R       (*((volatile unsigned long *) 0x40005400))
#define GPIO_PORTB_AFSEL_R     (*((volatile unsigned long *) 0x40005420))
#define GPIO_PORTB_PUR_R       (*((volatile unsigned long *) 0x40005510))
#define GPIO_PORTB_DEN_R       (*((volatile unsigned long *) 0x4000551C))
#define GPIO_PORTB_CR_R        (*((volatile unsigned long *) 0x40005524))
#define GPIO_PORTB_AMSEL_R     (*((volatile unsigned long *) 0x40005528))
#define GPIO_PORTB_PCTL_R      (*((volatile unsigned long *) 0x4000552C))
#define GPIO_PORTB_LOCK_R       (*((volatile unsigned long *)0x40005520))

// define the entire port
#define PortB  (*((volatile unsigned long *) 0x4000503C)) // PB0 - 3

// define the individual ports  
#define PortD7 (*((volatile unsigned long *) 0x40005020)) // PB3
#define PortD6 (*((volatile unsigned long *) 0x40005010)) // PB2
#define PortD5 (*((volatile unsigned long *) 0x40005008)) // PB1
#define PortD4 (*((volatile unsigned long *) 0x40005004)) // PB0

#define LOW 0x00
#define MHZ 80000
#define UHZ 80

#define PORT03 0x0F
#define PORT23 0x0C


void InitDisplayPort(void);

/*
    * Argument: Incoming nibble, sets PORTS B3 - B0 in order to manipulate 
    * D7 - D4
*/
void SendDisplayNibble(unsigned long nibble);
void SendDisplayByte(unsigned long byte, int RSMode);
void ENHighLow(void);

#endif