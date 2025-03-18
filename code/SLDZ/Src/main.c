/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "i2s.h"
#include "sdio.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* USER CODE BEGIN Includes */
#include <math.h>
#include "arm_math.h"
#include "stm32f4xx_ll_fmc.h"
#include "core_cm4.h"
#include <string.h>
/* Display part---------------------------------------------------------*/
#include "fonts.h"
#include "oled.h"



////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//		Generated with: STM32CubeMX 4.22.0
//		Firmware Package Name and Version STM32Cube FW_F4 V1.16.0
//
//
//	arm_math.h add #define ARM_MATH_CM4	in 290 line
//	replace file fmc.c from copy __fmc.c
//	file stm32f4xx_it.c: delete - void SPI3_IRQHandler(void)
//	replace file stm32f4xx_hal_spi.c from copy __stm32f4xx_hal_spi.c
//	replace file tim.c (or add to TIM8)
//				if (HAL_TIM_OnePulse_Init(&htim8, TIM_OPMODE_SINGLE) != HAL_OK)
//				{
//					_Error_Handler(__FILE__, __LINE__);
//				}
//	
//
//
//
//
//	TIM1 3333Hz control platter timer (333Hz)
//	TIM2 platter counter
//	TIM3 PWM round display
//	TIM4 strobe 80.0Hz 20%
//	TIM7 2730Hz interrupt
//	TIM8 500KHz 96(95) repetition counter
//	SPI1 WS LEDs
//	SPI2 OLED displays
//	SPI5 DAC init
//
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//	ver. 0.10
//		- 64MB SDRAM
//		- 2 OLED displays
// 		- added scratch track
//	ver. 0.21
//		- project ported to new pcb
//		- configured to work with the new DAC and SPDIF transmitter
//		- most peripherals initialized
//	ver. 0.23
//		- most peripherals initialized
//	ver. 0.25
//		- TIM8 bug fixed. Missing a line: HAL_TIM_OnePulse_Init(&htim8, TIM_OPMODE_SINGLE) != HAL_OK)
//	ver. 0.26
//		- minor fixes
//	ver. 0.27
//		- split into separate *.h files
//		- oled driver optimization
//	ver. 0.31
//		- added uart
//		- added rgb leds function
//		- added HD74HC164P LEDs
//		- oled driver optimization
//		- unused libraries cleaned up
//	ver. 0.32
//		- added adc process
//		- TIM1 change config 333Hz->10KHz
//	ver. 0.33
//		- changed OLDEs configuration
//		- added uart commands
//		- LEDS_LOAD prc for HD74HC164P moved to audio handler 
//	ver. 0.34
//		- TIM1 change config 10KHz->3333Hz
//		- added buttons prc
//	ver. 0.35
//		- minor fixes
//	ver. 0.36
//		- change motor GPIO initial state
//	ver. 0.37
//		- minor fixes
//	ver. 0.38
//		- add WFORMDYNAMIC reading prc
//	ver. 0.41
//		- minor fixes
//	ver. 0.42
//		- added rekordbox parser
//	ver. 0.43
//		-	add blinking pads
//	ver. 0.44
//		- minor fixes
//	ver. 0.47
//		-	added test sdram
//		-	added uart status messages
//	ver. 0.49
//		-	added support use_lfn in fatfs
//		- minor fixes
//	ver. 0.51
//		- improved SDRAM test
//		-	added fw version register to main.c
//	ver. 0.53
//		- minor fixes
//		-	changed the size of the heap and stack by 2X. Now Stack_Size 0x1000; Heap_Size 0x800;
//	ver. 0.57
//		-	improved OLED library
//		- rekordbox parser optimized
//	ver. 0.61
//		-	improved OLED library
//		-	improved track loading process
//	ver. 0.63
//		-	added optimization waveforms with color coefficient
//	ver. 0.67
//		- rekordbox parser improved
//	ver. 0.68
//		-	fixed drawing of static waveform
//	ver. 0.69
//		- minor fixes
//	ver. 0.70
//		- CDJ900 font added
//		- minor fixes
//		- added pitch calculation
//	ver. 0.71
//		- added gui_generation.h
//	ver. 0.74
//		- minor fixes
//	ver. 0.77
//		-	improved DrawMinuteMarkers()
//		- added ShowTempo()
//	ver. 0.81
//		- removed initialization of SDRAM area from the scatter file, which significantly speeded up system startup
//		-	added mini sdram test
//		- added ShowBPM()
//	ver. 0.85
//		- changed SDRAM parameter SdramTiming.WriteRecoveryTime = 4;			//2	//4 
//		- changed adc pitch aproximation
//		- added adc pitch hysteresis 
//		- added DDM speed regulation
//		- changed audio resampling coeff: optimal 32x, 4-point, 3rd-order optimal
//		- improved and optimized audio resampling algorithm
//	ver. 0.87
//		- regenerated code in CubeMX
//		- added encoder and timecode handlers
//	ver. 0.89
//		-	added timecode encoder in code handler
//	ver. 0.90
//		- minor fixes
//	ver. 0.92
//		- fixed oled ram select
//	ver. 0.93
//		-	added ROOT DISPLAY
//	ver. 0.97
//		- improved BORWSER functions
//	ver. 0.98
//		-	added SD cars remove-insert handler
//	ver. 0.99 
//		-	improved OLED_Putc function for outputting cut characters
//	ver. 1.00 
//		- fixed gui bug
//	ver. 1.03 
//		- fixed gui bug (increased size Stack_Size 0x1000, Heap_Size 0x800)
//		- improved waveform code
//	ver. 1.05
//		-	FontCDJ900 minor fixes
//		-	improved gui
//		-	added SD card symbol 
//	ver. 1.07
//		-	added beatjump with calculate jump distantion
//		-	added hot cues a, b, c
//	ver. 1.11
//		-	improved gui 
//		-	add browser animation
//		-	add 8 HOT CUES and PADS color from *.EXT file
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////



