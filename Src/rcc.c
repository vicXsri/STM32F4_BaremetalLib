/*
 * rcc.c
 *
 *  Created on: May 30, 2025
 *      Author: Vichu
 */


#include "rcc.h"


void RCC_Enable(uint32_t pheripheral, uint8_t bus){
	if(bus == AHB1_EN)
		RCC->AHB1ENR |= pheripheral;
	else if (bus == AHB2_EN)
		RCC->AHB2ENR |= pheripheral;
	else if (bus == AHB3_EN)
		RCC->AHB3ENR |= pheripheral;
	else if (bus == APB1_EN)
		RCC->APB1ENR |= pheripheral;
	else if (bus == APB2_EN)
		RCC->APB2ENR |= pheripheral;
}

void RCC_Disable(uint32_t pheripheral, uint8_t bus){
	if(bus == AHB1_EN)
		RCC->AHB1ENR &= ~pheripheral;
	else if (bus == AHB2_EN)
		RCC->AHB2ENR &= ~pheripheral;
	else if (bus == AHB3_EN)
		RCC->AHB3ENR &= ~pheripheral;
	else if (bus == APB1_EN)
		RCC->APB1ENR &= ~pheripheral;
	else if (bus == APB2_EN)
		RCC->APB2ENR &= ~pheripheral;
}

Status_TypeDef RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct){

	uint32_t tickstart;

	/*Configure HSE*/
	if((RCC_OscInitStruct->OscillatorType & RCC_OSC_TYPE_HSE) == RCC_OSC_TYPE_HSE){
		if(RCC_OscInitStruct->HSEState == HSE_ON){
			RCC->CR |= (1U << HSE_ON);
			tickstart = Get_Tick();
			while(!(RCC->CR & (1U << HSE_RDY))){
				if((Get_Tick() - tickstart) > HSE_TIMEOUT)	return VIC_TIMEOUT;
			}
		}
		else if(RCC_OscInitStruct->HSEState == HSE_BYP){
			RCC->CR |= (1U << HSE_BYP);
			tickstart = Get_Tick();
			while(!(RCC->CR & (1U << HSE_RDY))){
				if((Get_Tick() - tickstart) > HSE_TIMEOUT)	return VIC_TIMEOUT;
			}
		}
		else{
			RCC->CR &= ~((1U << HSE_ON) | (1U << HSE_BYP));
			tickstart = Get_Tick();
			while(RCC->CR & (1U << HSE_RDY)){
				if((Get_Tick() - tickstart) > HSE_TIMEOUT)	return VIC_TIMEOUT;
			}
		}
	}

	/*Configure HSI*/
	if((RCC_OscInitStruct->OscillatorType & RCC_OSC_TYPE_HSI) == RCC_OSC_TYPE_HSI){
		if(RCC_OscInitStruct->HSIState == HSI_ON){
			RCC->CR |= (1U << HSI_ON);
			tickstart = Get_Tick();
			while(!(RCC->CR & (1U << HSI_RDY))){
				if((Get_Tick() - tickstart) > HSI_TIMEOUT)	return VIC_TIMEOUT;
			}
		}
		else{
			RCC->CR &= ~(1U << HSI_ON);
			tickstart = Get_Tick();
			while(RCC->CR & (1U << HSI_RDY)){
				if((Get_Tick() - tickstart) > HSI_TIMEOUT)	return VIC_TIMEOUT;
			}
		}
	}

	/*Configure LSE*/
	if((RCC_OscInitStruct->OscillatorType & RCC_OSC_TYPE_LSE) == RCC_OSC_TYPE_LSE){
		if(RCC_OscInitStruct->LSEState == LSE_ON){
			RCC->BDCR |= (1U << LSE_ON);
			tickstart = Get_Tick();
			while(!(RCC->BDCR & (1U << LSE_RDY))){
				if((Get_Tick() - tickstart) > LSE_TIMEOUT) return VIC_TIMEOUT;
			}
		}
		else{
			RCC->BDCR &= ~(1U << LSE_ON);
			tickstart = Get_Tick();
			while(RCC->BDCR & (1U << LSE_RDY)){
				if((Get_Tick() - tickstart) > LSE_TIMEOUT) return VIC_TIMEOUT;
			}
		}
	}

	/*Configure LSI*/
	if((RCC_OscInitStruct->OscillatorType & RCC_OSC_TYPE_LSI) == RCC_OSC_TYPE_LSI){
		if(RCC_OscInitStruct->LSIState == LSI_ON){
			RCC->CSR |= (1U << LSI_ON);
			tickstart = Get_Tick();
			while(!(RCC->CSR & (1U << LSI_RDY))){
				if((Get_Tick() - tickstart) > LSI_TIMEOUT)	return VIC_TIMEOUT;
			}
		}
		else{
			RCC->CSR &= ~(1U << LSI_ON);
			tickstart = Get_Tick();
			while(RCC->CSR & (1U << LSI_RDY)){
				if((Get_Tick() - tickstart) > LSI_TIMEOUT)	return VIC_TIMEOUT;
			}
		}
	}

	/*Configure PLL*/
	if(RCC_OscInitStruct->PLL.PLLState != PLL_NONE){
		/*Disable PLL before config*/
		RCC->CR &= ~ (1U <<PLL_ON);
		tickstart = Get_Tick();
		while(RCC->CR & (1U << PLL_RDY)){
			if((Get_Tick() - tickstart) > PLL_TIMEOUT)	return VIC_TIMEOUT;
		}
		RCC->PLLCFGR = 0x0000;
		RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLSource << PLLSRC_Pos);
		RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLM << PLLM_Pos);
		RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLN << PLLN_Pos);
		RCC->PLLCFGR |= (((RCC_OscInitStruct->PLL.PLLP >> 1U) - 1U) << PLLP_Pos);
		RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLQ << PLLQ_Pos);
		RCC->PLLCFGR |= (RCC_OscInitStruct->PLL.PLLR << PLLR_Pos);


		RCC->CR |= (1U <<PLL_ON);

		tickstart = Get_Tick();
		while(!(RCC->CR & (1U << PLL_RDY))){
			if((Get_Tick() - tickstart) > PLL_TIMEOUT)	return VIC_TIMEOUT;
		}
	}

	return VIC_OK;
}

