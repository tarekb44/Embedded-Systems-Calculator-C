#ifndef KEYPAD_INIT_H
#define KEYPAD_INIT_H

#include "keypad_init.h"
#include "PLL.h"
#include "lcd_init.h"

#define SYSCTL_RCGC2_R          (*((volatile unsigned long*) 0x400FE108))

/////////////////////////// PORT E //////////////////////////
// PORT E -> Control the keypad rows 
//     - PE3 : Row 4
//     - PE2 : Row 3
//     - PE1 : Row 2
//     - PE0 : Row 1 
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *) 0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *) 0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *) 0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *) 0x4002451C))
#define GPIO_PORTE_CR_R         (*((volatile unsigned long *) 0x40024524))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *) 0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *) 0x4002452C))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *) 0x40024520))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *) 0x40024510))

// define the entire port PE0-PE3
#define PortE       (*((volatile unsigned long *) 0x4002403C))

// define the individual row ports  
#define Row4       (*((volatile unsigned long *) 0x40024020)) // PE3
#define Row3       (*((volatile unsigned long *) 0x40024010)) // PE2
#define Row2       (*((volatile unsigned long *) 0x40024008)) // PE1
#define Row1       (*((volatile unsigned long *) 0x40024004)) // PE0



/////////////////////////// PORT D //////////////////////////
// PORT D -> Control the keypad colomns
//     - PD3 : Colomn 4
//     - PD2 : Colomn 3
//     - PD1 : Colomn 2
//     - PD0 : Colomn 1 
#define GPIO_PORTD_DATA_R       (*((volatile unsigned long *) 0x400073FC))
#define GPIO_PORTD_DIR_R        (*((volatile unsigned long *) 0x40007400))
#define GPIO_PORTD_AFSEL_R      (*((volatile unsigned long *) 0x40007420))
#define GPIO_PORTD_DEN_R        (*((volatile unsigned long *) 0x4000751C))
#define GPIO_PORTD_CR_R         (*((volatile unsigned long *) 0x40007524))
#define GPIO_PORTD_AMSEL_R      (*((volatile unsigned long *) 0x40007528))
#define GPIO_PORTD_PCTL_R       (*((volatile unsigned long *) 0x4000752C))
#define GPIO_PORTD_LOCK_R       (*((volatile unsigned long *) 0x40007520))
#define GPIO_PORTD_PDR_R        (*((volatile unsigned long *) 0x40007514))

// define the entire port
#define PortD       (*((volatile unsigned long *) 0x4000703C)) // PD3 - PD0

// define the individual column ports  
#define Column4      (*((volatile unsigned long *)0x40007020)) //PD3 
#define Column3      (*((volatile unsigned long *)0x40007010)) //PD2
#define Column2      (*((volatile unsigned long *)0x40007008)) //PD1
#define Column1      (*((volatile unsigned long *)0x40007004)) //PD0

#define PORTS03 0x0F

void InitKeyPad(void);
char ReadKey(void);

#endif