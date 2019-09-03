/*
 * main.c
 *
 *  Created on: 02-May-2019
 *      Author: krishna
 */
#include "stm32f4xx_hal.h"
#include "main.h"
#include"string.h"
#include <stdio.h>


#define TRUE 1
#define FALSE 0

void GPIO_Init(void);
void Error_Handler(void);
void UART2_Init(void);
void SystemClock_Config(uint8_t clock_freq);
void CAN1_Init(void);
void CAN1_Tx(uint32_t Stdid, uint8_t led_no);
void CAN1_Rx(void);
void CAN_Filter_Config(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void Timer3_Init(void);
void Timer4_Init(void);
void Timer6_Init(void);
void Timer7_Init(void);
//void GLOW_Corresponding_LED(int8_t ledno);

UART_HandleTypeDef huart2;
CAN_HandleTypeDef hcan1;
TIM_HandleTypeDef htimer3;
TIM_HandleTypeDef htimer4;
TIM_HandleTypeDef htimer6;
TIM_HandleTypeDef htimer7;

uint32_t TxMailbox1;
CAN_RxHeaderTypeDef RxHeader1;



char msg[100];
int main (void)

{
	        HAL_Init();
	        BSP_LED_Init(LED2);
	        SystemClock_Config(SYS_CLOCK_FREQ_50_MHZ);
			GPIO_Init();
			Timer6_Init();
			Timer7_Init();
			Timer3_Init();
			Timer4_Init();
			UART2_Init();
			CAN1_Init();
			CAN_Filter_Config();
			if(HAL_CAN_ActivateNotification(&hcan1,CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_BUSOFF)!=HAL_OK)
			{
					Error_Handler();

			}

			if (HAL_CAN_Start(&hcan1) != HAL_OK)
			{
			Error_Handler();

			}

			if(HAL_TIM_Base_Start_IT(&htimer6) != HAL_OK)
			{
			Error_Handler();
			}

			if(HAL_TIM_Base_Start_IT(&htimer7) != HAL_OK)
			{
			Error_Handler();
			}
			if(HAL_TIM_Base_Start_IT(&htimer3) != HAL_OK)
			{
			 Error_Handler();
			}
			if(HAL_TIM_Base_Start_IT(&htimer4) != HAL_OK)
			{
			 Error_Handler();
			}

		while(1);
		return 0;

}
void UART2_Init(void)

{
	 huart2.Instance = USART2;
	 huart2.Init.BaudRate = 115200;
	 huart2.Init.WordLength = UART_WORDLENGTH_8B;
	 huart2.Init.StopBits = UART_STOPBITS_1;
	 huart2.Init.Parity = UART_PARITY_NONE;
	 huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	 huart2.Init.Mode = UART_MODE_TX_RX;

	if( HAL_UART_Init(&huart2)!= HAL_OK)
	{
		Error_Handler();
		//only to indictae there is an error
	}
}
void SystemClock_Config(uint8_t clock_freq)
{
	RCC_OscInitTypeDef  osc_init;
	RCC_ClkInitTypeDef  clk_init;
	uint32_t flatency;

		osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
		osc_init.HSEState  = RCC_HSE_BYPASS;

		osc_init.PLL.PLLState= RCC_PLL_ON;
		osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

		switch(clock_freq)
		{
		  case SYS_CLOCK_FREQ_50_MHZ:
		 {
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |  RCC_CLOCKTYPE_PCLK1 |  RCC_CLOCKTYPE_PCLK2 ;
			 clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			 clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			 clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			 clk_init.APB2CLKDivider =RCC_HCLK_DIV2;

			 flatency = FLASH_ACR_LATENCY_1WS;
			break;


		}
		case SYS_CLOCK_FREQ_84_MHZ:
		{
			osc_init.PLL.PLLM = 8;
		    osc_init.PLL.PLLN = 168;
		    osc_init.PLL.PLLP = 2;
		    osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |  RCC_CLOCKTYPE_PCLK1 |  RCC_CLOCKTYPE_PCLK2 ;
			 clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			 clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			 clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			 clk_init.APB2CLKDivider =RCC_HCLK_DIV2;

			 flatency = FLASH_ACR_LATENCY_2WS;

			break;

		}
		case SYS_CLOCK_FREQ_120_MHZ:
		{
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = 2;
			osc_init.PLL.PLLQ = 2;
			osc_init.PLL.PLLR = 2;

			clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |  RCC_CLOCKTYPE_PCLK1 |  RCC_CLOCKTYPE_PCLK2 ;
			clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		    clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			clk_init.APB2CLKDivider =RCC_HCLK_DIV2;

			flatency = FLASH_ACR_LATENCY_3WS;

			break;

		}
		case SYS_CLOCK_FREQ_180_MHZ:
			{

				// enable the clock for the power controller

			    __HAL_RCC_PWR_CLK_ENABLE();

			    //set voltage scale as 1
			    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

			    //set over drive mode
			    __HAL_PWR_OVERDRIVE_ENABLE();

				osc_init.PLL.PLLM = 8;
				osc_init.PLL.PLLN = 360;
				osc_init.PLL.PLLP = 2;
				osc_init.PLL.PLLQ = 2;
				osc_init.PLL.PLLR = 2;

				clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |  RCC_CLOCKTYPE_PCLK1 |  RCC_CLOCKTYPE_PCLK2 ;
				clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
			    clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
				clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
				clk_init.APB2CLKDivider =RCC_HCLK_DIV2;

				flatency = FLASH_ACR_LATENCY_5WS;

				break;

			}
		default:
			return;
		}

		if(HAL_RCC_OscConfig(&osc_init) != HAL_OK )
		{
			Error_Handler();
		}
        if(HAL_RCC_ClockConfig(&clk_init, flatency)!= HAL_OK)
		{
			Error_Handler();
		}

        // Need to always do the systic config to generate the interrupts for the clocks

        HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
        HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}
void Timer6_Init(void)
{
	//to generate an interrupt every 2 seconds

	htimer6.Instance = TIM6;
	htimer6.Init.Prescaler = 2499;
    htimer6.Init.Period = 40000-1;
	//htimer6.Init.Period = 1000-1;
    if (HAL_TIM_Base_Init(&htimer6) != HAL_OK)
    {
    	Error_Handler();
    }
}

void Timer7_Init(void)
{
	//to generate an interrupt every 3.5 seconds

	htimer7.Instance = TIM7;
	htimer7.Init.Prescaler = 3499;
	htimer7.Init.Period = 50000-1;
	//htimer7.Init.Period = 1400-1;
	    if (HAL_TIM_Base_Init(&htimer7) != HAL_OK)
	    {
	    	Error_Handler();
	    }

}
void Timer3_Init(void)
{
	//to generate an interrupt every 7 seconds

	htimer3.Instance = TIM3 ;
	htimer3.Init.Prescaler = 6499;
	//htimer3.Init.Period = 41250-1;
	htimer3.Init.Period = 53846-1;
	    if (HAL_TIM_Base_Init(&htimer3) != HAL_OK)
	    {
	    	Error_Handler();
	    }
}

void Timer4_Init(void)
{
	//to generate an interrupt every 8 seconds

  htimer4.Instance = TIM4 ;
  htimer4.Init.Prescaler = 6499;
  //htimer4.Init.Period = 44000-1;
  htimer4.Init.Period = 61538-1;
		if (HAL_TIM_Base_Init(&htimer4) != HAL_OK)
		 {
		    	Error_Handler();
		 }
}


void CAN_Filter_Config(void)
{
	CAN_FilterTypeDef can1_filter_init;

	can1_filter_init.FilterActivation = ENABLE;
	can1_filter_init.FilterBank = 0;
	can1_filter_init.FilterFIFOAssignment = CAN_RX_FIFO0;
	can1_filter_init.FilterIdHigh = 0x0000;
	can1_filter_init.FilterIdLow = 0x0000;
	can1_filter_init.FilterMaskIdHigh = 0x0000;
	can1_filter_init.FilterMaskIdLow = 0x0000;
	can1_filter_init.FilterMode = CAN_FILTERMODE_IDMASK;
	can1_filter_init.FilterScale = CAN_FILTERSCALE_32BIT;

	if (HAL_CAN_ConfigFilter(&hcan1, &can1_filter_init) != HAL_OK)
	{
		Error_Handler();
	}
}
void CAN1_Init(void)
{

	hcan1.Instance = CAN1;
	hcan1.Init.Mode= CAN_MODE_NORMAL;
	hcan1.Init.AutoBusOff = DISABLE;
	hcan1.Init.AutoRetransmission = ENABLE;
	hcan1.Init.AutoWakeUp = DISABLE;
	hcan1.Init.ReceiveFifoLocked = DISABLE;
	hcan1.Init.TimeTriggeredMode = ENABLE;
	hcan1.Init.TransmitFifoPriority = DISABLE;

	//settings forCAN bit timings
	hcan1.Init.Prescaler= 5;
	hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan1.Init.TimeSeg1 = CAN_BS1_8TQ;
	hcan1.Init.TimeSeg2 = CAN_BS1_1TQ;


	if (HAL_CAN_Init(&hcan1)!= HAL_OK)
	{ Error_Handler();

	}

}
void GPIO_Init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitTypeDef ledgpio;
	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA, &ledgpio);

	ledgpio.Pin = GPIO_PIN_9 | GPIO_PIN_8| GPIO_PIN_6 | GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &ledgpio);

	ledgpio.Pin = GPIO_PIN_8 |GPIO_PIN_9;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &ledgpio);

}


