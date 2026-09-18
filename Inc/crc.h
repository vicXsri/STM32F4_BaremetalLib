/*
 * crc.h
 *
 *  Created on: Sep 16, 2026
 *      Author: Vichu
 */

#ifndef CRC_H_
#define CRC_H_

#include "main.h"


#define CRC		((CRC_TypeDef*) CRC_Base)

Status_TypeDef CRC_Init(CRC_TypeDef* hcrc);
uint32_t CRC_Accumulate(CRC_TypeDef* hcrc, uint32_t pBuffer[], uint32_t BufferLength);
#endif /* CRC_H_ */
