/*
 * syscfg.h
 *
 *  Created on: May 31, 2025
 *      Author: Vichu
 */

#ifndef SYSCFG_H_
#define SYSCFG_H_

#include "main.h"

typedef struct{
	__IO uint32_t MEMRMP; //SYSCFG memory remap register
	__IO uint32_t PMC; //SYSCFG peripheral mode configuration register
	__IO uint32_t EXTICR[4]; //SYSCFG external interrupt configuration register 1-4
	uint32_t Reserved0[2]; // 0x18 - 0x1C
	__IO uint32_t CMPCR; //Compensation cell control register
	uint32_t Reserved1[2]; // 0x24 - 0x28
	__IO uint32_t CFGR; //SYSCFG configuration register
}SYSCFG_TypeDef;

#define SYSCFG				((SYSCFG_TypeDef*) SYSCFG_BASE)

void pc13_exti_interrupt(uint32_t IRQn);
void pc0_exti_interrupt(uint32_t IRQn);
#endif /* SYSCFG_H_ */
