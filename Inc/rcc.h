/*
 * rcc.h
 *
 *  Created on: May 30, 2025
 *      Author: Vichu
 */

#ifndef RCC_H_
#define RCC_H_

#include "main.h"

typedef struct{
	__IO uint32_t CR; //RCC clock control register
	__IO uint32_t PLLCFGR; //RCC PLL configuration register
	__IO uint32_t CFGR; //RCC clock configuration register
	__IO uint32_t CIR; //RCC clock interrupt register
	__IO uint32_t AHB1RSTR; //RCC AHB1 peripheral reset register
	__IO uint32_t AHB2RSTR; //RCC AHB2 peripheral reset register
	__IO uint32_t AHB3RSTR; //RCC AHB3 peripheral reset register
	uint32_t RESERVED1[1]; // Reserved 0x28 - 0x2C
	__IO uint32_t APB1RSTR; //RCC APB1 peripheral reset register
	__IO uint32_t APB2RSTR; //RCC APB2 peripheral reset register
	uint32_t RESERVED2[2]; // Reserved 0x28 - 0x2C
	__IO uint32_t AHB1ENR; //RCC AHB1 peripheral enable register
	__IO uint32_t AHB2ENR; //RCC AHB2 peripheral enable register
	__IO uint32_t AHB3ENR; //RCC AHB3 peripheral enable register
	uint32_t RESERVED3[1]; // Reserved 0x3C
	__IO uint32_t APB1ENR; //RCC APB1 peripheral clock enable register
	__IO uint32_t APB2ENR; //RCC APB2 peripheral clock enable register
	uint32_t RESERVED4[2]; // Reserved 0x48 - 0x4C
	__IO uint32_t AHB1LPENR; //RCC AHB1 peripheral clock enable in low power mode register
	__IO uint32_t AHB2LPENR; //RCC AHB2 peripheral clock enable in low power mode register
	__IO uint32_t AHB3LPENR; //RCC AHB3 peripheral clock enable in low power mode register
	uint32_t RESERVED5[1]; // Reserved 0x48 - 0x4C
	__IO uint32_t APB1LPENR; //RCC APB1 peripheral clock enable in low power mode register
	__IO uint32_t APB2LPENR; //RCC APB2 peripheral clock enabled in low power mode register
	uint32_t RESERVED6[2]; // Reserved 0x68 - 0x6C
	__IO uint32_t BDCR; //RCC Backup domain control register
	__IO uint32_t CSR; //RCC clock control & status register
	uint32_t RESERVED7[2]; // Reserved 0x78 - 0x7C
	__IO uint32_t SSCGR; //RCC spread spectrum clock generation register
	__IO uint32_t PLLI2SCFGR; //RCC PLLI2S configuration register
	__IO uint32_t PLLSAICFGR; //RCC PLL configuration register
	__IO uint32_t DCKCFGR; //RCC dedicated clock configuration register
	__IO uint32_t CKGATENR; //RCC clocks gated enable register
	__IO uint32_t DCKCFGR2; //RCC dedicated clocks configuration register 2
}RCC_TypeDef;

typedef struct{
	uint32_t PLLState; /*New state of PLL*/
	uint32_t PLLSource; /*PLL entry Clock Source*/
	uint32_t PLLM; /*PLLM Division factor for PLL VCO*/
	uint32_t PLLN; /*PLLN Multiplication factor for PLL VCO*/
	uint32_t PLLP; /*PLLP Division factor for main system clock*/
	uint32_t PLLQ; /*PLLQ Division factor for OTG FS, SDIO and RNG*/
	uint32_t PLLR; /*PLLQ Division factor for I2S & SAI*/
}RCC_PLLInitTypeDef;

typedef struct{
	uint32_t OscillatorType; /*Which Oscillator to be configured*/
	uint32_t HSEState; /*The new state of HSE*/
	uint32_t LSEState; /*The new state of LSE*/
	uint32_t HSIState; /*The new state of HSI*/
	uint32_t HSICalibrationValue; /*HSI Calibration Trimming Value*/
	uint32_t LSIState; /*The new state of LSI*/
	RCC_PLLInitTypeDef PLL; /*PLL Parameters*/
}RCC_OscInitTypeDef;

typedef struct{
	uint32_t ClockType;	/*Clock to be Configured*/
	uint32_t SYSCLKSource;	/*The Clock source (SYSCLKS) used as system clock*/
	uint32_t AHBCLKDivider;	/*AHB Clock Divider (HCLK)*/
	uint32_t APB1CLKDivider;	/*APB1 Clock Divider (PCLK1)*/
	uint32_t APB2CLKDivider;	/*APB2 Clock Divider (PCLK2)*/
}RCC_ClkInitTypeDef;

#define RCC					((RCC_TypeDef*) RCC_BASE)

#define GPIOAEN				(1U << 0)
#define GPIOBEN				(1U << 1)
#define GPIOCEN				(1U << 2)
#define GPIODEN				(1U << 3)
#define GPIOEEN				(1U << 4)
#define GPIOFEN				(1U << 5)
#define GPIOGEN				(1U << 6)
#define GPIOHEN				(1U << 7)
#define DMA1_EN  			(1UL << 21)
#define DMA2_EN  			(1UL << 22)

#define SYSCFG_EN  			(1U << 14)

#define AHB1_EN				(0x01U)
#define AHB2_EN				(0x02U)
#define AHB3_EN				(0x03U)
#define APB1_EN				(0x04U)
#define APB2_EN				(0x05U)


#define	HSI_ON				(0x00)
#define	HSI_RDY				(0x01)

			/*HSE Config*/
