#include "keypad_init.h"
#include "keypad_driver.h"
#include "lcd_init.h"
#include "PLL.h"
#include "engine.h"


int main(void)
{
    PLL_Init();
    SysTick_Init();
    InitDisplayPort();
    InitKeyPad();
    runEngine();
}