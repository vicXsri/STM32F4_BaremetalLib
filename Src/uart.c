/*
 * uart.c
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#include "uart.h"

extern UART_HandleTypeDef huart2;


#define uart &huart2
#define TIMEOUT_DEF	500


uint16_t timeout;


RingBuffer_TypeDef rx_buffer = { { 0 }, 0, 0};
RingBuffer_TypeDef tx_buffer = { { 0 }, 0, 0};

RingBuffer_TypeDef *_rx_buffer;
RingBuffer_TypeDef *_tx_buffer;


void store_char(unsigned char c, RingBuffer_TypeDef * buffer);


/********************************************************************************************/
void RingBuffer_Init(void){
	_rx_buffer = &rx_buffer;
	_tx_buffer = &tx_buffer;

	/*Enable the error interrupt*/
	__UART_ENABLE_IT_EIE(uart);

	/*Enable the rx interrupt*/
	__UART_ENABLE_IT_RXNE(uart);
}

void store_char(unsigned char c, RingBuffer_TypeDef * buffer){

}

void UART_isr(UART_HandleTypeDef *huart){

}
/********************************************************************************************/


/********************************************************************************************/
Status_TypeDef USART_Init(UART_HandleTypeDef* huart){

	if(huart == NULL) return VIC_ERROR;

	USART_MspInit(huart);

    /*Transfer Mode*/
    huart->Instance->CR1 = huart->Init.Mode;

    /*Set Baudrate*/
    if(huart->Instance == USART1 || huart->Instance == USART6)
		huart->Instance->BRR = USART_Compute_Baud(RCC_GetP2CLK_Freq(),huart->Init.BaudRate);
    else
    	huart->Instance->BRR = USART_Compute_Baud(RCC_GetP1CLK_Freq(),huart->Init.BaudRate);

    /*No of stop Bits*/
    huart->Instance->CR2 |= huart->Init.StopBits;

    /*Word Length*/
    huart->Instance->CR1 |= huart->Init.WordLength;

    /*parity control*/
    huart->Instance->CR1 |= huart->Init.parity;

    /*HWFlow control*/
    huart->Instance->CR3 |= huart->Init.HWFlowCtl;

    /*Over Sampling*/
    huart->Instance->CR1 |= huart->Init.OverSampling;

    /*Enable the usart Instance*/
    huart->Instance->CR1 |= USART_EN;

    NVIC_Enable(USART2_IRQ);
    return VIC_OK;
}

uint16_t USART_Compute_Baud(uint32_t pclk, uint32_t baudrate){
	return ((pclk + (baudrate / 2U)) / baudrate);
}
/********************************************************************************************/


/********************************************************************************************/
int __io_putchar(int ch){
	debug(ch);
	return ch;
}
void debug(int ch){
	while(!(USART2->SR & (1U << 7)));
	USART2->DR = (ch & 0xFF);
}

void uart_tx(const char* data){
	while(*data){
		debug(*data++);
	}
}

/********************************************************************************************/


/********************************************************************************************/
void __UART_ENABLE_IT_EIE(UART_HandleTypeDef* huart){
	huart->Instance->CR3 |= USART_EIE_EN;
}
void __UART_ENABLE_IT_RXNE(UART_HandleTypeDef* huart){
	huart->Instance->CR1 |= USART_RXNE_EN;
}
/********************************************************************************************/

Status_TypeDef UART_Transmit_DMA(UART_HandleTypeDef* huart, const uint8_t* pData, uint16_t size){

	if((huart == NULL) || (pData == NULL) || (size == 0U) ||
		(huart->hdmatx == NULL)){
		return VIC_ERROR;
	}

	huart->pTxBuffptr = pData;
	huart->TxXferSize = size;
	huart->TxXferCount = size;

	huart->hdmatx->XferCpltCallback = UART_DMATransmitCplt;
	huart->hdmatx->XferHalfCpltCallback = UART_DMATransmitHalfCplt;
//		huart->hdmatx->XferErrorCallback = ;
	huart->hdmatx->XferAbortCallback = NULL;

	if(DMA_START_IT(huart->hdmatx, (uint32_t)pData,
			(uint32_t)&huart->Instance->DR, size) != VIC_OK){
		return VIC_ERROR;
	}

	huart->Instance->SR &= ~(0x01UL << 6U);

	huart->Instance->CR3 |= (0x01UL << 7U);

	return VIC_OK;

}

void UART_DMATransmitCplt(DMA_HandleTypeDef* hdma){
	UART_HandleTypeDef *huart = (UART_HandleTypeDef*) (hdma->Parent);

	/* Normal Mode */
	if(hdma->Init.Mode != DMA_CIRCULAR){
		huart->TxXferCount = 0U;

		huart->Instance->CR3 &= ~(0x01UL << 7U);
		huart->Instance->CR1 |= (0x01UL << 6U);
	}

	/* Circular Mode */
	else{
		UART_TxCpltCallback(huart);
	}
}

void UART_DMATransmitHalfCplt(DMA_HandleTypeDef* hdma){
	UART_HandleTypeDef *huart = (UART_HandleTypeDef*) (hdma->Parent);
	UART_TxHalfCpltCallback(huart);
}

__attribute__((weak)) void UART_TxCpltCallback(UART_HandleTypeDef *huart){

}

__attribute__((weak)) void UART_TxHalfCpltCallback(UART_HandleTypeDef *huart){

}
