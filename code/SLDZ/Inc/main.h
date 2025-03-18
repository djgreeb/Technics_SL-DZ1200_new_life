/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2024 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define ENC_A_Pin GPIO_PIN_2
#define ENC_A_GPIO_Port GPIOE
#define ENC_A_EXTI_IRQn EXTI2_IRQn
#define ENC_B_Pin GPIO_PIN_3
#define ENC_B_GPIO_Port GPIOE
#define DATA_LED_Pin GPIO_PIN_4
#define DATA_LED_GPIO_Port GPIOE
#define CLK_LED_Pin GPIO_PIN_5
#define CLK_LED_GPIO_Port GPIOE
#define SW_CDSD_Pin GPIO_PIN_14
#define SW_CDSD_GPIO_Port GPIOC
#define SW_REV_Pin GPIO_PIN_15
#define SW_REV_GPIO_Port GPIOC
#define SPI5_CS_Pin GPIO_PIN_8
#define SPI5_CS_GPIO_Port GPIOF
#define TIMCODE_A_Pin GPIO_PIN_0
#define TIMCODE_A_GPIO_Port GPIOB
#define TIMCODE_A_EXTI_IRQn EXTI0_IRQn
#define CS0_Pin GPIO_PIN_12
#define CS0_GPIO_Port GPIOB
#define CS1_Pin GPIO_PIN_13
#define CS1_GPIO_Port GPIOB
#define DC_Pin GPIO_PIN_14
#define DC_GPIO_Port GPIOB
#define RST_Pin GPIO_PIN_11
#define RST_GPIO_Port GPIOD
#define TIMCODE_B_Pin GPIO_PIN_13
#define TIMCODE_B_GPIO_Port GPIOD
#define SW_TTCD_Pin GPIO_PIN_6
#define SW_TTCD_GPIO_Port GPIOG
#define TT_ON_Pin GPIO_PIN_8
#define TT_ON_GPIO_Port GPIOA
#define TT_REV_Pin GPIO_PIN_11
#define TT_REV_GPIO_Port GPIOA
#define FREE_Pin GPIO_PIN_12
#define FREE_GPIO_Port GPIOA
#define MUTE_Pin GPIO_PIN_10
#define MUTE_GPIO_Port GPIOG
#define DOOR_Pin GPIO_PIN_12
#define DOOR_GPIO_Port GPIOG
#define FLED_Pin GPIO_PIN_8
#define FLED_GPIO_Port GPIOB
#define SD_EN_Pin GPIO_PIN_9
#define SD_EN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
