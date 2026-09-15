/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Srivisweswara Mohan Santhi
 * @brief          : Main program body
 ******************************************************************************
 **/

#include "main.h"
#include "debounce.h"


UART_HandleTypeDef huart2;
CAN_HandleTypeDef hcan1;
DMA_HandleTypeDef hdma_usart2_tx;

Debounce_Handel_t user_btn, user_btn_pc0, user_btn_pc13;

void SystemSetup();
void SystemClock_Config(void);
void M_GPIO_Init(void);
void M_USART2_UART_Init(void);
void Error_Handler(void);
void M_DMA1_Init(void);
void M_CAN1_Init(void);

CAN_TxTypeDef TxHeader;
CAN_RxTypeDef RxHeader;

CAN_FilterTypeDef canFilter;

uint32_t mailbox;

uint8_t txData[8];
uint8_t rxData[8];

char buff[50];

uint32_t canBaudRate = 0;

uint8_t itr=0;

void filter_can(void){

	canFilter.FilterActivation = ENABLE;
	canFilter.FilterFIFOAssignment = RX_FIFO0;
	canFilter.FilterBank = FILTER_BANK0;
	canFilter.FilterMode = CAN_FILTERMODE_IDMASK;
	canFilter.FilterScale = CAN_FILTERSCALE_32BIT;
	canFilter.FilterIdHigh = 0x0000;
	canFilter.FilterIdLow = 0x0000;
	canFilter.FilterMaskIdHigh = 0x0000;
	canFilter.FilterMaskIdLow = 0x0000;
	canFilter.SlaveStartFilterBank = 14;

	if(CAN_ConfigFilter(&hcan1, &canFilter) != VIC_OK){
		printf("Filter Error\r\n\r\n");
		Error_Handler();
	}else{
		printf("Filter Success\r\n\r\n");
	}
}

void transmit_can(void){
	TxHeader.IDE = CAN_EXT_ID;
	TxHeader.ExtId = 0xFFFF;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.DLC = 8;

	txData[0] = itr++;
	txData[1] = itr++;
	txData[2] = itr++;
	txData[3] = itr++;
	txData[4] = itr++;
	txData[5] = itr++;
	txData[6] = itr++;
	txData[7] = itr++;

	if(CAN_TransmitMessage(&hcan1, &TxHeader, txData, &mailbox) != VIC_OK){
		printf("Transmit Failed\r\n\r\n");
		Error_Handler();
	}else{
		printf("Transmit Success\r\n\r\n");
		while (!(CAN1->TSR & (1U << 0U)));
		CAN1->TSR |= 1U << 0U;
	}

}

void recieve_can(void){
	if(CAN_TransmitMessage(&hcan1, &TxHeader, txData, &mailbox) != VIC_OK){
		printf("Transmit Failed\r\n\r\n");
		Error_Handler();
	}else{
		printf("Transmit Success\r\n\r\n");
		while (!(CAN1->TSR & (1U << 0U)));
		CAN1->TSR |= 1U << 0U;
	}
}

void UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == USART2){
		UART_Transmit_DMA(&huart2, (uint8_t*)buff, (uint16_t)strlen(buff));
	}
}

int main(void){

 	SystemSetup();

 	SystemClock_Config();

 	FPU_Init();

 	M_GPIO_Init();

	M_DMA1_Init();
	M_USART2_UART_Init();

	sprintf(buff, "Hello from uart DMA !!!!\r\n");
	UART_Transmit_DMA(&huart2, (uint8_t*)buff, (uint16_t)strlen(buff));

 	while(1){
// 		printf("hellooo worldd !!!\r\n");
// 		uart_tx("hellooo worldd !!!\r\n");
 		delay(1000);
	}
 }

void SystemSetup(){
	__RCC_SYSCFG_CLK_ENABLE();
	TimeBase_Init(SYS_DEF_CORE_CLOCK);
}

void SystemClock_Config(void){
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/*Enable PWR in APB1 Enable Register*/
	__RCC_PWR_CLK_ENABLE();

	/*SET VOS in SCALE1 Mode in CR register in power*/
	__PWR_VOLTAGESCALING_CONFIG();

	RCC_OscInitStruct.OscillatorType = RCC_OSC_TYPE_HSE;
	RCC_OscInitStruct.HSEState = HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = PLL_HSE_SRC;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = 2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;

	if(RCC_OscConfig(&RCC_OscInitStruct) != VIC_OK){
		Error_Handler();
	}

	if(__PWR_OVERDRIVE_ENABLE() != VIC_OK){
		Error_Handler();
	}

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|
								  RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLOCKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HLCK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HLCK_DIV2;

	if(RCC_ClkConfig(&RCC_ClkInitStruct) != VIC_OK){
		Error_Handler();
	}
}

void M_GPIO_Init(void){

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__RCC_GPIOH_CLK_ENABLE();
	__RCC_GPIOA_CLK_ENABLE();
	__RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStruct.Pin       = GPIO_PIN_5;
	GPIO_InitStruct.Mode      = GPIO_OUTPUT;
	GPIO_InitStruct.OType     = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin       = GPIO_PIN_13;
	GPIO_InitStruct.Mode      = GPIO_INPUT;
	GPIO_InitStruct.Pull      = GPIO_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	GPIO_InitStruct.Pin       = GPIO_PIN_0;
	GPIO_InitStruct.Mode      = GPIO_INPUT;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_Init(GPIOC, &GPIO_InitStruct);

 	pc13_exti_interrupt(EXTI15_10_IRQ);

 	Debounce_Init(&user_btn_pc13, GPIOC, GPIO_PIN_13, 20, true);

//	pc0_exti_interrupt(0x06U); // EXTIO0
}

void M_USART2_UART_Init(void){

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = USART_WL_8B;
	huart2.Init.StopBits = USART_STOP_BIT1;
	huart2.Init.parity = USART_PARITY_NONE;
	huart2.Init.Mode = USART_MODE_TX_RX;
	huart2.Init.HWFlowCtl = USART_HWCONTROL_NONE;
	huart2.Init.OverSampling = USART_OverSampling_16;

	if(USART_Init(&huart2) != VIC_OK){
		Error_Handler();
	}
}
void M_DMA1_Init(void){

	__RCC_DMA1_CLK_ENABLE();

	NVIC_Enable(DMA1_Stream6_IRQn); // TX

}

void M_CAN1_Init(void){

	hcan1.Instance = CAN1;
	hcan1.Init.Mode = CAN_LOOPBACK_MODE;
	hcan1.Init.Prescaler = 5;
	hcan1.Init.TimeSegment1 = 15;
	hcan1.Init.TimeSegment2 = 2;
	hcan1.Init.SyncJumpWidth = 1;
	hcan1.Init.TimeTriggeredMode = DISABLE;
	hcan1.Init.AutoBusOff = DISABLE;
	hcan1.Init.AutoWakeUp = DISABLE;
	hcan1.Init.AutoRetranmission = DISABLE;
	hcan1.Init.RecieveFIFOLocked = DISABLE;
	hcan1.Init.TransmitFIFOPriority = DISABLE;

	if(CAN_Init(&hcan1) != VIC_OK){
		Error_Handler();
	}

}

void Error_Handler(void){
	while(1){
		GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		delay(100);
	}
}
