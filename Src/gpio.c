/*
 * gpio.c
 *
 *  Created on: May 30, 2025
 *      Author: Vichu
 */


#include "gpio.h"

void GPIO_Init(GPIO_Typedef* GPIOx, GPIO_InitTypeDef* GPIO_Init){

	/* Set the Mode of the GPIO Pin*/
	CLEAR_FIELD(GPIOx->MODER, 0x03U, (GPIO_Init->Pin * 0x02));
	SET_FIELD(GPIOx->MODER, GPIO_Init->Mode, (GPIO_Init->Pin * 0x02));

	/* In case of alternate or output mode*/
	if((GPIO_Init->Mode == GPIO_OUTPUT) || (GPIO_Init->Mode == GPIO_ANALOG)){
		/*Set the speed of the gpio pin*/
		CLEAR_FIELD(GPIOx->OSPEEDR, 0x03U, (GPIO_Init->Pin * 0x02));
		SET_FIELD(GPIOx->OSPEEDR, GPIO_Init->Mode, (GPIO_Init->Pin * 0x02));

		/*configure the output mode of gpio pin*/
		(GPIO_Init->OType)?
			SET_FIELD(GPIOx->OTYPER, 0x01U, GPIO_Init->Pin):
			CLEAR_FIELD(GPIOx->OTYPER, 0x01U, GPIO_Init->Pin);
	}

	/* Except for analog mode, set the pull up/down setup */
	if((GPIO_Init->Mode) != GPIO_ANALOG){
		CLEAR_FIELD(GPIOx->PUPDR, 0x03U, (GPIO_Init->Pin * 0x02));
		SET_FIELD(GPIOx->PUPDR, GPIO_Init->Pull, (GPIO_Init->Pin * 0x02));
	}

	/* Set the AFR Register */
	if((GPIO_Init->Mode) == GPIO_ALTERNATE){
		if(GPIO_Init->Pin <= 7){
			CLEAR_FIELD(GPIOx->AFR[0], 0x0FU, (GPIO_Init->Pin * 0x04));
			SET_FIELD(GPIOx->AFR[0], GPIO_Init->Alternate, (GPIO_Init->Pin * 0x04));
		}
		else{
			CLEAR_FIELD(GPIOx->AFR[1], 0x0FU, (GPIO_Init->Pin * 0x04));
			SET_FIELD(GPIOx->AFR[1], GPIO_Init->Alternate, ((GPIO_Init->Pin - 0x08)* 0x04));
		}
	}
}

void GPIO_DeInit(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN){
	/*Deactivate the Mode Register*/
	CLEAR_FIELD(GPIOx->MODER, 0x3U, (GPIO_PIN * 0x02));

	/*Deactivate the AFR Register*/
	(GPIO_PIN <= 0x07)?
	CLEAR_FIELD(GPIOx->AFR[0], 0x0FU, (GPIO_PIN * 0x04)):
	CLEAR_FIELD(GPIOx->AFR[1], 0x0FU, ((GPIO_PIN - 0x08) * 0x04));

	/*Deactivate the PULL Register*/
	CLEAR_FIELD(GPIOx->PUPDR, 0x03U, (GPIO_PIN * 0x02));

	/*Deactivate the Output mode Register*/
	CLEAR_FIELD(GPIOx->OTYPER, 0x01U, GPIO_PIN);

	/*Deactivate the Output mode Register*/
	CLEAR_FIELD(GPIOx->OSPEEDR, 0x03U, (GPIO_PIN * 0x02));

}

void GPIO_WritePin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN, uint8_t state){
	(state == 1)?
			/**/
			SET_FIELD(GPIOx->ODR, 0x01U, GPIO_PIN):
			CLEAR_FIELD(GPIOx->ODR, 0x01U, GPIO_PIN);
}

void GPIO_TogglePin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN){
	INVERT_BIT(GPIOx->ODR, 0x01U,GPIO_PIN);
}

bool GPIO_ReadPin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN){
	return	READ_FIELD(GPIOx->IDR, GPIO_PIN, 0x01U);
}

bool GPIO_LockPin(GPIO_Typedef* GPIOx,  uint16_t GPIO_PIN){

	/*We should follow the Lock Key write sequence*/
	/*Sequence Start*/

	/*WR LCKR[16] = ‘1’ + LCKR[15:0]*/
	WRITE_REG(GPIOx->LCKR ,(0x01U << GPIO_PIN)| (0x01U << 0x10U));

	/*WR LCKR[16] = ‘0’ + LCKR[15:0]*/
	WRITE_REG(GPIOx->LCKR ,(0x01U << GPIO_PIN)| (0x01U << 0x10U));

	/*WR LCKR[16] = ‘1’ + LCKR[15:0]*/
	WRITE_REG(GPIOx->LCKR ,(0x01U << GPIO_PIN)| (0x01U << 0x10U));
	/*RD LCKR - Dummy read!!!*/
	(void)GPIOx->LCKR;

	/*Sequence End*/
	return READ_FIELD(GPIOx->LCKR, 0x01U, 0x10U);
}