Status_TypeDef RCC_ClkConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct){

	uint32_t tickstart;

	__FLASH_PREFETCH_LATENCY();

	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= RCC_ClkInitStruct->SYSCLKSource << RCC_CFGR_SW_Pos;

	RCC->CFGR &= ~(RCC_CFGR_HPRE_Msk |
			       RCC_CFGR_PPRE1_Msk |
				   RCC_CFGR_PPRE2_Msk);

	RCC->CFGR |= (RCC_ClkInitStruct->AHBCLKDivider  << RCC_CFGR_HPRE_Pos |
				  RCC_ClkInitStruct->APB1CLKDivider << RCC_CFGR_PPRE1_Pos |
				  RCC_ClkInitStruct->APB2CLKDivider << RCC_CFGR_PPRE2_Pos);

	tickstart = Get_Tick();

	while((RCC->CFGR & (0x03 << RCC_CFGR_SWS_Pos)) != (RCC_ClkInitStruct->SYSCLKSource << RCC_CFGR_SWS_Pos)){
		if((Get_Tick() - tickstart) > CLOCKSWITCH_TIMEOUT) return VIC_TIMEOUT;
	}

	TimeBase_Init(SYS_CORE_CLOCK);

	return VIC_OK;
}

uint32_t RCC_GetHCLK_Freq(void){
	uint32_t sysclk_src = (RCC->CFGR >> 2) & 0x03;
	uint32_t pll_src, pllm, plln, pllp,pllr;
	uint32_t sysclk_freq;

	switch(sysclk_src){
		case 0x00: //HSI
			sysclk_freq = HSI_FREQ;
			break;
		case 0x01: //HSE
			sysclk_freq = HSE_FREQ;
			break;
		case 0x02: //PLLCLK
			pll_src = (RCC->PLLCFGR & (1U << 22)) ? HSE_FREQ :
												    HSI_FREQ;
			pllm = RCC->PLLCFGR & 0x3F;
			plln = (RCC->PLLCFGR >> 6) & 0x1FF;
			pllp = (((RCC->PLLCFGR >> 16) & 0x3) + 1) * 2;
			sysclk_freq = (pll_src / pllm) * plln / pllp;
			break;
		case 0x03: //PLLCR
			pll_src = (RCC->PLLCFGR & (1U << 22)) ? HSE_FREQ :
												    HSI_FREQ;
			pllm = RCC->PLLCFGR & 0x3F;
			plln = (RCC->PLLCFGR >> 6) & 0x1FF;
			pllr = ((RCC->PLLCFGR >> 28) & 0x7);
			sysclk_freq = (pll_src / pllm) * plln / pllr;
			break;
	}
	return sysclk_freq;
}
uint32_t RCC_GetP1CLK_Freq(void){
	uint32_t apb1_Prescaler = (RCC->CFGR >> 10) & 0x7;
	if(apb1_Prescaler < 4)
		return RCC_GetHCLK_Freq();
	else
		return RCC_GetHCLK_Freq()/(1 << (apb1_Prescaler - 3));

}
uint32_t RCC_GetP2CLK_Freq(void){
	uint32_t apb2_Prescaler = (RCC->CFGR >> 13) & 0x7;

	return (RCC_GetHCLK_Freq()  / apb2_Prescaler);
}