void CAN1_Tx(uint32_t Stdid, uint8_t data_no)
{
	CAN_TxHeaderTypeDef TxHeader;
    uint8_t can_msg[1];
	can_msg[0]= data_no;
	TxHeader.DLC= 1;
	TxHeader.StdId=Stdid;

	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;

		 if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader,can_msg,&TxMailbox1)!= HAL_OK)
			{
			 Error_Handler();
			}

}

void CAN1_Rx(void)
{
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t rcvd_msg[10];

	while (!HAL_CAN_GetRxFifoFillLevel(&hcan1,CAN_RX_FIFO0));

	if (HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&RxHeader,rcvd_msg)!= HAL_OK)
		{
		Error_Handler();
		}


}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	  uint8_t rcvd_msg1[8];

	if (HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&RxHeader1,rcvd_msg1)!= HAL_OK)
					{
					 Error_Handler();
					}

    if (RxHeader1.StdId==0x13)
          	   {
    	        memset(msg,0,sizeof(msg));
    			sprintf(msg, " 0x13 received \r\n");
    			HAL_UART_Transmit(&huart2, (uint8_t*)&msg, strlen(msg),HAL_MAX_DELAY);
          	   }
    if (RxHeader1.StdId==0x14)
             	   {
       	        memset(msg,0,sizeof(msg));
       			sprintf(msg, "0x14 received\r\n");
       			HAL_UART_Transmit(&huart2, (uint8_t*)&msg, strlen(msg),HAL_MAX_DELAY);
             	   }


}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