/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
extern uint8_t OLED_RAM_SELECT;
#include "global_variables.h"
extern uint8_t OLED_BUF[2][1024];				//0-HIGH DISPLAY (BROWSE) 1-LOW DISPLAY (WAVEFORM)
#include "gui_generation.h"
#include "rekordbox.h"

static char FW_VERSION[4] = "1.11";	

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void GET_SD_INFO(void);								//check used and free memory on sd card
void COLOR_SET(uint32_t color, uint8_t LD);			//	set color buffer for rgb leds	
void ADC_SELECT_CH(uint32_t ch);				//		select channel for ADC	
void BLINK_INTERFACE(uint8_t pd);				//blinking pads and round display - reaction
void CLEAR_DB_VARIABLES(void);


/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#include "audio_handler.h"
#include "dac.h"



/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SDIO_SD_Init();
  MX_FATFS_Init();
  MX_FMC_Init();
  MX_I2S3_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_SPI5_Init();
  MX_SPI1_Init();
  MX_TIM4_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_TIM7_Init();

  /* USER CODE BEGIN 2 */
	MOTOR_FREE_ON;
	USART1->CR1 |= USART_CR1_RXNEIE; //interrupt for a RX enable
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
	#if defined(USART_STATUS_SENDER)		
	sprintf((char*)U_TX_DATA, "%s", "Start system\n\r");	
	HAL_UART_Transmit(&huart1, U_TX_DATA, 14, 5);	
	sprintf((char*)U_TX_DATA, "%s", "FW ver. ");	
	HAL_UART_Transmit(&huart1, U_TX_DATA, 8, 5);	
	HAL_UART_Transmit(&huart1, FW_VERSION, 4, 5);	
	sprintf((char*)U_TX_DATA, "%s", "\n\r");	
	HAL_UART_Transmit(&huart1, U_TX_DATA, 2, 5);	
	#endif	

	OLED_CS0;	
	HAL_Delay(1);
	OLED_00_Init();
	OLED_Set_Contrast(0);
	OLED_CS1;	
	HAL_Delay(1);
	OLED_01_Init();
	OLED_Set_Contrast(0);
	
	OLED_CS0;	
	OLED_RAM_SELECT = OLED_BROWSE;
	COPY_LOGO(0);							//DRAW STARTUP
	OLED_UpdateScreen();	
	OLED_CS1;	
	OLED_RAM_SELECT = OLED_WFM;
	COPY_LOGO(1);							//DRAW STARTUP
	OLED_UpdateScreen();		
	HAL_I2S_Transmit_IT(&hi2s3, PCM_2, 2);				//start audio process	
	#if defined(USART_STATUS_SENDER)		
	sprintf((char*)U_TX_DATA, "Start audio process\n\r");	
	HAL_UART_Transmit(&huart1, U_TX_DATA, 21, 5);	
	#endif	

	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	TIM3->CCR1 = 0;					//round PWM
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);		//PWM ROUND
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);		//PWM STROBE
	
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);		//start PWM for DDM	
	HAL_TIM_Base_Start_IT(&htim7);							//start timer+interrupt for DDM
	MOTOR_FREE_OFF;
	
	DAC_INIT();
	HAL_GPIO_WritePin(MUTE_GPIO_Port, MUTE_Pin, GPIO_PIN_SET);			//unmute
	#if defined(USART_STATUS_SENDER)		
	sprintf((char*)U_TX_DATA, "DAC init\n\r");	
	HAL_UART_Transmit(&huart1, U_TX_DATA, 10, 5);	
	#endif	
	
	LEDS_LOAD_CNT = 0;
	for(N=0;N<224;N++)
		{
		N+=N;	
		if(N>223)
			{
			N = 223;	
			}		
		OLED_CS1;
		HAL_Delay(20);	
		OLED_Set_Contrast(N);
		OLED_CS0;
		HAL_Delay(20);	
		OLED_Set_Contrast(N);			
		}
	COLOR_SET(PADS_COLOR[5], 0);
	COLOR_SET(PADS_COLOR[5], 1);
	COLOR_SET(PADS_COLOR[5], 2);
	COLOR_SET(PADS_COLOR[5], 3);
	COLOR_SET(PADS_COLOR[5], 4);
	COLOR_SET(PADS_COLOR[5], 5);
	COLOR_SET(PADS_COLOR[5], 6);
	COLOR_SET(PADS_COLOR[5], 7);	
	HAL_SPI_Transmit_DMA(&hspi1, PAD_BUF, 100);		
	
	////////////////////////////mini SDRAM test
	#if defined(USART_STATUS_SENDER)		
	sprintf((char*)U_TX_DATA, "Mini SDRAM test\n\r");	
	HAL_UART_Transmit(&huart1, U_TX_DATA, 17, 5);	
	#endif	
	N = 0;	
	for(y=0;y<2046;y++)
		{
		PCM[y][993][0] = 0xFFAA;	
		}		
	for(y=0;y<2046;y++)
		{
		if(PCM[y][993][0] != 0xFFAA)	
			{	
			N++;
			}
		}	
	for(y=0;y<2046;y++)
		{
		PCM[y][7993][0] = 0xAA55;	
		}		
	for(y=0;y<2046;y++)
		{
		if(PCM[y][7993][0] != 0xAA55)	
			{	
			N++;
			}
		}	
	for(y=0;y<2046;y++)
		{
		PCM[y][3][1] = 0x0000;	
		}		
	for(y=0;y<2046;y++)
		{
		if(PCM[y][3][1] != 0x0000)	
			{	
			N++;
			}
		}	
	#if defined(USART_STATUS_SENDER)		
	sprintf((char*)U_TX_DATA, "%05lu errors\n\r", N);	
	HAL_UART_Transmit(&huart1, U_TX_DATA, 14, 25);		
	#endif			
	//#include "sdram_test.h"
	CLEAR_DB_VARIABLES();	
	OLED_CS1;	
	OLED_RAM_SELECT = OLED_WFM;	
	OLED_DrawFilledRectangle(0, 0, 128, 64, OLED_BLACK);
	OLED_DrawLine(63, 0, 63, 24, OLED_WHITE);	
	OLED_DrawLine(64, 0, 64, 24, OLED_WHITE);		
	sprintf((char*)Buf, "0:00.00");
	OLED_GotoXY(41, 30);
	OLED_Puts(Buf, &Font_7x10, OLED_WHITE);
	Buf[0] = 0x25; //% symbol	
	Buf[1] = 0;	
	OLED_GotoXY(123, 35);
	OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);	
	ShowTrackNumber(0);	
	DrawNewEmpty_TIMESCROLL();
	OLED_DrawLine(0, 27, 0, 38, OLED_WHITE);				///////////////////////
	OLED_DrawLine(17, 27, 17, 38, OLED_WHITE);			//	Track shield
	OLED_DrawLine(1, 26, 16, 26, OLED_WHITE);				//
	OLED_DrawLine(1, 39, 16, 39, OLED_WHITE);				///////////////////////
	OLED_UpdateScreen();	
	HAL_Delay(100);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 while (1)
  {
	if(SD_STATUS==SD_MOUNTED)				//////////////////////////////////////////////////////////////////////
		{
		wfmpos = play_adr/(294*wfmzoom);			
		if(previous_wfmpos != wfmpos)
			{
			OLED_RAM_SELECT = OLED_WFM;	
			previous_wfmpos = wfmpos;
			if(wfmzoom==1)
				{	
				wf_ofs = 0;
				}	
			else if(wfmzoom==2)
				{	
				wf_ofs = wfmx2;
				}
			else if(wfmzoom==4)
				{	
				wf_ofs = wfmx4;
				}
			else if(wfmzoom==8)
				{	
				wf_ofs = wfmx8;
				}
			else if(wfmzoom==16)
				{	
				wf_ofs = wfmx16;
				}
			else if(wfmzoom==32)
				{	
				wf_ofs = wfmx32;
				}
			a_div_v = (all_long/wfmzoom)+63;
			for(N=0;N<128;N++)
				{
				wpos = wfmpos+N;	
				if((wpos>=64) && (wpos<a_div_v))	
					{
					y = WFORMDYNAMIC[wf_ofs+wpos/2-32];	
					if(wpos%2==0)
						{
						y>>=4;		
						}						
					else
						{
						y&=0x0F;	
						}		
					if(N==63 || N==64)
						{
						if(y<11)
							{
							OLED_DrawLine(N, 0, N, 10-y, OLED_WHITE);	
							OLED_DrawLine(N, 12+y, N, 22, OLED_WHITE);	
							}				
						OLED_DrawLine(N, 11-y, N, 11+y, OLED_BLACK);	
						}				
					else
						{
						if(y<11)
							{	
							OLED_DrawLine(N, 0, N, 10-y, OLED_BLACK);	
							OLED_DrawLine(N, 12+y, N, 22, OLED_BLACK);	
							}
						OLED_DrawLine(N, 11-y, N, 11+y, OLED_WHITE);						
						}						
					}
				else			//pre start or end waveform	
					{
					if(N==63 || N==64)
						{
						OLED_DrawLine(N, 0, N, 22, OLED_WHITE);		
						}
					else
						{
						OLED_DrawLine(N, 0, N, 22, OLED_BLACK);	
						}					
					}	
				}	
			need_update_oled1|=0x1F;			//(0...4 = 5 lines)
			}	

		timepos = play_adr/588;			
		if(previous_timepos!= timepos)
			{
			OLED_RAM_SELECT = OLED_WFM;	
			previous_timepos = timepos;
			sprintf((char*)Buf, "%1lu:%02lu.%02lu", (play_adr/2646000)%10, (play_adr/44100)%60, (play_adr/588)%75);
			OLED_GotoXY(41, 30);
			OLED_Puts(Buf, &Font_7x10, OLED_WHITE);
			need_update_oled1|=0x18;			//(3...4)	
			REDRAW_TIMESCROLL((62*(play_adr/147))/all_long);	
			}
			
		if((4096*end_adr_valid_data)<(147*all_long))
			{
			res = f_read(&file, PCM[end_adr_valid_data][0], 32768, &nbytes);
			if(res==FR_OK)
				{
				RAMSCROLL((1727*end_adr_valid_data)/all_long);	
				end_adr_valid_data++;			
				}
			}	
						
		if(need_load_track)
			{				
			COLOR_SET(0, 0);
			COLOR_SET(0, 1);
			COLOR_SET(0, 2);
			COLOR_SET(0, 3);
			COLOR_SET(0, 4);
			COLOR_SET(0, 5);
			COLOR_SET(0, 6);
			COLOR_SET(0, 7);					
			HAL_SPI_Transmit_DMA(&hspi1, PAD_BUF, 100);
			HAL_Delay(100);
			PREPARE_LOAD_TRACK(track_play_now, TRACK_PLAY_IN_CURRENT_PLAYLIST);
			if(PADS_MODE==PADS_HCUE_REC)
				{
				PADS_MODE = PADS_HCUE;	
				}				
			previous_PADS_MODE = 0xFF; 		//forceble reload rgb leds	
			need_load_track = 0;		
			}
			
		if(HAL_GPIO_ReadPin(GPIOC, SW_CDSD_Pin)==1)
			{
			MOTOR_OFF;		
			}	
		else
			{
			MOTOR_ON;		
			}		
			
		if(HAL_GPIO_ReadPin(GPIOG, DOOR_Pin)==0)			//check sd card door now open
			{
			f_close(&file);	
			f_mount(0, "0", 0);					//unmount filesystem		
			TIM3->CCR1 = 0;		
			HAL_GPIO_WritePin(GPIOB, FLED_Pin, GPIO_PIN_RESET);
			MOTOR_OFF;	
			CLEAR_DB_VARIABLES();			
			OLED_RAM_SELECT = OLED_WFM;	
			OLED_DrawFilledRectangle(0, 0, 128, 25, OLED_BLACK);
			OLED_DrawLine(63, 0, 63, 24, OLED_WHITE);	
			OLED_DrawLine(64, 0, 64, 24, OLED_WHITE);			
			sprintf((char*)Buf, "0:00.00");
			OLED_GotoXY(41, 30);
			OLED_Puts(Buf, &Font_7x10, OLED_WHITE);
			ShowBPM(0xFFFF);	
			ShowTrackNumber(0);
			OLED_DrawFilledRectangle(0, 43, 127, 21, OLED_BLACK);	
			DrawNewEmpty_TIMESCROLL();
			need_update_oled1|=0xFF;			//all	
			COLOR_SET(PADS_COLOR[5], 0);
			COLOR_SET(PADS_COLOR[5], 1);
			COLOR_SET(PADS_COLOR[5], 2);
			COLOR_SET(PADS_COLOR[5], 3);
			COLOR_SET(PADS_COLOR[5], 4);
			COLOR_SET(PADS_COLOR[5], 5);
			COLOR_SET(PADS_COLOR[5], 6);
			COLOR_SET(PADS_COLOR[5], 7);	
			need_load_rgb = 1;
			SD_STATUS = SD_OPEN_DOOR;	
			dSHOW = 0xFF;
			SwitchInformationLayer(ROOT_DSPL);
			}
			
	/////////////////TEMPORARY			
	//	if((HAL_GetTick()-temp_time)>500)
	//		{
	//		sprintf((char*)U_TX_DATA, "%04lu.%04lu.%04lu.%04lu.%04lu", ADC_DATA[0], ADC_DATA[1], ADC_DATA[2], ADC_DATA[3], ADC_DATA[4]);
	//		U_TX_DATA[24] = 13;
	//		U_TX_DATA[25] = 10;	
	//		HAL_UART_Transmit(&huart1, U_TX_DATA, 26, 5);
	//		temp_time = HAL_GetTick();	
	//		}		
		}
	else if(SD_STATUS==SD_OPEN_DOOR)			//////////////////////////////////////////////////////////////////////
		{
		if(HAL_GPIO_ReadPin(GPIOG, DOOR_Pin)==1)			//check sd card door now close
			{
			HAL_GPIO_WritePin(GPIOB, FLED_Pin, GPIO_PIN_SET);
			SD_STATUS = SD_SCAN_RB;	
			}	
		}
	else if(SD_STATUS==SD_SCAN_RB)			//////////////////////////////////////////////////////////////////////
		{
		HAL_Delay(300);	
		BSP_SD_Init();	
		HAL_Delay(200);	
		CLEAR_DB_VARIABLES();
		res = f_mount(&FAT, "0", 1);
		if(res == FR_OK)
			{
			#if defined(USART_STATUS_SENDER)		
			sprintf((char*)U_TX_DATA, "Drive mounted\n\r");	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 15, 5);	
			#endif		
				
			TOTAL_TRACKS = DATABASE_PARSER();

			if(TOTAL_TRACKS==0xFFFE)
				{
				#if defined(USART_STATUS_SENDER)		
				sprintf((char*)U_TX_DATA, "Rekordbox database not found!\n\r");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 31, 5);	
				#endif		
				SD_STATUS = SD_NEED_REPLACE;
				}
			else if(TOTAL_TRACKS==0xFFFF)
				{
				#if defined(USART_STATUS_SENDER)		
				sprintf((char*)U_TX_DATA, "Rekordbox database has more than 512 tracks.\n\r");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 46, 5);	
				#endif	
				SD_STATUS = SD_NEED_REPLACE;	
				}
			else if(TOTAL_TRACKS==0xFFF1)
				{
				#if defined(USART_STATUS_SENDER)		
				sprintf((char*)U_TX_DATA, "Playlists structure error.\n\r");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 28, 5);	
				#endif	
				SD_STATUS = SD_NEED_REPLACE;	
				}	
			else if(TOTAL_TRACKS==0)
				{
				#if defined(USART_STATUS_SENDER)		
				sprintf((char*)U_TX_DATA, "Rekordbox database dont't have a tracks.\n\r");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 42, 5);	
				#endif	
				SD_STATUS = SD_NEED_REPLACE;	
				}	
			else
				{
				#if defined(USART_STATUS_SENDER)		
				sprintf((char*)U_TX_DATA, "Rekordbox database have a %03lu tracks\n\r", TOTAL_TRACKS);	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 38, 5);	
				#endif
				SD_STATUS = SD_MOUNTED;	
				}	
			GET_SD_INFO();	
			dSHOW = 0xFF;	
			SwitchInformationLayer(ROOT_DSPL);	
			}
		else
			{
			#if defined(USART_STATUS_SENDER)		
			sprintf((char*)U_TX_DATA, "Drive not mounted\n\r");	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 19, 5);	
			#endif	
			SD_STATUS = SD_NEED_REPLACE;	
			}					
		}
	else if(SD_STATUS==SD_NEED_REPLACE)			//////////////////////////////////////////////////////////////////////
		{	
		if(HAL_GPIO_ReadPin(GPIOG, DOOR_Pin)==0)			//check sd card door
			{
			HAL_GPIO_WritePin(GPIOB, FLED_Pin, GPIO_PIN_RESET);
			SD_STATUS = SD_OPEN_DOOR;	
			}	
		}
		
	#include "browse_animation.h"
		
	if(tempo_need_update>0)
		{
		if(tempo_need_update==1)
			{
			ShowTempo(potenciometer_tempo);
			//change speed motor
			TIM7->PSC = 164830000/potenciometer_tempo;	
			}	
		if(originalBPM!=0xFFFF)
			{
			ShowBPM(((originalBPM+5)*potenciometer_tempo)/100000);	
			}
		tempo_need_update = 0;
		}	
		
	if(usart_new_data)									////////////////////////usart data handler
		{
		HAL_Delay(5);	
		#if defined(USART_INPUT_CMD_HANDLER)		
		if((U_RX_DATA[0]==108) && (U_RX_DATA[1]==101) && (U_RX_DATA[2]==100))				//led			[led_num][R][G][B]
			{							
			COLOR_SET(0x10000*U_RX_DATA[4]+0x100*U_RX_DATA[5]+U_RX_DATA[6], U_RX_DATA[3]);	
			need_load_rgb = 1;		
			sprintf((char*)U_TX_DATA, "load new color\n\r");	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 16, 5);		
			}
		else if((U_RX_DATA[0]==112) && (U_RX_DATA[1]==108) && (U_RX_DATA[2]==97) && (U_RX_DATA[3]==121))				//play
			{
			play_adr = 0;				//start playing		
			sprintf((char*)U_TX_DATA, "Play 0 address\n\r");	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 16, 5);					
			}
		else if(U_RX_DATA[0]==0x7F)				//OLED display commands
			{
			OLED_CS0;		
			OLED_WRITECOMMAND(U_RX_DATA[1]);
			OLED_WRITECOMMAND(U_RX_DATA[2]);					
			OLED_CS1;		
			OLED_WRITECOMMAND(U_RX_DATA[1]);
			OLED_WRITECOMMAND(U_RX_DATA[2]);				
			sprintf((char*)U_TX_DATA, "Display conf. DONE\n\r");
			HAL_UART_Transmit(&huart1, U_TX_DATA, 20, 5);			
			}
		else if(U_RX_DATA[0]==0xE0)				//load track from RB database
			{		
			sprintf((char*)U_TX_DATA, "Start loading track\n\r");	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 21, 15);		
			_TRACK_NUMBER = U_RX_DATA[1];
			_TRACK_IN_PLAYLIST = U_RX_DATA[2];
			need_load_track = 1;
			}	
		else if((U_RX_DATA[0]==0x6D) && (U_RX_DATA[1]==0x11))				//rekordbox variables reading
			{
			if(U_RX_DATA[2]==0)					//playlist
				{
				for(N=0;N<512;N++)
					{	
					HAL_UART_Transmit(&huart1, &playlist[N][0], 55, 55);
					U_TX_DATA[0] = 13;
					U_TX_DATA[1] = 10;	
					HAL_UART_Transmit(&huart1, U_TX_DATA, 2, 5);
					}	
				}	
			else if(U_RX_DATA[2]==1)					//parcser adress
				{
				for(N=0;N<512;N++)
					{	
					sprintf((char*)U_TX_DATA, "%11lu \n\r", parcser_adress[N]);	
					HAL_UART_Transmit(&huart1, U_TX_DATA, 14, 15);		
					}	
				}		
			else if(U_RX_DATA[2]==2)					//original tempo
				{
				for(N=0;N<512;N++)
					{	
					sprintf((char*)U_TX_DATA, "%3lu.%01lu \n\r", original_tempo[N]/10, original_tempo[N]%10);	
					HAL_UART_Transmit(&huart1, U_TX_DATA, 8, 5);		
					}	
				}			
			else if(U_RX_DATA[2]==3)					//rating
				{
				for(N=0;N<512;N++)
					{	
					sprintf((char*)U_TX_DATA, "RAT %3lu COLOR %3lu\n\r", rating[N]/256, rating[N]%256);	
					HAL_UART_Transmit(&huart1, U_TX_DATA, 19, 5);		
					}	
				}
			else if(U_RX_DATA[2]==4)					//duration
				{
				for(N=0;N<512;N++)
					{	
					sprintf((char*)U_TX_DATA, "%02lu:%02lu \n\r", duration[N]/60, duration[N]%60);	
					HAL_UART_Transmit(&huart1, U_TX_DATA, 8, 5);		
					}	
				}	
			else if(U_RX_DATA[2]==5)					//key_id
				{
				for(N=0;N<512;N++)
					{	
					sprintf((char*)U_TX_DATA, "%5lu \n\r", key_id[N]);	
					HAL_UART_Transmit(&huart1, U_TX_DATA, 8, 5);		
					}	
				}	
			else if(U_RX_DATA[2]==6)					//TRACKLIST NAME
				{
				for(N=0;N<20;N++)
					{	
					HAL_UART_Transmit(&huart1, &TRACKLIST_NAME[N][0], 21, 55);
					U_TX_DATA[0] = 13;
					U_TX_DATA[1] = 10;	
					HAL_UART_Transmit(&huart1, U_TX_DATA, 2, 5);	
					}	
				}	
			}
		else
			{
			sprintf((char*)U_TX_DATA, "%s", "Unsupported command");	
			U_TX_DATA[19] = 13;
			U_TX_DATA[20] = 10;	
			HAL_UART_Transmit(&huart1, U_TX_DATA, 21, 5);						
			}
		#endif				
		usart_new_data = 0;		
		}
	#include "encoder_handler.h"
		
	if(need_update_oled0!=0)
		{
		OLED_CS0;		
		OLED_RAM_SELECT = OLED_BROWSE;		
		if(need_update_oled0&0x01)
			{
			OLED_UpdatePart(0);	
			need_update_oled0&=0xFE;	
			}
		if(need_update_oled0&0x02)
			{
			OLED_UpdatePart(1);	
			need_update_oled0&=0xFD;	
			}	
		if(need_update_oled0&0x04)
			{
			OLED_UpdatePart(2);	
			need_update_oled0&=0xFB;	
			}	
		if(need_update_oled0&0x08)
			{
			OLED_UpdatePart(3);	
			need_update_oled0&=0xF7;	
			}				
		if(need_update_oled0&0x10)
			{
			OLED_UpdatePart(4);	
			need_update_oled0&=0xEF;	
			}			
		if(need_update_oled0&0x20)
			{
			OLED_UpdatePart(5);	
			need_update_oled0&=0xDF;	
			}				
		if(need_update_oled0&0x40)
			{
			OLED_UpdatePart(6);	
			need_update_oled0&=0xBF;	
			}				
		if(need_update_oled0&0x80)
			{
			OLED_UpdatePart(7);	
			need_update_oled0&=0x7F;	
			}		
		}
		
	if(need_update_oled1!=0)
		{	
		OLED_CS1;	
		OLED_RAM_SELECT = OLED_WFM;		
		if(need_update_oled1&0x01)
			{
			OLED_UpdatePart(0);	
			need_update_oled1&=0xFE;	
			}
		if(need_update_oled1&0x02)
			{
			OLED_UpdatePart(1);	
			need_update_oled1&=0xFD;	
			}	
		if(need_update_oled1&0x04)
			{
			OLED_UpdatePart(2);	
			need_update_oled1&=0xFB;	
			}	
		if(need_update_oled1&0x08)
			{
			OLED_UpdatePart(3);	
			need_update_oled1&=0xF7;	
			}				
		if(need_update_oled1&0x10)
			{
			OLED_UpdatePart(4);	
			need_update_oled1&=0xEF;	
			}			
		if(need_update_oled1&0x20)
			{
			OLED_UpdatePart(5);	
			need_update_oled1&=0xDF;	
			}				
		if(need_update_oled1&0x40)
			{
			OLED_UpdatePart(6);	
			need_update_oled1&=0xBF;	
			}				
		if(need_update_oled1&0x80)
			{
			OLED_UpdatePart(7);	
			need_update_oled1&=0x7F;	
			}		
		}		
			
	if(PADS_MODE!=previous_PADS_MODE)
		{
		if(PADS_MODE==PADS_HCUE)
			{	
			for(y=0;y<8;y++)
				{
				if(HCUE_adr[0][y]!=0xFFFF)
					{
					if(HCUE_COLOR[y]!=0xFFFF)	
						{
						COLOR_SET(HCUE_COLOR[y], y);	
						}
					else
						{						
						COLOR_SET(PADS_COLOR[1], y);
						}							
					}				
				else
					{
					COLOR_SET(PADS_COLOR[5], y);		
					}
				}								
			}
		else if(PADS_MODE==PADS_LOOP)
			{
			COLOR_SET(PADS_COLOR[2], 0);
			COLOR_SET(PADS_COLOR[2], 1);
			COLOR_SET(PADS_COLOR[2], 2);
			COLOR_SET(PADS_COLOR[2], 3);
			COLOR_SET(PADS_COLOR[2], 4);
			COLOR_SET(PADS_COLOR[2], 5);
			COLOR_SET(PADS_COLOR[2], 6);
			COLOR_SET(PADS_COLOR[2], 7);				
			}				
		else if(PADS_MODE==PADS_SLIP_LOOP)
			{
			COLOR_SET(PADS_COLOR[3], 0);
			COLOR_SET(PADS_COLOR[3], 1);
			COLOR_SET(PADS_COLOR[3], 2);
			COLOR_SET(PADS_COLOR[3], 3);
			COLOR_SET(PADS_COLOR[3], 4);
			COLOR_SET(PADS_COLOR[3], 5);
			COLOR_SET(PADS_COLOR[4], 6);
			COLOR_SET(PADS_COLOR[4], 7);		
			}			
		else if(PADS_MODE==PADS_BEAT_JUMP)
			{	
			COLOR_SET(PADS_COLOR[0], 0);
			COLOR_SET(PADS_COLOR[0], 1);
			COLOR_SET(PADS_COLOR[2], 2);
			COLOR_SET(PADS_COLOR[2], 3);
			COLOR_SET(PADS_COLOR[2], 4);
			COLOR_SET(PADS_COLOR[2], 5);
			COLOR_SET(PADS_COLOR[0], 6);
			COLOR_SET(PADS_COLOR[0], 7);				
			}	
		else if(PADS_MODE==PADS_HCUE_REC)
			{	
			COLOR_SET(PADS_COLOR[0], 0);
			COLOR_SET(PADS_COLOR[0], 1);
			COLOR_SET(PADS_COLOR[0], 2);
			COLOR_SET(PADS_COLOR[0], 3);
			COLOR_SET(PADS_COLOR[0], 4);
			COLOR_SET(PADS_COLOR[0], 5);
			COLOR_SET(PADS_COLOR[0], 6);
			COLOR_SET(PADS_COLOR[0], 7);					
			}	
		previous_PADS_MODE = PADS_MODE; 	
		need_load_rgb = 1;	
		}	
		
	if(need_load_rgb==1)
		{
		load_rgb_tim = HAL_GetTick();	
		if((load_rgb_tim-load_rgb_prev_tim)>25)			//delay 5ms
			{
			HAL_SPI_Transmit_DMA(&hspi1, PAD_BUF, 100);	
			need_load_rgb = 0;
			load_rgb_prev_tim = load_rgb_tim;	
			}
		}	
			
	if(HAL_GPIO_ReadPin(GPIOC, SW_REV_Pin)==1)		//Switch reverse
		{
		MOTOR_REV_ON;	
		//reverse = 1;	
		}	
	else
		{
		MOTOR_REV_OFF;
		//reverse = 0;	
		}		
		
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;			

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 90;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 4;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
#include "timer_handler.h"
#include "timecode_handler.h"
	
