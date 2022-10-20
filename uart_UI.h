//UART Interface


/****************************************************************************************************
TARGET DEVICE : TM4c123gh6pm
INTERFACE : TM4c123gh6pm Uart0 debugging interface.
PURPOSE : Utilizes Uart0 to allow the user to communicate with the redboard through commands in a terminal.
****************************************************************************************************/

#ifndef __UART_UI_H
#define __UART_UI_H

//**************************************
//USER DATA DECLARATIONS
#define MAX_CHARS 80
#define MAX_FIELDS 6

#include <stdint.h>
#include <stdbool.h>

//^User data structure^
typedef struct _USER_DATA
{
    char buffer[MAX_CHARS+1];
    uint8_t fieldCount;
    uint8_t fieldPosition[MAX_FIELDS];
    char fieldType[MAX_FIELDS];
} USER_DATA;


//USER DATA FUNCTIONS*********************
void getsUart0(USER_DATA *input);
void parseFields(USER_DATA *input);
char* getFieldString(USER_DATA *input, uint8_t fieldNumber);
int32_t getFieldInteger(USER_DATA *input, uint8_t fieldNumber);
float getFieldFloat(USER_DATA *input, uint8_t fieldNumber);
bool isCommand(USER_DATA *input, const char strCommand[], uint8_t minArguments);

//EXTRANEOUS FUNCTONS*********************
bool checkNum(const char *c);
bool checkAlpha(const char *c);
bool checkDelim(const char *c);
bool isStrEq(const char *str1,const char *str2);
void toupper(char *c);
bool check1Field(char fieldType, uint8_t fieldNum, USER_DATA input);
bool checkFields(char *fields, uint8_t numFields, USER_DATA input);

void printInt32ToUart0(int32_t num);
void printUInt32ToUart0(uint32_t num);
void printFloatToUart0(float num);

//SHELL***********************************
void shell (void);
void redLED();
uint32_t cpointer2uint32 (char *c);
void printUint8t2Hex(uint8_t num);
void prinUint8toDecimal(uint8_t num);
void printUint32t2Hex(uint32_t num);
#endif
