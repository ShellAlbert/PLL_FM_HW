/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SMTR2_DEC0_Pin GPIO_PIN_2
#define SMTR2_DEC0_GPIO_Port GPIOE
#define SMTR2_NSLEEP_Pin GPIO_PIN_3
#define SMTR2_NSLEEP_GPIO_Port GPIOE
#define SMTR2_DEC1_Pin GPIO_PIN_4
#define SMTR2_DEC1_GPIO_Port GPIOE
#define SMTR2_I1_Pin GPIO_PIN_5
#define SMTR2_I1_GPIO_Port GPIOE
#define SMTR2_I0_Pin GPIO_PIN_6
#define SMTR2_I0_GPIO_Port GPIOE
#define SMTR2_ADEC_Pin GPIO_PIN_13
#define SMTR2_ADEC_GPIO_Port GPIOC
#define SMTR2_DIR_Pin GPIO_PIN_14
#define SMTR2_DIR_GPIO_Port GPIOC
#define M2_I_ADC_Pin GPIO_PIN_0
#define M2_I_ADC_GPIO_Port GPIOC
#define M1_I_ADC_Pin GPIO_PIN_1
#define M1_I_ADC_GPIO_Port GPIOC
#define M4_I_ADC_Pin GPIO_PIN_2
#define M4_I_ADC_GPIO_Port GPIOC
#define M3_I_ADC_Pin GPIO_PIN_3
#define M3_I_ADC_GPIO_Port GPIOC
#define ENC1_B_BUF_Pin GPIO_PIN_0
#define ENC1_B_BUF_GPIO_Port GPIOA
#define ENC1_A_BUF_Pin GPIO_PIN_1
#define ENC1_A_BUF_GPIO_Port GPIOA
#define SMTR1_PWM_Pin GPIO_PIN_2
#define SMTR1_PWM_GPIO_Port GPIOA
#define SMTR2_PWM_Pin GPIO_PIN_3
#define SMTR2_PWM_GPIO_Port GPIOA
#define PT100_3_Pin GPIO_PIN_4
#define PT100_3_GPIO_Port GPIOA
#define PT100_2_Pin GPIO_PIN_5
#define PT100_2_GPIO_Port GPIOA
#define PT100_1_Pin GPIO_PIN_6
#define PT100_1_GPIO_Port GPIOA
#define M4_PWM__Pin GPIO_PIN_7
#define M4_PWM__GPIO_Port GPIOA
#define MCU_RST_CPU_Pin GPIO_PIN_4
#define MCU_RST_CPU_GPIO_Port GPIOC
#define VBAT_ADC_Pin GPIO_PIN_5
#define VBAT_ADC_GPIO_Port GPIOC
#define M1_PWM__Pin GPIO_PIN_0
#define M1_PWM__GPIO_Port GPIOB
#define M2_PWM__Pin GPIO_PIN_1
#define M2_PWM__GPIO_Port GPIOB
#define ARM_ONOFF_Pin GPIO_PIN_7
#define ARM_ONOFF_GPIO_Port GPIOE
#define ENC4_A_BUF_Pin GPIO_PIN_9
#define ENC4_A_BUF_GPIO_Port GPIOE
#define NFAULT34_Pin GPIO_PIN_10
#define NFAULT34_GPIO_Port GPIOE
#define ENC4_B_BUF_Pin GPIO_PIN_11
#define ENC4_B_BUF_GPIO_Port GPIOE
#define M3_PWM__Pin GPIO_PIN_12
#define M3_PWM__GPIO_Port GPIOE
#define M3_PWM_E13_Pin GPIO_PIN_13
#define M3_PWM_E13_GPIO_Port GPIOE
#define NSLEEP34_Pin GPIO_PIN_15
#define NSLEEP34_GPIO_Port GPIOE
#define NSLEEP12_Pin GPIO_PIN_10
#define NSLEEP12_GPIO_Port GPIOB
#define NFAULT12_Pin GPIO_PIN_11
#define NFAULT12_GPIO_Port GPIOB
#define MCU_SPI2_NSS_Pin GPIO_PIN_12
#define MCU_SPI2_NSS_GPIO_Port GPIOB
#define MCU_SPI2_SCK_Pin GPIO_PIN_13
#define MCU_SPI2_SCK_GPIO_Port GPIOB
#define MCU_SPI2_MISO_Pin GPIO_PIN_14
#define MCU_SPI2_MISO_GPIO_Port GPIOB
#define MCU_SPI2_MOSI_Pin GPIO_PIN_15
#define MCU_SPI2_MOSI_GPIO_Port GPIOB
#define MCU_UART3_TXD_Pin GPIO_PIN_8
#define MCU_UART3_TXD_GPIO_Port GPIOD
#define MCU_UART3_RXD_Pin GPIO_PIN_9
#define MCU_UART3_RXD_GPIO_Port GPIOD
#define LIMIT_SW1_Pin GPIO_PIN_10
#define LIMIT_SW1_GPIO_Port GPIOD
#define LIMIT_SW2_Pin GPIO_PIN_11
#define LIMIT_SW2_GPIO_Port GPIOD
#define ENC3_B_BUF_Pin GPIO_PIN_12
#define ENC3_B_BUF_GPIO_Port GPIOD
#define ENC3_A_BUF_Pin GPIO_PIN_13
#define ENC3_A_BUF_GPIO_Port GPIOD
#define LIMIT_SW3_Pin GPIO_PIN_14
#define LIMIT_SW3_GPIO_Port GPIOD
#define LIMIT_SW4_Pin GPIO_PIN_15
#define LIMIT_SW4_GPIO_Port GPIOD
#define M4_PWM_C6_Pin GPIO_PIN_6
#define M4_PWM_C6_GPIO_Port GPIOC
#define M1_PWM_C7_Pin GPIO_PIN_7
#define M1_PWM_C7_GPIO_Port GPIOC
#define M2_PWM_C8_Pin GPIO_PIN_8
#define M2_PWM_C8_GPIO_Port GPIOC
#define MCU_RST_FPGA_Pin GPIO_PIN_9
#define MCU_RST_FPGA_GPIO_Port GPIOC
#define MCU_LED2_Pin GPIO_PIN_8
#define MCU_LED2_GPIO_Port GPIOA
#define MCU_LED1_Pin GPIO_PIN_11
#define MCU_LED1_GPIO_Port GPIOA
#define MCU_LED3_Pin GPIO_PIN_15
#define MCU_LED3_GPIO_Port GPIOA
#define MCU_UART4_TXD_Pin GPIO_PIN_10
#define MCU_UART4_TXD_GPIO_Port GPIOC
#define MCU_UART4_RXD_Pin GPIO_PIN_11
#define MCU_UART4_RXD_GPIO_Port GPIOC
#define MCU_LED4_Pin GPIO_PIN_12
#define MCU_LED4_GPIO_Port GPIOC
#define SMTR1_nFAULT_Pin GPIO_PIN_0
#define SMTR1_nFAULT_GPIO_Port GPIOD
#define SMTR1_M0_Pin GPIO_PIN_1
#define SMTR1_M0_GPIO_Port GPIOD
#define SMTR1_M1_Pin GPIO_PIN_2
#define SMTR1_M1_GPIO_Port GPIOD
#define SMTR1_TOFF_SEL_Pin GPIO_PIN_3
#define SMTR1_TOFF_SEL_GPIO_Port GPIOD
#define SMTR1_DIR_Pin GPIO_PIN_4
#define SMTR1_DIR_GPIO_Port GPIOD
#define SMTR1_ADEC_Pin GPIO_PIN_5
#define SMTR1_ADEC_GPIO_Port GPIOD
#define SMTR1_I0_Pin GPIO_PIN_6
#define SMTR1_I0_GPIO_Port GPIOD
#define SMTR1_I1_Pin GPIO_PIN_7
#define SMTR1_I1_GPIO_Port GPIOD
#define SMTR1_DEC0_Pin GPIO_PIN_3
#define SMTR1_DEC0_GPIO_Port GPIOB
#define ENC2_B_BUF_Pin GPIO_PIN_4
#define ENC2_B_BUF_GPIO_Port GPIOB
#define ENC2_A_BUF_Pin GPIO_PIN_5
#define ENC2_A_BUF_GPIO_Port GPIOB
#define SMTR1_NSLEEP_Pin GPIO_PIN_6
#define SMTR1_NSLEEP_GPIO_Port GPIOB
#define SMTR1_DEC1_Pin GPIO_PIN_7
#define SMTR1_DEC1_GPIO_Port GPIOB
#define SMTR2_NFAULT_Pin GPIO_PIN_8
#define SMTR2_NFAULT_GPIO_Port GPIOB
#define SMTR2_M0_Pin GPIO_PIN_9
#define SMTR2_M0_GPIO_Port GPIOB
#define SMTR2_M1_Pin GPIO_PIN_0
#define SMTR2_M1_GPIO_Port GPIOE
#define SMTR2_TOFF_SEL_Pin GPIO_PIN_1
#define SMTR2_TOFF_SEL_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
