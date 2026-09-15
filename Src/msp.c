/*
 * msp.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#include "msp.h"

#define MODE_AF                                 (0x2UL << 0U)
#define OUTPUT_PP                               (0x0UL << 4U)
#define  GPIO_MODE_AF_PP                        (MODE_AF | OUTPUT_PP)

extern DMA_HandleTypeDef hdma_usart2_tx;

void USART_MspInit(UART_HandleTypeDef* huart){
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  if(huart->Instance == USART2){

		  __RCC_USART2_CLK_ENABLE();
		  __RCC_GPIOA_CLK_ENABLE();

			/**USART2 GPIO Configuration
			PA2     ------> USART2_TX
			PA3     ------> USART2_RX
			*/

		  /*TX*/
		  GPIO_InitStruct.Pin = GPIO_PIN_2 ;
		  GPIO_InitStruct.Mode = GPIO_ALTERNATE;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		  GPIO_InitStruct.OType = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Alternate = GPIO_AF7;
		  GPIO_Init(GPIOA, &GPIO_InitStruct);

		  /*RX*/
		  GPIO_InitStruct.Pin = GPIO_PIN_3 ;
		  GPIO_InitStruct.Mode = GPIO_ALTERNATE;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		  GPIO_InitStruct.OType = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Alternate = GPIO_AF7;
		  GPIO_Init(GPIOA, &GPIO_InitStruct);


		  /* USART2 DMA1 Init */

//		  /* USART2_TX Init */
		  hdma_usart2_tx.Instance = DMA1_Stream_6;
		  hdma_usart2_tx.Init.Channel = DMA_CHANNEL_4;
		  hdma_usart2_tx.Init.Direction = DMA_MEM_TO_PERP;
		  hdma_usart2_tx.Init.PeriphInc = DMA_PERP_INC_DISABLE;
		  hdma_usart2_tx.Init.MemInc = DMA_MEM_INC_ENABLE;
		  hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PERIP_DATA_SIZE_BYTE;
		  hdma_usart2_tx.Init.MemDataAlignment = DMA_MEM_DATA_SIZE_BYTE;
		  hdma_usart2_tx.Init.Mode = DMA_NORMAL;
		  hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
		  hdma_usart2_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

		  if(DMA1_Init(&hdma_usart2_tx) != VIC_OK){
//			  Error_Handler();
		  }

		  DMA_LINK(huart, &hdma_usart2_tx);

	  }

}


void CAN_MspInit(CAN_HandleTypeDef* hcan){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	if(hcan->Instance == CAN1){

		  __RCC_CAN1_CLK_ENABLE();
		  delay(100);
		  __RCC_GPIOA_CLK_ENABLE();

		  /**
		   	CAN1 GPIO Configuration
			PA12     ------> CAN1_TX
			PA11     ------> CAN1_RX
		   **/

		  /*TX*/
		  GPIO_InitStruct.Pin = GPIO_PIN_12;
		  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//		  GPIO_InitStruct.OType = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Alternate = GPIO_AF9;
		  GPIO_Init(GPIOA, &GPIO_InitStruct);

		  /*RX*/
		  GPIO_InitStruct.Pin = GPIO_PIN_11 ;
		  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		  GPIO_InitStruct.Pull = GPIO_NOPULL;
		  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//		  GPIO_InitStruct.OType = GPIO_MODE_OUTPUT_PP;
		  GPIO_InitStruct.Alternate = GPIO_AF9;
		  GPIO_Init(GPIOA, &GPIO_InitStruct);

	  }

}


