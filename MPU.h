/*
 * MPU.h
 *
 *      Author: kartikey
 */

#ifndef MPU_H_
#define MPU_H_

#include <stdint.h>
#include <stdbool.h>

#define pid 1234

#define OVERALL_BASE_ADDR           0x00000000
#define FLASH_BASE_ADDR             0x00000000
#define PERIPHERAL_BASE_ADDR        0x40000000
#define SRAM_BASE_ADDR              0x20000000

#define NVIC_MPU_ATTR_AP_FULLACC    0x03000000
#define NVIC_MPU_ATTR_AP_PRIVRW     0x01000000
#define NVIC_MPU_ATTR_AP_NOACC      0x00000000

#define REG_0  0x00
#define REG_1  0x01
#define REG_2  0x02
#define REG_3  0x03
#define REG_4  0x04
#define REG_5  0x05
#define REG_6  0x06
#define REG_7  0x07
#define REG_8  0x08

#define SRAM_0      0x20000000
#define SRAM_START  0x20001000
#define SRAM_1      0x20002000
#define SRAM_2      0x20004000
#define SRAM_3      0x20006000 //4KiB
#define SRAM_4      0x20007000 //4KiB

#define SRAM_END    0x20007FFF


void enableMPU();

void setPsp(uint32_t * add);
void setAspBit();
uint32_t* MSPValue();
uint32_t* PSPValue();
void switchToUnprivilegeMode();

//** Interrupt Handlers **//
void enableInterruptHandler();
void BusFaultISR();
void FaultISR(void);
void UsageFaultISR();
void MPUFaultISR();
void PendsvISR();

//** Fault Testing **//
void usageFaultTest();
void busFaultTest();
void faultTestsDemo();
void hardFaultTest();
void pendSvTest();
void memProtectionTest();

//** Region Testing **//
void flashAccessTest();
void peripheralAccessTest();
void SRAMAcessTest();
void SRAMAccessRestricted();
void mallocTest();

//** Region Rules **//
void overallAccess();
void overallAccessNoPrivilege();
void allowFlashAccess(void);
void allowFlashAccessNoPrivilege(void);
void allowPeripheralAccess(void);
void allowPeripheralAccessNoPrivilege(void);
void setupSramAccess(void);
void setSramAccessWindow(uint32_t baseAdd, uint32_t size_in_bytes);

#endif /* MPU_H_ */
