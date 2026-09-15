/*
 * debounce.h
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

#include "gpio.h"

typedef struct{
	uint32_t last_tick;
	uint32_t debounce_delay;
	bool last_state;
	GPIO_Typedef* GPIOx;
	uint32_t pins;
	bool active_high;
}Debounce_Handel_t;

void Debounce_Init(Debounce_Handel_t* handle, GPIO_Typedef* GPIOx, uint32_t pin,  uint32_t delay_ms, bool active_high);

bool Debounce_Check(Debounce_Handel_t* handle, uint32_t current_tick);

#endif /* DEBOUNCE_H_ */
