/*
 * RTOSlibrary.c
 *
 *  Created on: 31-Aug-2022
 *      Author: kartikey
 */
#include "tm4c123gh6pm.h"
#include "gpio.h"
#include "uart0.h"
#include "RTOSlibrary.h"
#include "uart_UI.h"


void reboot()
{
    APINT_REG = 0x05FA0004; //Unlock and reset
}

void ps()
{
    putsUart0("PS called");
}

void ipcs()
{
    putsUart0("IPCS called");
}

void kill(uint32_t pid)
{
    printUint32t2Hex(pid);
    putsUart0(" killed");
}

void pmap(uint32_t pid)
{
    putsUart0("Memory usage by ");
    printUint32t2Hex(pid);
}

void preempt(bool on)
{
    if(on)
    {
        putsUart0("Preempt on");
    }
    else
    {
        putsUart0("Preempt off");
    }
}

void sched(bool prio_on)
{
    if(prio_on)
    {
        putsUart0("sched prio");
    }
    else
    {
        putsUart0("sched rr");
    }
}

void pidof(const char name[])
{
    putsUart0(name);
    putsUart0(" launched");
}


