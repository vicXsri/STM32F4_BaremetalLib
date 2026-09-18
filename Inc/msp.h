/*
 * msp.h
 *
 *  Created on: Jun 13, 2025
 *      Author: Vichu
 */

#ifndef MSP_H_
#define MSP_H_

#include "main.h"

//void USART_MspInit(UART_HandleTypeDef* huart);
//void CAN1_MspInit(CAN_HandleTypeDef* hcan);

void CRC_MspInit(CRC_TypeDef* hcrc);

#endif /* MSP_H_ */