//////////////////////////////////////////////////////////////////////////////
//
//		Encoder handler		
//
//	do not create long-running processes in this interrupt 
//	because the connection with the SD card is interrupted
//		
void EXTI2_IRQHandler(void)
	{
	enc_curr_time = HAL_GetTick();	
	enc_time = enc_curr_time - enc_prev_time;	
	if(((GPIOE->IDR)&0x00000008)==0x00)
		{
		if((enc_time>12 && enc_prev_dir==0) || (enc_time>100 && enc_prev_dir==1))	
			{	
			enc_prev_time = enc_curr_time; 	
			enc_need_down = 1;	
			enc_prev_dir = 0;		
			}	
		}
	else
		{
		if((enc_time>12 && enc_prev_dir==1) || (enc_time>100 && enc_prev_dir==0))	
			{
			enc_prev_time = enc_curr_time; 	
			enc_need_up = 1;	
			enc_prev_dir = 1;		
			}			
		}
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
	}	


/////////////////////////////////////////////////////
//	set color buffer for rgb leds
//	led_num 0...7
//
void COLOR_SET(uint32_t color, uint8_t LD)
	{
	if(LD>7)
		{
		return;	
		}		
	uint8_t j, r, g, b;	
		
	if(LD<4)
		{
		LD+= 4;	
		}
	else
		{
		LD = 7-LD;	
		}
		
	r = (color>>16) & 0x000000FF;	
	g = (color>>8) & 0x000000FF;	
	b = color & 0x000000FF; 
	for(j=0;j<4;j++)
		{
		if((g<<(2*j)&0x80)!=0)
			{
			PAD_BUF[j+(12*LD)] = 0xC0;	
			}
		else
			{
			PAD_BUF[j+(12*LD)] = 0x80;	
			}
		if(((g<<(2*j+1))&0x80)!=0)
			{
			PAD_BUF[j+(12*LD)]|=0x0C;	
			}
		else
			{
			PAD_BUF[j+(12*LD)]|=0x08;	
			}	
		}
	for(j=0;j<4;j++)
		{
		if((r<<(2*j)&0x80)!=0)
			{
			PAD_BUF[j+4+(12*LD)] = 0xC0;	
			}
		else
			{
			PAD_BUF[j+4+(12*LD)] = 0x80;	
			}
		if(((r<<(2*j+1))&0x80)!=0)
			{
			PAD_BUF[j+4+(12*LD)]|=0x0C;	
			}
		else
			{
			PAD_BUF[j+4+(12*LD)]|=0x08;	
			}	
		}	
	for(j=0;j<4;j++)
		{
		if((b<<(2*j)&0x80)!=0)
			{
			PAD_BUF[j+8+(12*LD)] = 0xC0;	
			}
		else
			{
			PAD_BUF[j+8+(12*LD)] = 0x80;	
			}
		if(((b<<(2*j+1))&0x80)!=0)
			{
			PAD_BUF[j+8+(12*LD)]|=0x0C;	
			}
		else
			{
			PAD_BUF[j+8+(12*LD)]|=0x08;	
			}	
		}	
	return;	
	}	
	

