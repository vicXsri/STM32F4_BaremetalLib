/*
 * dma.c
 *
 *  Created on: Sep 14, 2026
 *      Author: Vichu
 */


#include "dma.h"

static uint32_t DMA_CalcBaseAndBitshift(DMA_HandleTypeDef* hdma);
static void DMA_SetConfig(DMA_HandleTypeDef* hdma, uint32_t SrcAddr,
		uint32_t DstAddr, uint32_t DataLength);

Status_TypeDef DMA1_Init(DMA_HandleTypeDef* hdma){

	uint32_t tickstart;
	uint32_t temp = 0U;
	DMA_BaseRegistersTypeDef* registers;

	if((hdma == NULL) || (hdma->Instance == NULL)){
		return VIC_ERROR;
	}

	/* change the DMA State */
	hdma->State = DMA_STATE_BUSY;

	/* Initialize the lock resource. */
	hdma->Lock = ARM_UNLOCKED;

	/* Disable the Peripheral */
    hdma->Instance->CR &= ~(0x01UL << 0U);

	tickstart = Get_Tick();

    /* Check whether the stream is disabled */
    while((hdma->Instance->CR & (0x01UL << 0U)) != 0U){
    	if((Get_Tick() - tickstart) > DMA_TIMEOUT_ABORT){

    		hdma->State = DMA_STATE_TIMEOUT;
    		return VIC_TIMEOUT;
    	}
    }

    temp = hdma->Instance->CR;

    temp &= ((uint32_t)~0x0FEF7FE0UL);

    temp |= hdma->Init.Channel					| hdma->Init.Direction	      |
    		hdma->Init.PeriphInc				| hdma->Init.MemInc			  |
    		hdma->Init.PeriphDataAlignment		| hdma->Init.MemDataAlignment |
    		hdma->Init.Mode						| hdma->Init.Priority;


    if(hdma->Init.FIFOMode == DMA_FIFOMODE_ENABLE){
    	temp |= hdma->Init.MemBurst | hdma->Init.PeriphBurst;
    }

    hdma->Instance->CR = temp;

    temp = hdma->Instance->FCR;

    temp &= (uint32_t)~(0x07U);

    temp |= hdma->Init.FIFOMode;

    if(hdma->Init.FIFOMode == DMA_FIFOMODE_ENABLE){
    	temp |= hdma->Init.FIFOThreshold;
    }

    hdma->Instance->FCR = temp;

	registers = (DMA_BaseRegistersTypeDef*)DMA_CalcBaseAndBitshift(hdma);

	registers->IFCR = 0x3FUL << hdma->StreamIndex;

	hdma->State = DMA_STATE_READY;

	return VIC_OK;
}

static uint32_t DMA_CalcBaseAndBitshift(DMA_HandleTypeDef* hdma){
	uint32_t streamNumber;
	static const uint8_t flagBitshiftOffset[8] = {
		0U, 6U, 16U, 22U, 0U, 6U, 16U, 22U
	};

	streamNumber = ((((uint32_t)hdma->Instance & 0xFFU) - 16U) / 24U);
	hdma->StreamIndex = flagBitshiftOffset[streamNumber];

	if(streamNumber > 3U){
		/* HISR/HIFCR register pair for streams 4-7. */
		hdma->StreamBaseAddress =
			(((uint32_t)hdma->Instance & (uint32_t)~0x3FFU) + 4U);
	}else{
		/* LISR/LIFCR register pair for streams 0-3. */
		hdma->StreamBaseAddress =
			((uint32_t)hdma->Instance & (uint32_t)~0x3FFU);
	}

	return hdma->StreamBaseAddress;
}


Status_TypeDef DMA_START_IT(DMA_HandleTypeDef* hdma, uint32_t SrcAddr, uint32_t DstAddr, uint32_t DataLength){

	Status_TypeDef status = VIC_OK;
	DMA_BaseRegistersTypeDef *regs;

	if((hdma == NULL) || (SrcAddr == 0U) || (DstAddr == 0U) ||
		(DataLength == 0U) || (DataLength > 0xFFFFU)){
		return VIC_ERROR;
	}

	regs = (DMA_BaseRegistersTypeDef *)hdma->StreamBaseAddress;

	if(hdma->State == DMA_STATE_READY){
		hdma->State = DMA_STATE_BUSY;

		DMA_SetConfig(hdma, SrcAddr, DstAddr, DataLength);

		regs->IFCR = 0x3FUL << hdma->StreamIndex;

		hdma->Instance->CR |= (0x01UL << 4U) | (0x01UL << 2U) | (0x01UL << 1UL);

		if(hdma->XferHalfCpltCallback != NULL){
			hdma->Instance->CR |= (0x01UL << 3U);
		}

		hdma->Instance->CR |= (0x01UL << 0U);

	}else{
		status = VIC_BUSY;
	}

	return status;
}

void DMA_IRQHandler(DMA_HandleTypeDef* hdma){
	DMA_BaseRegistersTypeDef *regs;
	uint32_t pendingFlags;

	if(hdma == NULL){
		return;
	}

	regs = (DMA_BaseRegistersTypeDef *)hdma->StreamBaseAddress;
	pendingFlags = regs->ISR >> hdma->StreamIndex;

	/* Transfer error or direct-mode error. */
	if((pendingFlags & ((1UL << 3U) | (1UL << 2U))) != 0U){
		regs->IFCR = ((1UL << 3U) | (1UL << 2U)) << hdma->StreamIndex;
		hdma->Instance->CR &= ~((1UL << 4U) | (1UL << 3U) |
				(1UL << 2U) | (1UL << 1U) | (1UL << 0U));
		hdma->State = DMA_STATE_ERROR;

		if(hdma->XferErrorCallback != NULL){
			hdma->XferErrorCallback(hdma);
		}
		return;
	}

	/* Half-transfer complete. */
	if((pendingFlags & (1UL << 4U)) != 0U){
		regs->IFCR = (1UL << 4U) << hdma->StreamIndex;
		if(hdma->XferHalfCpltCallback != NULL){
			hdma->XferHalfCpltCallback(hdma);
		}
	}

	/* Transfer complete. */
	if((pendingFlags & (1UL << 5U)) != 0U){
		regs->IFCR = (1UL << 5U) << hdma->StreamIndex;

		if(hdma->Init.Mode != DMA_CIRCULAR){
			hdma->Instance->CR &= ~((1UL << 4U) | (1UL << 3U) |
					(1UL << 2U) | (1UL << 1U));
			hdma->State = DMA_STATE_READY;
		}

		if(hdma->XferCpltCallback != NULL){
			hdma->XferCpltCallback(hdma);
		}
	}
}

void DMA_LINK(UART_HandleTypeDef* huart, DMA_HandleTypeDef* hdma){

	huart->hdmatx = hdma;
	hdma->Parent = huart;

}

static void DMA_SetConfig(DMA_HandleTypeDef* hdma, uint32_t SrcAddr, uint32_t DstAddr, uint32_t DataLength){

	hdma->Instance->CR &= ~(0x01UL << 18U);

	hdma->Instance->NDTR = DataLength;

	if((hdma->Init.Direction) == DMA_MEM_TO_PERP){
		hdma->Instance->PAR = DstAddr;
		hdma->Instance->M0AR = SrcAddr;
	}else{
		hdma->Instance->PAR = SrcAddr;
		hdma->Instance->M0AR = DstAddr;
	}



}
