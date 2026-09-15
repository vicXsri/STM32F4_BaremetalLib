/*
 * debounce.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */


#include "debounce.h"

void Debounce_Init(Debounce_Handel_t* handle, GPIO_Typedef* GPIOx, uint32_t pin,  uint32_t delay_ms, bool active_high){
	if(handle != NULL){
		handle->last_tick = 0;
		handle->debounce_delay = delay_ms;
		handle->GPIOx = GPIOx;
		handle->pins = pin;
		handle->last_state = false;
		handle->active_high = active_high;
	}
}

bool Debounce_Check(Debounce_Handel_t* handle, uint32_t current_tick){

	bool raw_voltage = GPIO_ReadPin(handle->GPIOx, handle->pins);

	bool current_pressed = (handle->active_high)? raw_voltage : !raw_voltage;

	if((current_tick - handle->last_tick) < handle->debounce_delay){
		return false;
	}

	if(current_pressed != handle->last_state){
		handle->last_tick = current_tick;
		handle->last_state = current_pressed;
		if(current_pressed == true){
			return true;
		}
	}

	return false;
}
