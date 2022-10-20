/*
 * hardware.c
 *
 *  Created on: 26-Sep-2022
 *      Author: kartikey
 */
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "clock.h"
#include "gpio.h"
#include "hardware.h"
#include "MPU.h"
#include "wait.h"


void waitPbPress_0()
{
    while(getPinValue(PUSH_BUTTON_0));
}
void waitPbPress_1()
{
    while(getPinValue(PUSH_BUTTON_1));
}
void waitPbPress_2()
{
    while(getPinValue(PUSH_BUTTON_2));
}
void waitPbPress_3()
{
    while(getPinValue(PUSH_BUTTON_3));
}
void waitPbPress_4()
{
    while(getPinValue(PUSH_BUTTON_4));
}
void waitPbPress_5()
{
    while(getPinValue(PUSH_BUTTON_5));
}

void initPbsLeds()
{
    // Initialize system clock to 40 MHz
    //initSystemClockTo40Mhz();

    // Enable clocks
    enablePort(PORTF);
    enablePort(PORTD);
    enablePort(PORTC);
    enablePort(PORTE);

    // Configure LED and pushbutton pins
    setPinCommitControl(PUSH_BUTTON_1);
    selectPinPushPullOutput(GREEN_LED);
    selectPinPushPullOutput(RED_LED);

    //configuring my red led
    GPIO_PORTF_DIR_R |= RED_LED_MASK;
    GPIO_PORTF_DR2R_R |= RED_LED_MASK;
    GPIO_PORTF_DEN_R |= RED_LED_MASK;

    selectPinPushPullOutput(YELLOW_LED);
    selectPinPushPullOutput(ORANGE_LED);

    selectPinDigitalInput(PUSH_BUTTON_0);
    enablePinPullup(PUSH_BUTTON_0);

    selectPinDigitalInput(PUSH_BUTTON_1);
    enablePinPullup(PUSH_BUTTON_1);

    selectPinDigitalInput(PUSH_BUTTON_2);
    enablePinPullup(PUSH_BUTTON_2);

    selectPinDigitalInput(PUSH_BUTTON_3);
    enablePinPullup(PUSH_BUTTON_3);

    selectPinDigitalInput(PUSH_BUTTON_4);
    enablePinPullup(PUSH_BUTTON_4);

    selectPinDigitalInput(PUSH_BUTTON_5);
    enablePinPullup(PUSH_BUTTON_5);
}

void runhardware()
{

    setPinValue(GREEN_LED, 0);
    setPinValue(RED_LED, 0);
    setPinValue(ORANGE_LED, 0);
    setPinValue(YELLOW_LED, 0);

    waitPbPress_0();


    setPinValue(GREEN_LED, 0);
    setPinValue(RED_LED, 0);
    setPinValue(ORANGE_LED, 1);
    setPinValue(YELLOW_LED, 0);

    waitPbPress_1();

    setPinValue(GREEN_LED, 0);
    setPinValue(RED_LED, 0);
    setPinValue(ORANGE_LED, 0);
    setPinValue(YELLOW_LED, 1);

    waitPbPress_2();

    setPinValue(GREEN_LED, 1);
    setPinValue(RED_LED, 0);
    setPinValue(ORANGE_LED, 0);
    setPinValue(YELLOW_LED, 0);

    waitPbPress_3();

    setPinValue(GREEN_LED, 0);
    setPinValue(RED_LED, 1);
    setPinValue(ORANGE_LED, 0);
    setPinValue(YELLOW_LED, 0);

    waitPbPress_4();

    setPinValue(GREEN_LED, 1);
    setPinValue(RED_LED, 0);
    setPinValue(ORANGE_LED, 1);
    setPinValue(YELLOW_LED, 1);

    waitPbPress_5();

    setPinValue(GREEN_LED, 1);
    setPinValue(RED_LED, 1);
    setPinValue(ORANGE_LED, 0);
    setPinValue(YELLOW_LED, 1);

    // Endless loop
}
void LEDFlashSequence()
{
    setPinValue(ORANGE_LED, 1);
    waitMicrosecond(100000);
    setPinValue(ORANGE_LED, 0);
    waitMicrosecond(100000);
    setPinValue(YELLOW_LED, 1);
    waitMicrosecond(100000);
    setPinValue(YELLOW_LED, 0);
    waitMicrosecond(100000);
    setPinValue(GREEN_LED, 1);
    waitMicrosecond(100000);
    setPinValue(GREEN_LED, 0);
    waitMicrosecond(100000);
    setPinValue(RED_LED, 1);
    waitMicrosecond(100000);
    setPinValue(RED_LED, 0);
    waitMicrosecond(100000);
    setPinValue(RED_LED, 1);
    waitMicrosecond(100000);
    setPinValue(RED_LED, 0);
    waitMicrosecond(100000);
    setPinValue(GREEN_LED, 1);
    waitMicrosecond(100000);
    setPinValue(GREEN_LED, 0);
    waitMicrosecond(100000);
    setPinValue(YELLOW_LED, 1);
    waitMicrosecond(100000);
    setPinValue(YELLOW_LED, 0);
    waitMicrosecond(100000);
    setPinValue(ORANGE_LED, 1);
    waitMicrosecond(100000);
    setPinValue(ORANGE_LED, 0);
    waitMicrosecond(100000);
}

void LEDFlashSequenceReverse()
{
    setPinValue(RED_LED, 1);
    waitMicrosecond(100000);
    setPinValue(RED_LED, 0);
    waitMicrosecond(100000);
    setPinValue(GREEN_LED, 1);
    waitMicrosecond(100000);
    setPinValue(GREEN_LED, 0);
    waitMicrosecond(100000);
    setPinValue(YELLOW_LED, 1);
    waitMicrosecond(100000);
    setPinValue(YELLOW_LED, 0);
    waitMicrosecond(100000);
    setPinValue(ORANGE_LED, 1);
    waitMicrosecond(100000);
    setPinValue(ORANGE_LED, 0);
    waitMicrosecond(100000);
    setPinValue(ORANGE_LED, 1);
    waitMicrosecond(100000);
    setPinValue(ORANGE_LED, 0);
    waitMicrosecond(100000);
    setPinValue(YELLOW_LED, 1);
    waitMicrosecond(100000);
    setPinValue(YELLOW_LED, 0);
    waitMicrosecond(100000);
    setPinValue(GREEN_LED, 1);
    waitMicrosecond(100000);
    setPinValue(GREEN_LED, 0);
    waitMicrosecond(100000);
    setPinValue(RED_LED, 1);
    waitMicrosecond(100000);
    setPinValue(RED_LED, 0);
    waitMicrosecond(100000);

}

void LEDRestartSequence()
{
    setPinValue(RED_LED, 1);
    setPinValue(GREEN_LED, 1);
    setPinValue(YELLOW_LED, 1);
    setPinValue(ORANGE_LED, 1);
    waitMicrosecond(250000);
    setPinValue(RED_LED, 0);
    setPinValue(GREEN_LED, 0);
    setPinValue(YELLOW_LED, 0);
    setPinValue(ORANGE_LED, 0);
}