void USART1_IRQHandler(void)
	{
	uint8_t USART_RX_B;	
	if(USART1->SR & USART_SR_RXNE)		//have a new data
		{
		USART_RX_B = (USART1->DR);	
		if(((HAL_GetTick() - usart_timeout)>200))
			{	
			if(USART_RX_B==47)
				{
				usart_data_cnt = 0;
				U_RX_DATA[1] = 0;
				U_RX_DATA[2] = 0;
				U_RX_DATA[3] = 0;
				U_RX_DATA[4] = 0;
				U_RX_DATA[5] = 0;
				U_RX_DATA[6] = 0;
				U_RX_DATA[7] = 0;
				U_RX_DATA[8] = 0;
				U_RX_DATA[9] = 0;
				U_RX_DATA[10] = 0;
				U_RX_DATA[11] = 0;
				U_RX_DATA[12] = 0;
				U_RX_DATA[13] = 0;
				U_RX_DATA[14] = 0;
				U_RX_DATA[15] = 0;						
				}
			else
				{
				usart_data_cnt = 0xFF;	
				}
			}
		else
			{
			if(usart_data_cnt<16)	
				{
				U_RX_DATA[usart_data_cnt] = USART_RX_B;			
				usart_data_cnt++;
					
				if(usart_data_cnt>2 && usart_new_data==0)
					{			
					usart_new_data = 1;	
					}
				}
			}
		usart_timeout = HAL_GetTick(); 			
		}
  HAL_UART_IRQHandler(&huart1);
	}		
	
	


