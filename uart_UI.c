//UART Interface



/****************************************************************************************************
TARGET DEVICE : TM4c123gh6pm
INTERFACE : TM4c123gh6pm Uart0 debugging interface.
PURPOSE : Utilizes Uart0 to allow the user to communicate with the redboard through commands in a terminal.
****************************************************************************************************/
//Directives
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "uart_UI.h"
#include "gpio.h"
#include "uart0.h"
#include "RTOSlibrary.h"

void getsUart0(USER_DATA *input)
{
    uint8_t count = 0;

    bool cFlag = 1;
    char c;

    while(cFlag)
    {
        c = getcUart0();

        //Backspace function. Apparently in windows it thinks that backspace is delete and delete as escape. ?????
        if(c == 8 || c == 127)
        {
            if(count > 0)
            {
                count--;
            }
        }
        else
        {
            //Enter Function
            if(c == 10 || c == 13)
            {
                input->buffer[count] = '\0';
                cFlag = 0;
            }
            else
            {
                //Printable Character Function
                if(c >= 32)
                {
                    input->buffer[count++] = c;
                    if(count >= MAX_CHARS)
                    {
                        input->buffer[MAX_CHARS] = '\0';
                        cFlag = 0;
                    }
                }
            }

        }
    }
}



//Parses fields in the buffer of the USER_DATA structure to be part of the alphabet, number, or delimiter... not really with delimiter.
void parseFields(USER_DATA *input)
{
    bool pDelim = true;
    input->fieldCount = 0;
    uint8_t count = 0;

    while(input->buffer[count] != '\0' && input->fieldCount < MAX_FIELDS)
    {
        if(pDelim == false)
        {
            if(checkDelim(&(input->buffer[count])))
            {
                pDelim = true;
                input->buffer[count] = '\0';
            }
            count++;
        }
        else
        {
            if(checkDelim(&(input->buffer[count])))
            {
                input->buffer[count] = '\0';
                count++;
            }
            else
            {
                pDelim = false;
                input->fieldPosition[input->fieldCount] = count;

                if(checkAlpha(&(input->buffer[count])))
                    input->fieldType[input->fieldCount] = 'a';
                else
                    input->fieldType[input->fieldCount] = 'n';

                (input->fieldCount)++;
                count++;

            }

        }
    }

}

//First, we check if we have an argument in the first place. Then, we check if USER DATA has at least
//the minimum number of arguments passed is equal to less than or equal to field count -1(this is because field count includes the initial
//command which should be removed).
//If both of these conditions are true, we then check at the first position of the first field which should be the string command, and if it
//matches the passed in string strCommand then this should the command we are looking for. Thus, we return a true value.
bool isCommand(USER_DATA *input, const char strCommand[], uint8_t minArguments)
{
    bool flag = false;
    if(input->fieldCount != 0 && (input->fieldCount - 1) >= minArguments)
    {
        if((isStrEq(input->buffer,strCommand)))
        {
            flag = true;
        }
    }
    return flag;
}
//Finds the char pointer at field number, if it exists, and returns it.
//If it doesn't exist, return NULL(0).
char *getFieldString(USER_DATA *input, uint8_t fieldNumber)
{
    char *c = 0;

    if(fieldNumber < input->fieldCount)
    {
        if((input->fieldType[fieldNumber]  == 'a')|| input->fieldType[fieldNumber]  == 'n')
        {
            uint8_t pos = input->fieldPosition[fieldNumber];
            c = &(input->buffer[pos]);
        }
    }
    return c;

}


//Finds the char string at field number, and, if it is an integer, convert it to a int32_t.
//If it does not exist, return 0.
int32_t getFieldInteger(USER_DATA *input, uint8_t fieldNumber)
{
    int32_t x = 0;

    if(fieldNumber < input->fieldCount)
    {
        if(input->fieldType[fieldNumber] == 'n')
        {
            uint8_t pos = input->fieldPosition[fieldNumber];
            bool negative = false;

            if(input->buffer[pos] == '-')
            {
                negative = true;
                pos++;
            }

            while(input->buffer[pos] != '\0')
            {
                x *= 10;
                x += input->buffer[pos] - '0';
                pos++;
            }

            if(negative)
                x *= -1;
        }

    }
    return x;
}

