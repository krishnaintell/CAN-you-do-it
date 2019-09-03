/*
 * main.h
 *
 *  Created on: 02-May-2019
 *      Author: krishna
 */

#include "stm32f4xx_hal.h"
#include "stm32f4xx_nucleo.h"
#ifndef MAIN_H_
#define MAIN_H_

#define SYS_CLOCK_FREQ_50_MHZ  50
#define SYS_CLOCK_FREQ_84_MHZ  84
#define SYS_CLOCK_FREQ_120_MHZ  120
#define SYS_CLOCK_FREQ_180_MHZ  180

#define LED1_PORT GPIOB
#define LED2_PORT GPIOC
#define LED3_PORT GPIOC
#define LED4_PORT GPIOB
#define LED5_PORT GPIOC
#define LED6_PORT GPIOC

#define LED1_PIN GPIO_PIN_9
#define LED_2PIN GPIO_PIN_9
#define LED3_PIN GPIO_PIN_8
#define LED4_PIN GPIO_PIN_8
#define LED5_PIN GPIO_PIN_6
#define LED6_PIN GPIO_PIN_5

#endif /* MAIN_H_ */



