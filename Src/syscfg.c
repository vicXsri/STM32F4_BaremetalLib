/*
 * syscf.c
 *
 *  Created on: May 31, 2025
 *      Author: Vichu
 */


#include "syscfg.h"

void pc13_exti_interrupt(uint32_t IRQn){
	__disable_IRQ();

	SYSCFG->EXTICR[3] |= 	(1U << 5); // 5 - 1

	EXTI->IMR  |= (1U << 13);
	EXTI->FTSR |= (1U << 13);
	EXTI->RTSR |= (1U << 13);

	NVIC_Enable(IRQn);

	__enable_IRQ();
}

void pc0_exti_interrupt(uint32_t IRQn){
	__disable_IRQ();

	SYSCFG->EXTICR[0] |= 	(1UL << 1U); // 5 - 1

	EXTI->IMR  |= (1U << 0);
	EXTI->RTSR |= (1U << 0);
	EXTI->FTSR |= (1U << 0);

	NVIC_Enable(IRQn);

	__enable_IRQ();
}
