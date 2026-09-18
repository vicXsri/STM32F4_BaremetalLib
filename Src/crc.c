/*
 * crc.c
 *
 *  Created on: Sep 16, 2026
 *      Author: Vichu
 */


#include "crc.h"

Status_TypeDef CRC_Init(CRC_TypeDef* hcrc){

	if(hcrc == NULL){
		return VIC_ERROR;
	}

	CRC_MspInit(hcrc);

	return VIC_OK;
}

uint32_t CRC_Accumulate(CRC_TypeDef* hcrc, uint32_t pBuffer[], uint32_t BufferLength){

//	uint32_t temp = 0U;

//	CRC->CR = (0x01UL << 0U);

	for(uint32_t i = 0; i < BufferLength; i++){
		hcrc->DR = pBuffer[i];
	}

	return hcrc->DR;

}
