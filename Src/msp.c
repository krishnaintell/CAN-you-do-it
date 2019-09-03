/*
 * msp.c
 *
 *  Created on: 02-May-2019
 *      Author: krishna
 */

#include "main.h"


 void HAL_MspInit(void)
{
  // 1. Set up the priority grouping for the Arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Set up the Exceptions relevant to the priority grouping
	SCB->SHCSR |= 0x7 <<16;   //we enabled usage fault, memory fault  and bus fault system exceptions

	//3. Configure the priority for the exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0,0);

}

 void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	 GPIO_InitTypeDef gpio_uart;
	 // we are doing low level initialization of the USART2 peripheral

	 //1. enable theclock for USART2

	    __HAL_RCC_USART2_CLK_ENABLE();
	    __HAL_RCC_GPIOA_CLK_ENABLE();

	 //2. Do the pin muxing configs
       gpio_uart.Pin = GPIO_PIN_2;
       gpio_uart.Mode = GPIO_MODE_AF_PP;
       gpio_uart.Pull = GPIO_PULLUP;
       gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
       gpio_uart.Alternate = GPIO_AF7_USART2;

      HAL_GPIO_Init(GPIOA, &gpio_uart);  // all the above was done for Tx

      // now the same for Rx

      gpio_uart.Pin = GPIO_PIN_3;

      HAL_GPIO_Init(GPIOA, &gpio_uart);


       //3. Enable the IRQ and set up the priority(NVIC settings). It is actually optional
      HAL_NVIC_EnableIRQ(USART2_IRQn);
      HAL_NVIC_SetPriority(USART2_IRQn,15,0);


}

 void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
 {
	 GPIO_InitTypeDef GPIO_InitStruct;
	 	 // we are doing low level initialization of the USART2 peripheral

	 	 //1. enable theclock for CAN

	 	    __HAL_RCC_CAN1_CLK_ENABLE();
	 	    __HAL_RCC_GPIOA_CLK_ENABLE();

	 	 //2. Do the pin muxing configs
	 	   GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
	 	   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	 	   GPIO_InitStruct.Pull = GPIO_NOPULL;
	 	   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	 	   GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;

	       HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  // all the above was done for Tx




	        //3. Enable the IRQ and set up the priority(NVIC settings). It is actually optional
	       HAL_NVIC_SetPriority(CAN1_TX_IRQn,15,0);
	       HAL_NVIC_SetPriority(CAN1_RX0_IRQn,14,0);
	       HAL_NVIC_SetPriority(CAN1_RX1_IRQn,15,0);
	       HAL_NVIC_SetPriority(CAN1_SCE_IRQn,15,0);



	    	       HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
	    	       HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
	    	       HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
	    	       HAL_NVIC_EnableIRQ(CAN1_SCE_IRQn);

 }

 void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htimer)

 {
         //1. Enable the clock for timer 3 , timer 4 , timer 6 and timer 7 , the sysclock
	 __HAL_RCC_TIM6_CLK_ENABLE();
	 __HAL_RCC_TIM7_CLK_ENABLE();
	 __HAL_RCC_TIM3_CLK_ENABLE();
	 __HAL_RCC_TIM4_CLK_ENABLE();



		 //2. Enable IRQ of timer 3, timer 4, timer 6 and timer7
	  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
	  HAL_NVIC_EnableIRQ(TIM7_IRQn);
	  HAL_NVIC_EnableIRQ(TIM3_IRQn);
	  HAL_NVIC_EnableIRQ(TIM4_IRQn);



	    //3. setup up the priority for the IRQnum
	    HAL_NVIC_SetPriority(TIM6_DAC_IRQn,12,0);
	    HAL_NVIC_SetPriority(TIM7_IRQn,13,0);
	    HAL_NVIC_SetPriority(TIM3_IRQn,14,0);
	    HAL_NVIC_SetPriority(TIM4_IRQn,15,0);



 }

