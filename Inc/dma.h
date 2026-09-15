/*
 * dma.h
 *
 *  Created on: Sep 14, 2026
 *      Author: Vichu
 */

#ifndef DMA_H_
#define DMA_H_

#include "main.h"

#define DMA1				((DMA_TypeDef*) DMA1_BASE)

#define DMA1_Stream_0		((DMA_StreamTypeDef*) DMA1_Stream0_Base)
#define DMA1_Stream_1		((DMA_StreamTypeDef*) DMA1_Stream1_Base)
#define DMA1_Stream_2		((DMA_StreamTypeDef*) DMA1_Stream2_Base)
#define DMA1_Stream_3		((DMA_StreamTypeDef*) DMA1_Stream3_Base)
#define DMA1_Stream_4		((DMA_StreamTypeDef*) DMA1_Stream4_Base)
#define DMA1_Stream_5		((DMA_StreamTypeDef*) DMA1_Stream5_Base)
#define DMA1_Stream_6		((DMA_StreamTypeDef*) DMA1_Stream6_Base)
#define DMA1_Stream_7		((DMA_StreamTypeDef*) DMA1_Stream7_Base)

#define DMA2				((DMA_TypeDef*) DMA2_BASE)

#define DMA2_Stream_0		((DMA_StreamTypeDef*) DMA2_Stream0_Base)
#define DMA2_Stream_1		((DMA_StreamTypeDef*) DMA2_Stream1_Base)
#define DMA2_Stream_2		((DMA_StreamTypeDef*) DMA2_Stream2_Base)
#define DMA2_Stream_3		((DMA_StreamTypeDef*) DMA2_Stream3_Base)
#define DMA2_Stream_4		((DMA_StreamTypeDef*) DMA2_Stream4_Base)
#define DMA2_Stream_5		((DMA_StreamTypeDef*) DMA2_Stream5_Base)
#define DMA2_Stream_6		((DMA_StreamTypeDef*) DMA2_Stream6_Base)
#define DMA2_Stream_7		((DMA_StreamTypeDef*) DMA2_Stream7_Base)

#define DMA_CHANNEL_0		(0x00U)
#define DMA_CHANNEL_1		(0x01UL << 25U)
#define DMA_CHANNEL_2		(0x02UL << 25U)
#define DMA_CHANNEL_3		(0x03UL << 25U)
#define DMA_CHANNEL_4		(0x04UL << 25U)
#define DMA_CHANNEL_5		(0x05UL << 25U)
#define DMA_CHANNEL_6		(0x06UL << 25U)
#define DMA_CHANNEL_7		(0x07UL << 25U)

#define DMA_PERP_TO_MEM		(0x00U)
#define DMA_MEM_TO_PERP		(0x01UL << 6U)
#define DMA_MEM_TO_MEM		(0x02UL << 6U)

#define DMA_PERP_INC_DISABLE	(0x00U)
#define DMA_PERP_INC_ENABLE		(0x01UL << 9U)

#define DMA_MEM_INC_DISABLE		(0x00U)
#define DMA_MEM_INC_ENABLE		(0x01UL << 10U)

#define DMA_PERIP_DATA_SIZE_BYTE		(0X00U)
#define DMA_PERIP_DATA_SIZE_HALF_WORD	(0X01UL << 11U)
#define DMA_PERIP_DATA_SIZE_WORD		(0X02UL << 11U)

#define DMA_MEM_DATA_SIZE_BYTE		(0X00U)
#define DMA_MEM_DATA_SIZE_HALF_WORD	(0X01UL << 13U)
#define DMA_MEM_DATA_SIZE_WORD		(0X02UL << 13U)

#define DMA_NORMAL					(0x00U)
#define DMA_CIRCULAR				(0x01UL << 8U)
#define DMA_PFCTRL					(0x01UL << 5U)

#define DMA_PRIORITY_LOW			(0x00U)
#define DMA_PRIORITY_MEDIUM			(0x01UL << 16U)
#define DMA_PRIORITY_HIGH			(0x02UL << 16U)
#define DMA_PRIORITY_VERY_HIGH		(0x03UL << 16U)

#define DMA_FIFOMODE_DISABLE		(0x00U)
#define DMA_FIFOMODE_ENABLE			(0x01UL << 2U)

#define DMA_FIFO_THRESHOLD_1QUARTERFULL	(0x00U)
#define DMA_FIFO_THRESHOLD_HALFFULL		(0x01UL << 0U)
#define DMA_FIFO_THRESHOLD_3QUARTERSFULL	(0x02UL << 0U)
#define DMA_FIFO_THRESHOLD_FULL			(0x03UL << 0U)

#define DMA_MBURST_SINGLE			(0x00U)
#define DMA_MBURST_INC4				(0x01UL << 23U)
#define DMA_MBURST_INC8				(0x02UL << 23U)
#define DMA_MBURST_INC16			(0x03UL << 23U)

#define DMA_PBURST_SINGLE			(0x00U)
#define DMA_PBURST_INC4				(0x01UL << 21U)
#define DMA_PBURST_INC8				(0x02UL << 21U)
#define DMA_PBURST_INC16			(0x03UL << 21U)

#define DMA_TIMEOUT_ABORT			((uint32_t)0x05U)

Status_TypeDef DMA1_Init(DMA_HandleTypeDef* hdma);
Status_TypeDef DMA_START_IT(DMA_HandleTypeDef* hdma, uint32_t SrcAddr,
		uint32_t DstAddr, uint32_t DataLength);
void DMA_IRQHandler(DMA_HandleTypeDef* hdma);
void DMA_LINK(UART_HandleTypeDef* huart, DMA_HandleTypeDef* hdma);
#endif /* DMA_H_ */
