/*
 * it.c
 *
 *  Created on: 02-May-2019
 *      Author: krishna
 */

#include "main.h"

extern CAN_HandleTypeDef hcan1;
extern TIM_HandleTypeDef htimer3;
extern TIM_HandleTypeDef htimer4;
extern TIM_HandleTypeDef htimer6;
extern TIM_HandleTypeDef htimer7;

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


void CAN1_TX_IRQHandler (void)
{
	HAL_CAN_IRQHandler(&hcan1);
}

void CAN1_RX0_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&hcan1);
}

void CAN1_RX1_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&hcan1);
}

void CAN1_SCE_IRQHandler(void)
{
	HAL_CAN_IRQHandler(&hcan1);
}

void TIM6_DAC_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer6);
}

void TIM7_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer7);
}

void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer3);
}

void TIM4_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&htimer4);
}


