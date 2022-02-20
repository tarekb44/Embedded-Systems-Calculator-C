#include "engine.h"

char charArray[40]; 
int index = 0;

void convertChar(char currentChar, int shift, int show);

// automatically in not in shift state
int shiftMode = 0;

int completion = 0;

// no shift - shift
unsigned long A[2] = {0x2B, 0x2A};
unsigned long B[2] = {0X2D, 0x2F};
unsigned long C[2] = {0x2E, 0x45};

int OperatorIndx;
int NumberIndx;
int DigitIndx;
float Number[40];
int Digit[40];
char Operator[40];

void convertChar(char currentChar, int shift, int show)
{
		unsigned long aShift, bShift, cShift;
		// display the char for user to see on LCD
    switch (currentChar)
    {

        case 'A':
			aShift = A[shift];
            SendDisplayByte(aShift, 1);
            break;
        case 'B':
			bShift = B[shift];
            SendDisplayByte(bShift, 1);
            break;
        case 'C':
			cShift = C[shift];
            SendDisplayByte(cShift, 1);
            break;
        case ' ': 
            SendDisplayByte(0x10 + 0x01, 1);
            break;
        case '#':
            SendDisplayByte(0x20 + 0x03, 1);
            break;
        case '+':
            SendDisplayByte(0x20 + 0x0B, 1);
            break;
        case '=':
            SendDisplayByte(0x30 + 0x0D, 1);
            break;
        case '-':
            SendDisplayByte(0x20 + 0x0D, 1);
            break;
        case 'E':
            SendDisplayByte(0x40 + 0x05, 1);
            break;
        case '.':
            SendDisplayByte(0x20 + 0x0E, 1);
            break;
        case '/':
            SendDisplayByte(0x20 + 0x0F, 1);
            break;
	    case '0':
            SendDisplayByte(0x30 + 0x00, 1);
            if(show == 0)
            {
                
            } 
            break;
        case '1':
            SendDisplayByte(0x30 + 0x01, 1);
            break;
        case '2':
            SendDisplayByte(0x30 + 0x02, 1);
            break;
        case '3':
            SendDisplayByte(0x30 + 0x03, 1);
            break;
        case '4':
            SendDisplayByte(0x30 + 0x04, 1);
            break;
        case '5':
            SendDisplayByte(0x30 + 0x05, 1);
            break;
        case '6':
            SendDisplayByte(0x30 + 0x06, 1);
            break;
        case '7':
            SendDisplayByte(0x30 + 0x07, 1);
            break;
        case '8':
            SendDisplayByte(0x30 + 0x08, 1);
            break;
        case '9':
            SendDisplayByte(0x30 + 0x09, 1);
            break;
    }	
}

char getResult(void)
{
    int currNum = 0;

    int firstDecNum = 0;
    int seen = 0;
    char operand = '+';   // assign to automatically add (for first number)

    int sArray[16];
    int sIndex = 8;
    
    int currDec = 0;

    int endIndex = 0; 
    int x = 0;


    for(int j = 0; j <= 16; j++)
    {
        char key = charArray[j];
        int firstNum = 0;
				
        if(isdigit(charArray[j]))
        {
            currNum = (charArray[j] - '0') + (currNum * 10);
            convertChar(charArray[j], 1);
        }

        if(key == '.')
        {
          if(seen == 0)
          {
            firstDecNum = currNum;
            seen = 1;
          }
        } 

        if((!isdigit(key)) || j == endIndex)
        {
            switch (operand)
            {
                case '+':
                    sArray[sIndex] = (currNum);
                    sIndex--;
                    break;
                case '-':
                    sArray[sIndex] = (currNum * -1);
                    sIndex--;
                    break;
                case '/':
                    if(seen == 1)
                    {
                      sArray[sIndex+1] = 0;
                      sArray[sIndex] = currDec / currNum;
											sIndex--;
                      currDec = 0;
                      seen = 0;
                    } else {
                      firstNum = sArray[sIndex+1];
                      sArray[sIndex+1] = 0;
                      sArray[sIndex] = firstNum / currNum;
											sIndex--;
                    }
                    break;
                case '*':
                    // this is the second part of the decimal
                    if(seen == 1)
                    {
                      sArray[sIndex+1] = 0;
                      sArray[sIndex] = currDec * currNum;
											sIndex--;
                      currDec = 0;
                      seen = 0;
                    } else {
                      firstNum = sArray[sIndex+1];
                      sArray[sIndex+1] = 0;
                      sArray[sIndex] = firstNum * currNum;
											sIndex--;
                    }
                    break;
                case '.':
                    if(key == '*' || key == '+' || key == '/' || key == '+')
                    {
                        currDec = ((currNum * 0.10) + firstDecNum);
                    } 
                    break;
            }
            currNum = 0;
            operand = key;
            firstNum = 0;
        }
    } 
    
    int ans = 0;

    for(int z = 16; z >= 0; z--)
    {
      ans += sArray[z];
    }  

    char calculatedResult[16]; //size of the number
    sprintf(calculatedResult, '%f', ans);
    
    //secondLine();
	SendDisplayByte(0x20, 1);
    convertChar('=', 0);
    SendDisplayByte(0x20, 1);

    for(int k = 0; k < 16; k++) 
    {
        convertChar(calculatedResult[k], 0);
    }
}

void Solve(void);
void SendDisplayAnswer(void);
void Decimal(int i);
void Exponent(int i);
void Minus(int i);
void Sum(int i);
void Multiply(int i);
void Divide(int i);

void SendDisplayAnswer(void){
	//float Output[40];
	//int OutputIndx = 0;
	int negative = 0;
	
	SendDisplayByte(0xC0, 0x00);
	SendDisplayByte(0x3D, 0x01);
	SendDisplayByte(0x20, 0x01);
	
	if(Number[0] < 0){
		Number[0] = Number[0] - (2 * Number[0]);
		negative = 1;
		SendDisplayByte(0x2D, 0x00);
	}
	char Output[16];
	sprintf(Output, "%f", Number[0]);
	for(int i = 0; i < 16; i++){
		convertChar(Output[i], 0);
	}
	
	if(Number[0] == 0){
		convertChar('0', 0);
	}
	SendDisplayByte(0x0C, 0x00);
	completion = 1;
}

void displayResult(void)
{
	secondLine(); // display the result in the second line
	for(int i = 0; i < 16; i++)
	{
		if(charArray[i] == "") break;
		convertChar(charArray[i], shiftMode);
	}
}

void secondLine(void)
{
    for(int i = 0; i < 51 - index; i++)
    {
        SendDisplayByte(0x20, 0x01);
        Systick_ms(1);
    }
}

void runEngine(void)
{
    while(1)
    {
        char currentChar = ReadKey();
        Systick_ms(20);
        if(currentChar == 'D')
        {
            shiftMode = !shiftMode; // switch polarity when shift is pressed
        }
        if(currentChar == '*')
        {
            getResult();
            break;
        }
        convertChar(currentChar, shiftMode);
    }
}