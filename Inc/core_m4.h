/*
 * corem4.h
 *
 *  Created on: Jun 1, 2025
 *      Author: Vichu
 */

#ifndef CORE_M4_H_
#define CORE_M4_H_

#include "main.h"

#define     __IM     volatile const
#define     __OM     volatile
#define     __IOM    volatile

#define NVIC_SETEN_BASE			0xE000E100UL
#define NVIC_CLEAREN_BASE		0xE000E180UL
#define NVIC_SETPEN_BASE		0xE000E200UL
#define NVIC_SETPEN_BASE		0xE000E200UL

#define SYS_CSR_BASE			0xE000E010UL

#define SCB_BASE				0xE000E008

#define SYS_DEF_CORE_CLOCK		16000000UL
#define SYS_CORE_CLOCK			180000000UL

#define HSI_FREQ				16000000UL
#define HSE_FREQ    			8000000U


typedef struct{
	__IOM uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
		uint32_t RESERVED0[24U];
	__IOM uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
		uint32_t RESERVED1[24U];
	__IOM uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
		uint32_t RESERVED2[24U];
	__IOM uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
		uint32_t RESERVED3[24U];
	__IOM uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
		uint32_t RESERVED4[56U];
	__IOM uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
		uint32_t RESERVED5[644U];
	__OM  uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
}NVIC_TypeDef;

typedef struct
{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[5U];
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_TypeDef;

typedef struct{
	__IO uint32_t SCR; // SysTick Control and Status Register, SYST_CSR
	__IO uint32_t RVR; // SysTick Reload Value Register, SYST_RVR
	__IO uint32_t CVR; // SysTick Current Value Register, SYST_CVR
	__IO uint32_t CALIB; // SysTick Calibration value Register, SYST_CALIB
}SysTick_TypeDef;


#define NVIC_R					((NVIC_TypeDef*) NVIC_SETEN_BASE)
#define SysTick					((SysTick_TypeDef*) SYS_CSR_BASE)
#define SCB						((SCB_TypeDef*) SCB_BASE)

#define EXTI15_10_IRQ			(0x28U)
#define USART2_IRQ				(0x26U)


#define DMA1_Stream0_IRQn				(11U)
#define DMA1_Stream1_IRQn				(12U)
#define DMA1_Stream2_IRQn				(13U)
#define DMA1_Stream3_IRQn				(14U)
#define DMA1_Stream4_IRQn				(15U)
#define DMA1_Stream5_IRQn				(16U)
#define DMA1_Stream6_IRQn				(17U)
#define DMA1_Stream7_IRQn				(47U)

void NVIC_Enable(uint32_t IRQn);

#endif /* CORE_M4_H_ */
