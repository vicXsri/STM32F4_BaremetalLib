/*
 * main.h
 *
 *  Created on: May 30, 2025
 *      Author: Vichu
 */

#ifndef MAIN_H_
#define MAIN_H_

#define	__IO volatile

static inline void __disable_IRQ(void){
	__asm volatile ("cpsid i" : : : "memory"); // global interrupt disable
}

static inline void __enable_IRQ(void){
	__asm volatile ("cpsie i" : : : "memory"); // global interrupt enable
}

typedef enum{
	VIC_OK			= 0x00U,
	VIC_ERROR		= 0x01U,
	VIC_BUSY		= 0x02U,
	VIC_TIMEOUT		= 0x03U
}Status_TypeDef;

typedef enum{
	ARM_UNLOCKED			= 0x00U,
	ARM_LOCKED			= 0x01U
}LOCK_TypeDef;

typedef enum{
	ENABLE = 1,
	DISABLE = !ENABLE
}State_TypeDef;



#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#include "core_m4.h"
#include "stm32_f446xx.h"
#include "bitManipulator.h"

#include "pwr.h"
#include "rcc.h"
#include "fpu.h"
#include "it.h"
#include "flash.h"
#include "timbase.h"
#include "syscfg.h"
#include "exti.h"
#include "gpio.h"
#include "uart.h"
#include "can.h"
#include "dma.h"
#include "msp.h"

#endif /* MAIN_H_ */
