/*
 * hardware.h
 *
 *  Created on: 26-Sep-2022
 *      Author: kartikey
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stdint.h>
#include <stdbool.h>

#define RED_LED_MASK 2
#define MY_RED_LED (*((volatile uint32_t *)(0x42000000 + (0x400253FC-0x40000000)*32 + 1*4)))

#define RED_LED PORTE,0
#define GREEN_LED PORTA,4
#define YELLOW_LED PORTA,3
#define ORANGE_LED PORTA,2
#define PUSH_BUTTON_0 PORTD,6
#define PUSH_BUTTON_1 PORTD,7
#define PUSH_BUTTON_2 PORTC,4
#define PUSH_BUTTON_3 PORTC,5
#define PUSH_BUTTON_4 PORTC,6
#define PUSH_BUTTON_5 PORTC,7

void waitPbPress_0();
void waitPbPress_1();
void waitPbPress_2();
void waitPbPress_3();
void waitPbPress_4();
void waitPbPress_5();

void initPbsLeds();
void runhardware();
void LEDFlashSequence();
void LEDFlashSequenceReverse();
void LEDRestartSequence();

#endif /* HARDWARE_H_ */