//////////////////////////////////////////////////////////////////////////////
//
//		select channel for ADC		
//			
void ADC_SELECT_CH(uint32_t ch)
	{
	ADC_ChannelConfTypeDef sConfig;
	sConfig.Channel = ch;
	sConfig.Rank = 1;
	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	HAL_ADC_ConfigChannel(&hadc1, &sConfig);	
	}

	
//////////////////////////////////////////////////////////////////////////////
//
//		blinking pads and round display - reaction
//		input pad 0..7	- beat jump pad
//	
void BLINK_INTERFACE(uint8_t pd)
	{
	blink_pad = pd;	
	TIM3->CCR1 = 0;		//turn off round	
	COLOR_SET(ACTIVE_PAD_COLOR, pd);	
	need_load_rgb = 1;	
	reblink_tim = 35;	
	return;	
	};	

	
///////////////////////////////////////////////
//get free space and total space	
//		
void GET_SD_INFO(void)
	{
	FATFS *fs;
	DWORD fre_clust;	
	f_getfree("0:", &fre_clust, &fs);
	used_mem = (fs->n_fatent - 2) * fs->csize;
	used_mem = used_mem>>11;
	if(used_mem>99999)
		{
		used_mem = 99999;	
		}	
	free_mem = fre_clust * (fs->csize);
	free_mem = free_mem>>11;		
	if(free_mem>99999)
		{
		free_mem = 99999;	
		}	
	used_mem = used_mem - free_mem;
	return;	
	};		
	
	
	