//Finds the char string at field number, and, if it is a number, convert it to a float.
//If it does not exist, return 0.
float getFieldFloat(USER_DATA *input, uint8_t fieldNumber)
{
    float x = 0;
    uint8_t decimalPlace = 1;
    float decimal = 0;

    if(fieldNumber < input->fieldCount)
    {
        if(input->fieldType[fieldNumber] == 'n')
        {
            uint8_t pos = input->fieldPosition[fieldNumber];
            bool negative = false;

            if(input->buffer[pos] == '-')
            {
                negative = true;
                pos++;
            }

            while( input->buffer[pos] != '.' && input->buffer[pos] != '\0')
            {
                x *= 10;
                x += input->buffer[pos] - '0';
                pos++;
            }

            if(input->buffer[pos] == '.')
                pos++;

            while(input->buffer[pos] != '\0')
            {
                decimal = input->buffer[pos] - '0';

                uint8_t i;
                for(i = 0; i < decimalPlace; i++)
                {
                    decimal /= 10;
                }
                x += decimal;
                pos++;
                decimalPlace++;
            }

            if(negative)
                x *= -1;
        }

    }
    return x;
}

//Shell Function
void shell (void)
{

    USER_DATA input;

    while(true)
    {
        putsUart0("\n>> ");
        getsUart0(&input);
        parseFields(&input);

        if((isCommand(&input, "reboot", 0)) || (isCommand(&input, "REBOOT", 0)))
        {
            reboot();
        }
        else if((isCommand(&input, "ps", 0)) || (isCommand(&input, "PS", 0)))
        {
            ps();
        }
        else if((isCommand(&input, "ipcs", 0)) || (isCommand(&input, "IPCS", 0)))
        {
            ipcs();
        }
        else if((isCommand(&input, "kill", 1)) || (isCommand(&input, "KILL", 1)))
        {
            char* value = getFieldString(&input,1);
            uint32_t pid = cpointer2uint32(value);
            kill(pid);
        }
        else if((isCommand(&input, "pmap", 1)) || (isCommand(&input, "PMAP", 1)))
        {
            char* value = getFieldString(&input,1);
            uint32_t pid = cpointer2uint32(value);
            pmap(pid);
        }
        else if((isCommand(&input, "preempt", 1))||(isCommand(&input, "PREEMPT", 1)))
        {
            bool verify = true;
            if(input.fieldType[1] == 'a')
            {
                if((isStrEq(getFieldString(&input, 1), "ON" )) || (isStrEq(getFieldString(&input, 1), "on" )))
                {
                    verify = true;
                }
                else if((isStrEq(getFieldString(&input, 1), "OFF" )) || (isStrEq(getFieldString(&input, 1), "off" )))
                {
                    verify = false;
                }
                else
                {
                    putsUart0("Non-valid option for preempt\n");
                }
            }
            else
            {
                putsUart0("Invalid preempt format\n");
            }
            preempt(verify);
        }
        else if((isCommand(&input, "sched", 1)) || (isCommand(&input, "SCHED", 1)))
        {
            bool verify = true;
            if(input.fieldType[1] == 'a')
            {
                if((isStrEq(getFieldString(&input, 1), "PRIO" )) || (isStrEq(getFieldString(&input, 1), "prio" )))
                {
                    verify = true;
                }
                else if((isStrEq(getFieldString(&input, 1), "RR" )) || (isStrEq(getFieldString(&input, 1), "rr" )))
                {
                    verify = false;
                }
                else
                {
                    putsUart0("Non-valid option for scheduler\n");
                }
            }
            else
            {
                putsUart0("Invalid scheduler format\n");
            }
            sched(verify);
        }
        else if((isCommand(&input, "pidof", 1)) || (isCommand(&input, "PIDOF", 1)))
        {
            char* process = getFieldString(&input, 1);
            pidof(process);
        }
        else if((isCommand(&input, "run", 1)) || (isCommand(&input, "RUN", 1)))
        {
            redLED();
        }
        else
        {
            putsUart0("Invalid Command\n");
        }

    }
}


//****************************************************************************************************
//EXTRANEOUS FUNCTIONS

//Checks if char is part of the english alphabet.
bool checkAlpha(const char *c)
{
    return ((*c >= 65 && *c <= 90) || (*c >= 97 && *c <= 122));
}

//Checks if the char is number.
bool checkNum(const char *c)
{
    return ((*c >= 48 && *c <= 57) || *c == 45 || *c == 46);
}

//Checks if the char is a delimiter.
bool checkDelim(const char *c)
{
    return !(checkAlpha(c) || checkNum(c));
}

//This functions prints up to an int32_t num.
void printInt32ToUart0(int32_t num)
{
    char c[11];
    int8_t x = -1;
    int32_t helper = 0;

    if(num == 0)
    {
        putcUart0('0');
    }
    else
    {
        if(num < 0)
        {
            putcUart0('-');
            num *= -1;
        }

        helper = num;
        while(helper != 0)
        {
            helper = helper/10;
            x++;
        }

        int i;
        for(i = x; i >=0 ; i--)
        {
            c[i] = (num % 10) + '0';
            num = num/10;
        }
        c[x+1] = '\0';
        putsUart0(c);
    }
}


