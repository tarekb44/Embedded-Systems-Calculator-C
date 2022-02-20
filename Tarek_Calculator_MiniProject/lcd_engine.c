/* #include "lcd_engine.h"


static void SendDisplayNibble(uint8_t nibble)
{
    // bit wise shift bits to right and mask in order to set the individual bits 
    PortD7 = ((nibble >> 3) & 0x01);
    PortD6 = ((nibble >> 2) & 0x01);
    PortD5 = ((nibble >> 1) & 0x01);
    PortD4 = ((nibble >> 0) & 0x01);

    // LCD ENABLE
    ENHighLow();
}


static void SendDisplayByte(uint8_t byte)
{
    // R/W is physically fixated to ground

    // Set the LCD to instruction mode
    RSMode(0x00);

    // send the upper higher nibbles
    SendDisplayByte(byte >> 4);

    // send the lower 4 bits 
    SendDisplayByte((byte & 0xF));
}


static void RSMode(uint8_t mode)
{
    RSPin = mode;
}


static void ENHighLow(void)
{
    // E is on PA2 
    ENPin = 0x04;
    Systick_us(5);
    ENPin = 0x00;
    Systick_us(45); // anything above 37 micro seconds 
} */