#define	HSE_OFF				(0x00U)
#define	HSE_ON				(0x10U)
#define	HSE_RDY				(0x11U)
#define	HSE_BYP				(0x12U)
#define	CSS_ON				(0x13U)

#define	LSI_ON				(0x00U)
#define	LSI_RDY				(0x01U)

#define LSE_ON				(0x00U)
#define LSE_RDY				(0x01U)

#define PLL_NONE			(0x00U)
#define PLL_ON				(0x18U)
#define PLL_RDY				(0x19U)

#define PLL_HSE_SRC			(0x01U)
#define PLL_HSI_SRC			(0x00U)

#define PLLM_Pos     0U
#define PLLN_Pos     6U
#define PLLP_Pos     16U
#define PLLSRC_Pos   22U
#define PLLQ_Pos     24U
#define PLLR_Pos     28U

#define HSE_TIMEOUT					100U
#define HSI_TIMEOUT					2U
#define	LSE_TIMEOUT					2U
#define LSI_TIMEOUT					2U
#define PLL_TIMEOUT					2U
#define CLOCKSWITCH_TIMEOUT			5000U

#define RCC_OSC_TYPE_NONE	(0x00U)
#define RCC_OSC_TYPE_HSE	(0x01U)
#define RCC_OSC_TYPE_HSI	(0x02U)
#define RCC_OSC_TYPE_LSE	(0x04U)
#define RCC_OSC_TYPE_LSI	(0x08U)

#define RCC_CLOCKTYPE_SYSCLK	(0x01U)
#define RCC_CLOCKTYPE_HCLK		(0x02U)
#define RCC_CLOCKTYPE_PCLK1		(0x04U)
#define RCC_CLOCKTYPE_PCLK2		(0x08U)

#define RCC_SYSCLOCKSOURCE_HSI		(0x00U)
#define RCC_SYSCLOCKSOURCE_HSE		(0x01U)
#define RCC_SYSCLOCKSOURCE_PLLCLK	(0x02U)
#define RCC_SYSCLOCKSOURCE_PLLRCLK	(0x03U)

/*AHB CLock Source*/
#define RCC_SYSCLK_DIV1				(0x00U)
#define RCC_SYSCLK_DIV2				(0x08U)
#define RCC_SYSCLK_DIV4				(0x09U)
#define RCC_SYSCLK_DIV8				(0x0AU)
#define RCC_SYSCLK_DIV16			(0x0BU)
#define RCC_SYSCLK_DIV64			(0x0CU)
#define RCC_SYSCLK_DIV128			(0x0DU)
#define RCC_SYSCLK_DIV256			(0x0EU)
#define RCC_SYSCLK_DIV512			(0x0FU)

#define RCC_HLCK_DIV1				(0x00U)
#define RCC_HLCK_DIV2				(0x04U)
#define RCC_HLCK_DIV4				(0x05U)
#define RCC_HLCK_DIV8				(0x06U)
#define RCC_HLCK_DIV16				(0x07U)


// AHB Prescaler Mask and Position
#define RCC_CFGR_HPRE_Pos     4U
#define RCC_CFGR_HPRE_Msk     (0xFU << RCC_CFGR_HPRE_Pos)

// APB1 Prescaler Mask and Position
#define RCC_CFGR_PPRE1_Pos    10U
#define RCC_CFGR_PPRE1_Msk    (0x7U << RCC_CFGR_PPRE1_Pos)

// APB2 Prescaler Mask and Position
#define RCC_CFGR_PPRE2_Pos    13U
#define RCC_CFGR_PPRE2_Msk    (0x7U << RCC_CFGR_PPRE2_Pos)

// System Clock Switch (SW) Position and Mask
#define RCC_CFGR_SW_Pos       0U
#define RCC_CFGR_SW_Msk       (0x3U << RCC_CFGR_SW_Pos)

// System Clock Switch Status (SWS) Position
#define RCC_CFGR_SWS_Pos      2U

#define APB1_PWR_EN			  (0x1CU)
#define APB1_USART2_EN		  (0x11U)
#define APB1_CAN1_EN		  (0x19U)
#define APB1_CAN2_EN		  (0x1AU)

void RCC_Enable(uint32_t pheripheral, uint8_t bus);
void RCC_Disable(uint32_t pheripheral, uint8_t bus);

Status_TypeDef RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
Status_TypeDef RCC_ClkConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct);

uint32_t RCC_GetHCLK_Freq(void);
uint32_t RCC_GetP1CLK_Freq(void);
uint32_t RCC_GetP2CLK_Freq(void);

void __RCC_GPIOA_CLK_ENABLE(void);
void __RCC_GPIOB_CLK_ENABLE(void);
void __RCC_GPIOC_CLK_ENABLE(void);
void __RCC_GPIOD_CLK_ENABLE(void);
void __RCC_GPIOE_CLK_ENABLE(void);
void __RCC_GPIOF_CLK_ENABLE(void);
void __RCC_GPIOG_CLK_ENABLE(void);
void __RCC_GPIOH_CLK_ENABLE(void);


void __RCC_PWR_CLK_ENABLE(void);
void __RCC_USART2_CLK_ENABLE(void);
void __RCC_CAN1_CLK_ENABLE(void);
void __RCC_CAN2_CLK_ENABLE(void);
void __RCC_SYSCFG_CLK_ENABLE(void);
void __RCC_DMA1_CLK_ENABLE(void);
void __RCC_DMA2_CLK_ENABLE(void);

#endif /* RCC_H_ */
