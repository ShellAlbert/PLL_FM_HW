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
#define SMTR2_M0_Pin GPIO_PIN_2
#define SMTR2_M0_GPIO_Port GPIOE
#define SMTR2_M1_Pin GPIO_PIN_3
#define SMTR2_M1_GPIO_Port GPIOE
#define SMTR2_TOFF_SEL_Pin GPIO_PIN_4
#define SMTR2_TOFF_SEL_GPIO_Port GPIOE
#define SMTR2_DEC1_Pin GPIO_PIN_5
#define SMTR2_DEC1_GPIO_Port GPIOE
#define SMTR2_nSLEEP_Pin GPIO_PIN_6
#define SMTR2_nSLEEP_GPIO_Port GPIOE
#define SMTR2_DEC0_Pin GPIO_PIN_13
#define SMTR2_DEC0_GPIO_Port GPIOC
#define SMTR2_I1_Pin GPIO_PIN_14
#define SMTR2_I1_GPIO_Port GPIOC
#define SMTR2_I0_Pin GPIO_PIN_15
#define SMTR2_I0_GPIO_Port GPIOC
#define M3_I_ADC_Pin GPIO_PIN_0
#define M3_I_ADC_GPIO_Port GPIOC
#define M2_I_ADC_Pin GPIO_PIN_1
#define M2_I_ADC_GPIO_Port GPIOC
#define M1_I_ADC_Pin GPIO_PIN_2
#define M1_I_ADC_GPIO_Port GPIOC
#define M4_I_ADC_Pin GPIO_PIN_3
#define M4_I_ADC_GPIO_Port GPIOC
#define ENC1_B_BUF_Pin GPIO_PIN_0
#define ENC1_B_BUF_GPIO_Port GPIOA
#define ENC1_A_BUF_Pin GPIO_PIN_1
#define ENC1_A_BUF_GPIO_Port GPIOA
#define MCU_RST_CPU_Pin GPIO_PIN_4
#define MCU_RST_CPU_GPIO_Port GPIOC
#define ARM_ONOFF_Pin GPIO_PIN_7
#define ARM_ONOFF_GPIO_Port GPIOE
#define ENC3_B_BUF_Pin GPIO_PIN_9
#define ENC3_B_BUF_GPIO_Port GPIOE
#define ENC3_A_BUF_Pin GPIO_PIN_11
#define ENC3_A_BUF_GPIO_Port GPIOE
#define SMTR2_nFAULT_Pin GPIO_PIN_15
#define SMTR2_nFAULT_GPIO_Port GPIOE
#define SMTR2_DIR_Pin GPIO_PIN_10
#define SMTR2_DIR_GPIO_Port GPIOB
#define SMTR2_ADEC_Pin GPIO_PIN_11
#define SMTR2_ADEC_GPIO_Port GPIOB
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
#define MCU_LED2_Pin GPIO_PIN_10
#define MCU_LED2_GPIO_Port GPIOD
#define MCU_LED1_Pin GPIO_PIN_11
#define MCU_LED1_GPIO_Port GPIOD
#define ENC4_B_BUF_Pin GPIO_PIN_12
#define ENC4_B_BUF_GPIO_Port GPIOD
#define ENC4_A_BUF_Pin GPIO_PIN_13
#define ENC4_A_BUF_GPIO_Port GPIOD
#define MCU_LED4_Pin GPIO_PIN_14
#define MCU_LED4_GPIO_Port GPIOD
#define MCU_LED3_Pin GPIO_PIN_15
#define MCU_LED3_GPIO_Port GPIOD
#define MCU_RST_FPGA_Pin GPIO_PIN_9
#define MCU_RST_FPGA_GPIO_Port GPIOC
#define nSLEEP12_Pin GPIO_PIN_12
#define nSLEEP12_GPIO_Port GPIOA
#define MCU_UART4_TXD_Pin GPIO_PIN_10
#define MCU_UART4_TXD_GPIO_Port GPIOC
#define MCU_UART4_RXD_Pin GPIO_PIN_11
#define MCU_UART4_RXD_GPIO_Port GPIOC
#define LIMIT_SW1_Pin GPIO_PIN_12
#define LIMIT_SW1_GPIO_Port GPIOC
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
#define nFAULT12_Pin GPIO_PIN_6
#define nFAULT12_GPIO_Port GPIOD
#define nSLEEP34_Pin GPIO_PIN_7
#define nSLEEP34_GPIO_Port GPIOD
#define nFAULT34_Pin GPIO_PIN_3
#define nFAULT34_GPIO_Port GPIOB
#define ENC2_A_BUF_Pin GPIO_PIN_4
#define ENC2_A_BUF_GPIO_Port GPIOB
#define ENC2_B_BUF_Pin GPIO_PIN_5
#define ENC2_B_BUF_GPIO_Port GPIOB
#define SMTR1_I0_Pin GPIO_PIN_7
#define SMTR1_I0_GPIO_Port GPIOB
#define SMTR1_DEC1_Pin GPIO_PIN_8
#define SMTR1_DEC1_GPIO_Port GPIOB
#define SMTR1_nSLEEP_Pin GPIO_PIN_9
#define SMTR1_nSLEEP_GPIO_Port GPIOB
#define SMTR1_DEC0_Pin GPIO_PIN_0
#define SMTR1_DEC0_GPIO_Port GPIOE
#define SMTR1_I1_Pin GPIO_PIN_1
#define SMTR1_I1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
