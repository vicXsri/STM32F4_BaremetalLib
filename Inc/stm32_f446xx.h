/*
 * stm32_f446xx.h
 *
 *  Created on: May 31, 2025
 *      Author: Vichu
 */

#ifndef STM32_F446XX_H_
#define STM32_F446XX_H_

#include "main.h"


#define PERIPH_BASE            (0x40000000UL) /*!< Base address of : AHB/ABP Peripherals                                                   */
#define APB1_BASE        	   (PERIPH_BASE + 0x00000UL) // Starting Address of APB1                                                 */
#define APB2_BASE        	   (PERIPH_BASE + 0x10000UL) // Starting Address of APB2                                                 */
#define AHB1_BASE        	   (PERIPH_BASE + 0x20000UL) // Starting Address of AHB1                                                 */

#define EXTI_BASE			   (PERIPH_BASE + 0x13C00UL)

#define SYSCFG_BASE			   (APB2_BASE + 0x3800UL)

#define RCC_BASE			   (AHB1_BASE + 0x3800UL)

#define PWR_BASE			   (PERIPH_BASE + 0x7000UL)

#define FLASH_BASE			   (AHB1_BASE + 0x3C00UL )

#define GPIOA_BASE		(AHB1_BASE + 0x0000UL)
#define GPIOB_BASE		(AHB1_BASE + 0x0400UL)
#define GPIOC_BASE		(AHB1_BASE + 0x0800UL)
#define GPIOD_BASE		(AHB1_BASE + 0x0C00UL)
#define GPIOE_BASE		(AHB1_BASE + 0x1000UL)
#define GPIOF_BASE		(AHB1_BASE + 0x1400UL)
#define GPIOG_BASE		(AHB1_BASE + 0x1800UL)
#define GPIOH_BASE		(AHB1_BASE + 0x1C00UL)

#define USART1_BASE			   (APB2_BASE + 0x1000UL )
#define USART2_BASE			   (APB1_BASE + 0x4400UL )
#define USART3_BASE			   (APB1_BASE + 0x4800UL )
#define UART4_BASE			   (APB1_BASE + 0x4C00UL )
#define UART5_BASE			   (APB1_BASE + 0x5000UL )
#define USART6_BASE			   (APB2_BASE + 0x1400UL )

#define CAN1_BASE			   (APB1_BASE + 0x6400UL )
#define CAN2_BASE			   (APB1_BASE + 0x6800UL )

#define DMA1_BASE		 		(AHB1_BASE + 0x6000UL)
#define DMA1_Stream0_Base		(DMA1_BASE + 0x010UL)
#define DMA1_Stream1_Base		(DMA1_BASE + 0x028UL)
#define DMA1_Stream2_Base		(DMA1_BASE + 0x040UL)
#define DMA1_Stream3_Base		(DMA1_BASE + 0x058UL)
#define DMA1_Stream4_Base		(DMA1_BASE + 0x070UL)
#define DMA1_Stream5_Base		(DMA1_BASE + 0x088UL)
#define DMA1_Stream6_Base		(DMA1_BASE + 0x0A0UL)
#define DMA1_Stream7_Base		(DMA1_BASE + 0x0B8UL)

#define DMA2_BASE		 		(AHB1_BASE + 0x6400UL)
#define DMA2_Stream0_Base		(DMA2_BASE + 0x010UL)
#define DMA2_Stream1_Base		(DMA2_BASE + 0x028UL)
#define DMA2_Stream2_Base		(DMA2_BASE + 0x040UL)
#define DMA2_Stream3_Base		(DMA2_BASE + 0x058UL)
#define DMA2_Stream4_Base		(DMA2_BASE + 0x070UL)
#define DMA2_Stream5_Base		(DMA2_BASE + 0x088UL)
#define DMA2_Stream6_Base		(DMA2_BASE + 0x0A0UL)
#define DMA2_Stream7_Base		(DMA2_BASE + 0x0B8UL)


#include "main.h"

typedef struct{
	__IO uint32_t LISR;
	__IO uint32_t HISR;
	__IO uint32_t LIFCR;
	__IO uint32_t HIFCR;
}DMA_TypeDef;

typedef struct{
	  __IO uint32_t CR;
	  __IO uint32_t NDTR;
	  __IO uint32_t PAR;
	  __IO uint32_t M0AR;
	  __IO uint32_t M1AR;
	  __IO uint32_t FCR;
}DMA_StreamTypeDef;

typedef struct{
	uint32_t Channel;

	uint32_t Direction;

	uint32_t PeriphInc;

	uint32_t MemInc;

	uint32_t PeriphDataAlignment;

	uint32_t MemDataAlignment;

	uint32_t Mode;

	uint32_t Priority;

	uint32_t FIFOMode;

	uint32_t FIFOThreshold;

	uint32_t MemBurst;

	uint32_t PeriphBurst;

}DMA_InitTypedef;

typedef enum{
	DMA_STATE_RESET 	= 0x00U,
	DMA_STATE_READY 	= 0x01U,
	DMA_STATE_BUSY 		= 0x02U,
	DMA_STATE_TIMEOUT 	= 0x03U,
	DMA_STATE_ERROR 	= 0x04U,
	DMA_STATE_ABORT 	= 0x05U,
}DMA_StateTypeDef;

typedef struct{
	__IO uint32_t ISR;
	uint32_t RESERVED;
	__IO uint32_t IFCR;
}DMA_BaseRegistersTypeDef;

typedef struct __DMA_HandleTypeDef{

	DMA_StreamTypeDef* Instance;
	DMA_InitTypedef Init;
	LOCK_TypeDef Lock;
	DMA_StateTypeDef State;
	void			*Parent;
	void 			(*XferCpltCallback)(struct __DMA_HandleTypeDef* hdma);
	void 			(*XferHalfCpltCallback)(struct __DMA_HandleTypeDef* hdma);
	void 			(*XferM1CpltCallback)(struct __DMA_HandleTypeDef* hdma);
	void 			(*XferM1HalfCpltCallback)(struct __DMA_HandleTypeDef* hdma);
	void 			(*XferErrorCallback)(struct __DMA_HandleTypeDef* hdma);
	void 			(*XferAbortCallback)(struct __DMA_HandleTypeDef* hdma);

	uint32_t StreamBaseAddress;
	uint32_t StreamIndex;
}DMA_HandleTypeDef;

typedef struct{
	uint32_t BaudRate;
	uint32_t WordLength;
	uint32_t StopBits;
	uint32_t parity;
	uint32_t Mode;
	uint32_t HWFlowCtl;
	uint32_t OverSampling;
}UART_InitTypeDef;

typedef struct{
	uint32_t SR;	// Status register
	uint32_t DR; 	// Data register
	uint32_t BRR; 	// Baud rate register
	uint32_t CR1; 	// Control register 1
	uint32_t CR2; 	// Control register 2
	uint32_t CR3; 	// Control register 3
	uint32_t GTPR; 	// Guard time and prescaler register
}USART_TypeDef;

typedef struct {
	USART_TypeDef		*Instance; /*Chooses Which UART*/
	UART_InitTypeDef	 Init;
	const uint8_t       *pTxBuffptr;
	uint16_t 	      	 TxXferSize;
	__IO uint16_t 	     TxXferCount;

	DMA_HandleTypeDef	 *hdmatx;
	DMA_HandleTypeDef	 *hdmarx;

}UART_HandleTypeDef;

#endif /* STM32_F446XX_H_ */