//Prints an uint32_t variable to the terminal.
void printUInt32ToUart0(uint32_t num)
{
    char c[11];
    int8_t x = -1;
    int32_t helper = 0;

    if(num == 0)
    {
        putcUart0('0');
    }
    else
    {
        helper = num;
        while(helper != 0)
        {
            helper = helper/10;
            x++;
        }

        int i;
        for(i = x; i >=0 ; i--)
        {
            c[i] = (num % 10) + '0';
            num = num/10;
        }
        c[x+1] = '\0';
        putsUart0(c);
    }
}

//Prints a float number
#define FLOAT_PRECISION 3
void printFloatToUart0(float num)
{
    char c[10 + 1 + FLOAT_PRECISION];
    int8_t i = 0;

    if(num < 0)
    {
        putcUart0('-');
        num *= -1;
    }

    uint32_t numUInt = num;
    float numFlt = num - numUInt;



    c[10] = '.';
    for(i = 11; i < (10 + 1 + FLOAT_PRECISION); i++)
    {
        numFlt *= 10;
        c[i] = (int)(numFlt) + '0';
        numFlt = numFlt - (int)numFlt;
    }


    for(i = 9; i >= 0 && numUInt != 0; i--)
    {
        c[i] = (numUInt % 10) + '0';
        numUInt /= 10;
    }

    for(i = i+1; i < (10 + 1 + FLOAT_PRECISION); i++)
    {
        putcUart0(c[i]);
    }

}

//Strcmp but boolean
bool isStrEq(const char *str1,const char *str2)
{
    bool flag = true;
    uint8_t i;
    for (i = 0; str1[i] != '\0'; i++)
    {
        char str1new = str1[i];
        char str2new = str2[i];

        if (str1new >= 65 && str1new <= 90)
        {
            str1new += 32;
        }
        if (str2new >= 65 && str2new <= 90)
        {
            str2new += 32;
        }
        if (str1new != str2new)
        {
            flag = false;
        }
    }
    return flag;
}

//Checks 1 field.
bool check1Field(char fieldType, uint8_t fieldNum, USER_DATA input)
{
    return input.fieldType[fieldNum] == fieldType;
}

//Checks multiple fields based on the string passed through.
bool checkFields(char *fields, uint8_t numFields, USER_DATA input)
{
    uint8_t i = 1;
    bool okay = true;
    while( i <= numFields && okay)
    {
        if(input.fieldType[i] != fields[i-1])
            okay = false;

        i++;
    }
    return okay;
}

uint32_t cpointer2uint32 (char *c)
{
    uint32_t final = 0;
    while(*c)
        {
            //the current character of the string
            uint8_t current = *c;
            //increment the current character
            *c++;

            //transform hex char to 4 bit number (ascii table)
            if(current >= '0' && current <= '9')
            {
                current = current - '0';
            }
            else if (current >= 'A' && current <= 'F')
            {
                current = current - 'a' + 10;
            }
            else if (current >= 'a' && current <= 'f')
            {
                current = current - 'A' + 10;
            }
            //make space for next digit
            uint32_t space = (final << 4);
            //add bits of next
            final = space | (current & 0xF);
        }
    return final;
}
void printUint8t2Hex(uint8_t num)
{
    int8_t i = 0;
    for(i = 1; i>=0; i--)
    {
        uint8_t space = (num>>(i*4));
        uint8_t current = space & 0xF;

        if (current>=0 && current<=9)
        {
            putcUart0(current+'0');
        }
        else
        {
            if(current == 10)
            {
                putcUart0('A');
            }
            else if(current == 11)
            {
                putcUart0('B');
            }
            else if(current == 12)
            {
                putcUart0('C');
            }
            else if(current == 13)
            {
                putcUart0('D');
            }
            else if(current == 14)
            {
                putcUart0('E');
            }
            else if(current == 15)
            {
                putcUart0('F');
            }
        }
    }
}

void printUint32t2Hex(uint32_t num)
{
    uint32_t num_shifted = (num);
    uint32_t num_shifted8 = (num >> 8);
    uint32_t num_shifted16 = (num >> 16);
    uint32_t num_shifted24 = (num >> 24);

    printUint8t2Hex((num_shifted24));
    printUint8t2Hex((num_shifted16));
    printUint8t2Hex((num_shifted8));
    printUint8t2Hex((num_shifted));
}

void redLED()
{
    enablePort(PORTF);
    selectPinPushPullOutput(PORTF,1);
    setPinValue(PORTF,1,1);

}