if (htim->Instance==TIM6)
{
	 while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=3){}
	 CAN1_Tx(0x1,1);
     CAN1_Tx(0x2,2);
	 CAN1_Tx(0x3,3);
}

    if (htim->Instance==TIM7)
    {
    	 while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=3){}
    	 CAN1_Tx(0x4,4);
         CAN1_Tx(0x5,5);
    	 CAN1_Tx(0x6,6);


     }

    if (htim->Instance==TIM3)
        {
    	     while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=3){}
        	 CAN1_Tx(0x7,7);
        	 //while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=2){}
        	 CAN1_Tx(0x8,8);
        	// while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=1){}
        	 CAN1_Tx(0x9,9);
         }

    if (htim->Instance==TIM4)
       {
    	     while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=3){}
        	 CAN1_Tx(0x10,10);
        	 //while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=2){}
        	 CAN1_Tx(0x11,11);
        	 //while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=1){}
        	 CAN1_Tx(0x12,12);
         }
    while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1)!=3){}
 }

/*void GLOW_Corresponding_LED(int8_t ledno)
{
	switch (ledno)
	{
	case 1 :
		HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED2_PORT,LED_2PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED3_PORT,LED3_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED4_PORT,LED4_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED5_PORT,LED5_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED6_PORT,LED6_PIN,GPIO_PIN_RESET);
	    break;
	case 2 :
		HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_PORT,LED_2PIN,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED3_PORT,LED3_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED4_PORT,LED4_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED5_PORT,LED5_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED6_PORT,LED6_PIN,GPIO_PIN_RESET);
        break;

	case 3 :
		HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_PORT,LED_2PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED3_PORT,LED3_PIN,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED4_PORT,LED4_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED5_PORT,LED5_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED6_PORT,LED6_PIN,GPIO_PIN_RESET);
		break;

	case 4 :
		HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_PORT,LED_2PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED3_PORT,LED3_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED4_PORT,LED4_PIN,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED5_PORT,LED5_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED6_PORT,LED6_PIN,GPIO_PIN_RESET);
		break;

	case 5 :
		HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_PORT,LED_2PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED3_PORT,LED3_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED4_PORT,LED4_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED5_PORT,LED5_PIN,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED6_PORT,LED6_PIN,GPIO_PIN_RESET);
		break;

	case 6 :
		HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_PORT,LED_2PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED3_PORT,LED3_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED4_PORT,LED4_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED5_PORT,LED5_PIN,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED6_PORT,LED6_PIN,GPIO_PIN_SET);
		break;

	default :
		return;
    }
}*/


void Error_Handler(void)
	{
	BSP_LED_On(LED2);
	}



/*void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
	memset(msg,0,sizeof(msg));
	sprintf(msg, "Mailbox0 sent\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t*)&msg, strlen(msg),HAL_MAX_DELAY);
}
void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan)
{
	memset(msg,0,sizeof(msg));
		sprintf(msg, "Mailbox1 sent\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*)&msg, strlen(msg),HAL_MAX_DELAY);
}
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan)
{
	memset(msg,0,sizeof(msg));
		sprintf(msg, "Mailbox2 sent \r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*)&msg, strlen(msg),HAL_MAX_DELAY);
}


void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan)
{
	    memset(msg,0,sizeof(msg));
		sprintf(msg, "Node 1 : Transmission has an error\r\n");
		HAL_UART_Transmit(&huart2, (uint8_t*)&msg, strlen(msg),HAL_MAX_DELAY);
}
*/