void __RCC_GPIOA_CLK_ENABLE(void){
	RCC->AHB1ENR |= GPIOAEN;
}
void __RCC_GPIOB_CLK_ENABLE(void){
	RCC->AHB1ENR |= GPIOBEN;
}
void __RCC_GPIOC_CLK_ENABLE(void){
	RCC->AHB1ENR |= GPIOCEN;
}
void __RCC_GPIOD_CLK_ENABLE(void){
	RCC->AHB1ENR |= GPIODEN;
}
void __RCC_GPIOE_CLK_ENABLE(void){
	RCC->AHB1ENR |= GPIOEEN;
}
void __RCC_GPIOF_CLK_ENABLE(void){
	RCC->AHB1ENR |= GPIOFEN;
}
void __RCC_GPIOG_CLK_ENABLE(void){
	RCC->AHB1ENR |= GPIOGEN;
}
void __RCC_GPIOH_CLK_ENABLE(void){
	RCC->AHB1ENR |= GPIOHEN;
}


void __RCC_PWR_CLK_ENABLE(void){
	RCC->APB1ENR |= (1U << APB1_PWR_EN);
}
void __RCC_USART2_CLK_ENABLE(void){
	RCC->APB1ENR |= (1U << APB1_USART2_EN);
}
void __RCC_USART3_CLK_ENABLE(void){
	RCC->APB1ENR |= (1U << APB1_USART3_EN);
}

void __RCC_CAN1_CLK_ENABLE(void){
	RCC->APB1ENR |= (1U << APB1_CAN1_EN);
}
void __RCC_CAN2_CLK_ENABLE(void){
	RCC->APB1ENR |= (1U << APB1_CAN2_EN);
}

void __RCC_SYSCFG_CLK_ENABLE(void){
	RCC->APB2ENR |= SYSCFG_EN;
}

void __RCC_DMA1_CLK_ENABLE(void){
	RCC->AHB1ENR |= DMA1_EN;
}
void __RCC_DMA2_CLK_ENABLE(void){
	RCC->AHB1ENR |= DMA2_EN;
}

void __RCC_CRC_CLK_ENABLE(void){
	RCC->AHB1ENR |= CRC_EN;
}
