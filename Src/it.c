/*
 * it.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#include "it.h"
#include "debounce.h"
//#include "uart.h"

extern Debounce_Handel_t user_btn;
extern Debounce_Handel_t user_btn_pc0;
extern Debounce_Handel_t user_btn_pc13;
extern void UART_isr (UART_HandleTypeDef *huart);
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_tx;

void EXTI15_10_IRQHandler(void){
	if((EXTI->PR & (1U << 13)) != 0){
        if (Debounce_Check(&user_btn_pc13, Get_Tick())) {
        	GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        }
		EXTI->PR = (1U << 13);
	}
}

void EXTI0_IRQHandler(void){
	if((EXTI->PR & (1UL << 0U)) != 0){
        if (Debounce_Check(&user_btn_pc0, Get_Tick())) {
        	GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        }
     }
		EXTI->PR = (1U << 0U);
}


void USART2_IRQHandler(){
	if(USART2->SR & (1U << 0x05U)){
		/* USART2 Callback Function*/
		UART_isr(&huart2);
	}

	if(((USART2->SR & (1UL << 6U)) != 0U) &&
		((USART2->CR1 & (1UL << 6U)) != 0U)){
		USART2->CR1 &= ~(1UL << 6U);
		UART_TxCpltCallback(&huart2);
	}
}

void DMA1_Stream6_IRQHandler(void){
	DMA_IRQHandler(&hdma_usart2_tx);
}