//////////////////////////////////////////////////////////////////////////////
//
//	clear varibles for rekordbox and fatfs
//		
//		
void CLEAR_DB_VARIABLES(void)
	{
	uint32_t q;	
	pitch = 0;	
	play_enable = 0;	
	play_adr = 0;	
	all_long = 0;		
	end_adr_valid_data = 0xFFFF;	
	for(q=0;q<28160;q++)
		{
		playlist[0][q] = 0;	
		}
	for(q=0;q<512;q++)
		{
		original_tempo[q] = 0xFFFF;	
		rating[q] = 0xFFFF;
		duration[q] = 0xFFFF;
		key_id[q] = 0xFF;
		parcser_adress[q] = 0xFFFFFFFF;	
		TRACKS_DATABASE[2*q] = 0;
		TRACKS_DATABASE[2*q+1] = 0;	
		}		
	for(q=0;q<2048;q++)
		{
		BEATGRID[q] = 0; 
		BPMGRID[q] = 0;
		}	
	TOTAL_TRACKS = 0;	
	TOTAL_TRACKS_IN_CURRENT_PLAYLIST = 0;	
	TRACK_PLAY_IN_CURRENT_PLAYLIST = 0;	
	track_play_now = 0;	
	_TRACK_NUMBER = 0xFFFF;	
	_TRACK_IN_PLAYLIST = 0xFFFF;	
	need_load_track = 0;	
	TOTAL_TRACKLISTS = 0;	
	originalBPM = 0xFFFF;	
	for(q=0;q<20;q++)
		{
		SDCARD_NAME[q] = 0;
		TRACKLIST_OFFSET[q] = 0;		
		}	
	for(q=0;q<15;q++)
		{
		SD_DATE[q] = 0;	
		}		
	for(q=0;q<100;q++)
		{
		KEYS[0][q] = 0;	
		}			
	for(q=0;q<420;q++)
		{
		TRACKLIST_NAME[0][q] = 0;	
		}	
	free_mem = 0;	
	used_mem = 0;	
  ScrollLong = 52;								//4...54
  ScrollPosition = 0;							//0...54-ScrollLong
  B0CurrentCursorPosition = 0;		//0...5 position
  B1CurrentCursorPosition = 0;		//0...5 position
  BCurrentPlaylistPosition = 1;			//1....TOTAL_TRACKLISTS-5
  BCurrentTrackPosition = 1;			//1....TOTAL_TRACKS-5			
	return;	
	}	
	
	
//////////////////////////////////////////////////FatFs Functions//////////////////////
WCHAR ff_convert (WCHAR wch, UINT dir) 
{ 
          if (wch < 0x80) { 
                    /* ASCII Char */ 
                    return wch; 
          }  

          /* I don't support unicode it is too big! */ 
          return 0; 
}  

WCHAR ff_wtoupper (WCHAR wch) 
{ 
          if (wch < 0x80) {      
                    /* ASCII Char */ 
                    if (wch >= 'a' && wch <= 'z') { 
                              wch &= ~0x20; 
                     } 
                      return wch; 
          }  

          /* I don't support unicode it is too big! */ 
          return 0; 
} 
//////////////////////////////////////////////////////////////////////////////////////	

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
