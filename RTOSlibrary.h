/*
 * RTOSlibrary.h
 *
 *  Created on: 31-Aug-2022
 *      Author: kartikey
 */

#ifndef RTOSLIBRARY_H_
#define RTOSLIBRARY_H_

//REGISTER DEFINES
#define APINT_REG (* ( (volatile uint32_t *) (0xE000ED0C) ) )

void reboot();
void ps();
void ipcs();
void kill(uint32_t pid);
void pmap(uint32_t pid);
void preempt(bool on);
void sched(bool prio_on);
void pidof(const char name[]);

#endif /* RTOSLIBRARY_H_ */
