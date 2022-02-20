#include "lcd_init.h"

void initGPIO(void);
void PortA_Init(void);
void PortB_Init(void);
void initGPIOS(void);

void initLCDSequence(void);
void Systick_ms(unsigned long milli);
void Systick_us(unsigned long nano);


void InitDisplayPort(void)
{
    initGPIOS();    // Ports PA3, PA2, and PB3 - PB2 are used so we need to init
    initLCDSequence();
}

void initGPIOS(void)
{
    unsigned char PORT_A_B = 0x3;
    SYSCTL_RCGC2_R |= 0x3;  
    while((SYSCTL_RCGC2_R&PORT_A_B) == LOW){}
    PortA_Init();
    PortB_Init(); 
}

/* follow the LCD init sequence as specified in Page 46 of the HD44780U data sheet
    * Initially the LCD operates in 8-BIT MODE, the first 7-steps, we assume the LCD 
    * operates in 8 bit mode. 
    * 
    * These steps are important for initialization, the following steps will be used for configuration
    * 
    * RS -> 0 - for instruction mode, 1 - for data mode
    * R/W -> 0 - for write mode, 1 - 1 for read mode
    * 0) Power On 
    * 1) Delay 40ms in order for Vcc to atleast 2.7V in order for the LCD to start internal operation
    * 2) Send the following command:
    *       -> R/S = 0 , R/W = 0, DB7 = 0, DB6 = 0, DB5 = 1, DB4 = 1
    * 3) Wait more than 4.1 ms
    * 3) Send the following command: 
    *       -> R/S = 0 , R/W = 0, DB7 = 0, DB6 = 0, DB5 = 1, DB4 = 1
    * 4) Wait more than 100 micro seconds
    * 5) Send the following command: 
    *       -> R/S = 0 , R/W = 0, DB7 = 0, DB6 = 0, DB5 = 1, DB4 = 1
    * 6) Send the following command: 
    *       -> R/S = 0 , R/W = 0, DB7 = 0, DB6 = 0, DB5 = 1, DB4 = 0
    * 
    * 
    * ///////////////// CONFIGURATION COMMANDS //////////////////////////
    * 
    */ 
void initLCDSequence(void)
{
    ////////// PART 1 ///////////
    Systick_ms(50); // 1 // wait more than 40 ms (worst case)
    RSPin = LOW;
    SendDisplayNibble(0x3);  // 2 // Try setting the display 
    Systick_ms(5);  // 3 // wait more than 4.1 ms
    SendDisplayNibble(0x3);  // 4 // Try setting the display with the appropriate Data pins
    Systick_us(120); // 5 // wait more than 100 micro seconds
    SendDisplayNibble(0x3);  // 6 Try setting the display with appropriate data pins
    SendDisplayNibble(0x2); // 7 Try setting the display; Only DB5 is high this time

    ////////// PART 2 /////////// Interface is now 8-bits; so two bytes (nibbles) must be sent
    SendDisplayByte(0x28, 0); // Configure for two lines, Set the character font to 5x8 dots 
    SendDisplayByte(0xE, 0); 
    Systick_ms(4); // delay 4ms
    SendDisplayByte(0x1, 0);   
    Systick_ms(4); // delay 4ms
    SendDisplayByte(0x06, 0); // increment the cursor, no shift  
    SendDisplayByte(PORT03, 0); // power on the data lines 
}


void SendDisplayNibble(unsigned long nibble)
{
    GPIO_PORTB_DATA_R = nibble;
    ENHighLow();
}


void SendDisplayByte(unsigned long byte, int RS)
{
    // R/W is physically fixated to ground

    // Set the LCD to instruction mode
    if(RS == 1)
    {
        RSPin = 0x08;
    } else {
        RSPin = 0x00;
    }

    // send the upper higher nibbles
    SendDisplayNibble(byte >> 4);

    // send the lower 4 bits 
    SendDisplayNibble((byte & 0x0F));
}



void ENHighLow(void)
{
    // E is on PA2 
    ENPin = 0x04;
    Systick_us(1);
    ENPin = LOW;
    Systick_us(45); // anything above 37 micro seconds 
}


void Systick_ms(unsigned long delay_ms)
{
	SysTick_Wait(delay_ms*MHZ);
}

void Systick_us(unsigned long delay_us)
{
	SysTick_Wait(delay_us*UHZ);
}

void PortA_Init(void)
{
    GPIO_PORTA_LOCK_R = 0x4C4F434B;
    GPIO_PORTA_CR_R |= PORT23;            // 2) allow changes to Port A3 - A2
    GPIO_PORTA_AMSEL_R &= ~PORT23;        // 3) disable the anolog function Port A3 - A2
    GPIO_PORTA_PCTL_R = 0x00000000;   // 4) PCTL on PA3 - PA2
    GPIO_PORTA_DIR_R |= PORT23;           // 5) Set PA3-PA2 to output mode
    GPIO_PORTA_AFSEL_R |= ~PORT23;        // 6) Disable the alternate functions on PA3-PA2
    GPIO_PORTA_PUR_R = LOW;          // disable pullup resistors on PA     
    GPIO_PORTA_DEN_R |= PORT23;           // 7) Enable the digital Input Output on PA3-PA2
}

void PortB_Init(void)
{
    GPIO_PORTB_LOCK_R = 0x4C4F434B;
    GPIO_PORTB_CR_R |= PORT03;            // 2) allow changes to PORTB3 - B0
    GPIO_PORTB_AMSEL_R &= ~PORT03;        // 3) disable the anaolog functions on B3-B0
	GPIO_PORTB_PCTL_R = 0x00000000;   // 4) PCTL on PB3 - PB0
    GPIO_PORTB_DIR_R |= PORT03;          // 5) Set PB3-PB0 to output mode
    GPIO_PORTB_AFSEL_R &= ~PORT03;        // 6) Disable the alternate functions 
    GPIO_PORTB_PUR_R = LOW;          // disable pullup resistors on PB3-0       
    GPIO_PORTB_DEN_R |= PORT03;           // 7) Enavble the digital Input and Output PB3-PB0
}