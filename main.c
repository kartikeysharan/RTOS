#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "uart_UI.h"
#include "uart0.h"
#include "RTOSlibrary.h"
#include "wait.h"
#include "clock.h"
#include "tm4c123gh6pm.h"
#include "hardware.h"
#include "MPU.h"
#include "gpio.h"

//uint32_t stack[512];
uint8_t* heap = (uint8_t*)0x20001400; //first 4kib to be used by the OS
uint32_t* psp = (uint32_t*)0x20008000; //PSP pointing to top of the heap
//uint32_t* psp = (uint32_t*)0x20002000; //PSP pointing to top of the heap

void initHW(void)
{
    initSystemClockTo40Mhz();
    _delay_cycles(3);
    initUart0();
    setUart0BaudRate(115200, 40e6);
    initPbsLeds();
    LEDRestartSequence();
    NVIC_CFG_CTRL_R |= NVIC_CFG_CTRL_DIV0;
}

int main(void)
{
    initHW();
    enableInterruptHandler();

    //shell();

    //faultTestsDemo();

    setPsp(psp);
    setAspBit();

    //mallocTest();

    overallAccess();
    //overallAccessNoPrivilege();

    allowFlashAccess();
    //allowFlashAccessNoPrivilege();

    allowPeripheralAccess();
    //allowPeripheralAccessNoPrivilege();

    setupSramAccess();

    enableMPU();

    //switchToUnprivilegeMode();

    //flashAccessTest();

    //peripheralAccessTest();

    SRAMAcessTest();
    //SRAMAccessRestricted();

    while(true);
}
