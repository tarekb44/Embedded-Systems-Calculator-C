#include "keypad_init.h"

void PortD_Init(void);
void PortE_Init(void);
void setColumns(int index);
// 1) First column is on
// 2) Second Column is on
// 3) Third column is on
// 4) Fourth Column is on
unsigned long columns[4][4] = {
        {0x01, 0x00, 0x00, 0x00},
        {0x00, 0x02, 0x00, 0x00},
        {0x00, 0x00, 0x04, 0x00},
        {0x00, 0x00, 0x00, 0x08}
};

unsigned long Keypad_input;

unsigned long keypad_chars[4][4] = {
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'}
};

/*

unsigned long keypad_chars[4][4] = {{0x31, 0x32, 0x33, 0x41},
									{0x34, 0x35, 0x36, 0x42},
									{0x37, 0x38, 0x39, 0x43},
									{0x2A, 0x30, 0x23, 0x44}
};

*/

void InitKeyPad(void)
{
    SYSCTL_RCGC2_R |= 0x18;
    while(SYSCTL_RCGC2_R&0x18 == 0x00);
    PortE_Init(); // rows 
    PortD_Init(); // columns
}

void setColumns(int index)
{
    Column1 = columns[index][0];
    Column2 = columns[index][1];
    Column3 = columns[index][2];
    Column4 = columns[index][3];
}

char ReadKey(void)
{
    for(int col = 1; col <= 4;  col++)
    {
        setColumns(col-1);
        Systick_ms(10);
        for(int row = 1; row <= 4; row++)
        {
            if((PortE & (1U << row-1)) > 0x00)
            {
                return keypad_chars[col-1][row-1];
            }
        }
    }

    return 'z';         // invalid character
}

void PortD_Init(void)
{
    GPIO_PORTD_CR_R |= PORT03;           // allow changes to PD3-0       
    GPIO_PORTD_AMSEL_R &= ~PORT03;        // disable analog function
    GPIO_PORTD_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
    GPIO_PORTD_DIR_R |= PORT03;          // PD3-0 Input   
    GPIO_PORTD_AFSEL_R &= ~PORT03;        // no alternate function
    GPIO_PORTD_PDR_R |= PORT03;          // disable pullup resistors on PD3-0       
    GPIO_PORTD_DEN_R |= PORT03;          // enable digital pins PD3-0 
}

void PortE_Init(void)
{
    GPIO_PORTE_CR_R |= PORT03;           // allow changes to PE3-0       
    GPIO_PORTE_AMSEL_R &= ~PORT03;        // disable analog function
    GPIO_PORTE_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
    GPIO_PORTE_DIR_R &= ~PORT03;          // PE3-0 Output   
    GPIO_PORTE_AFSEL_R &= ~PORT03;        // no alternate function
    GPIO_PORTE_PUR_R &= ~PORT03;          // enable pull down resistors on PE3-0       
    GPIO_PORTE_DEN_R |= PORT03;          // enable digital pins PE3-0
}