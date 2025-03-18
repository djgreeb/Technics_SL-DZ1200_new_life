/////////////////////////////////////////////////////////////////////////////////////////////////
// 	timers handler
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "stdint.h"

/////////////////////////////////////////////////////////////////////////
//
//	TIM1 3333Hz control platter timer
//	
void TIM1_UP_TIM10_IRQHandler(void)
	{	
	if(TIM1_DIV<10)
		{
		if(TIM1_DIV==0)
			{
			HAL_ADC_Start(&hadc1);	
			}			
		else if(TIM1_DIV==1)				//pitch
			{
			ADC_TEMP = HAL_ADC_GetValue(&hadc1);
			ADC_TEMP+=3*ADC_DATA[0];
			ADC_DATA[0] = ADC_TEMP>>2;	
			ADC_SELECT_CH(ADC_CH1);

			if(tempo_reset==0)
				{
				if(ADC_DATA[0]>(previous_adc_pitch+HYSTERESIS) || (HYSTERESIS+ADC_DATA[0])<previous_adc_pitch)			//	out of hysteresis
					{																																																	//
					previous_adc_pitch = ADC_DATA[0];																																  //
					if(tempo_range==0)		//8%
						{	
						if(previous_adc_pitch<2048)	//plus
							{
							potenciometer_tempo = (2047-previous_adc_pitch);
							potenciometer_tempo/=12;	
							potenciometer_tempo*=5;	
							if(potenciometer_tempo>800)
								{
								potenciometer_tempo = 800;	
								}								
							potenciometer_tempo+=10000;	
							}
						else					//minus
							{
							potenciometer_tempo = previous_adc_pitch-2048;
							potenciometer_tempo/=12;	
							potenciometer_tempo*=5;	
							if(potenciometer_tempo>800)
								{
								potenciometer_tempo = 800;	
								}		
							potenciometer_tempo = 10000 - potenciometer_tempo;	
							}				
						}
					else if(tempo_range==1)		//16%
						{
						if(previous_adc_pitch<2048)	//plus
							{
							potenciometer_tempo = (2047-previous_adc_pitch);
							potenciometer_tempo/=12;	
							potenciometer_tempo*=10;	
							if(potenciometer_tempo>1600)
								{
								potenciometer_tempo = 1600;	
								}	
							potenciometer_tempo+=10000;	
							}
						else					//minus
							{
							potenciometer_tempo = previous_adc_pitch-2048;
							potenciometer_tempo/=12;	
							potenciometer_tempo*=10;	
							if(potenciometer_tempo>1600)
								{
								potenciometer_tempo = 1600;	
								}		
							potenciometer_tempo = 10000 - potenciometer_tempo;	
							}		
						}
					else if(tempo_range==2)		//33%
						{
						if(previous_adc_pitch<2048)	//plus
							{
							potenciometer_tempo = (2047-previous_adc_pitch);
							potenciometer_tempo/=12;	
							potenciometer_tempo*=20;	
							if(potenciometer_tempo>3300)
								{
								potenciometer_tempo = 3300;	
								}		
							potenciometer_tempo+=10000;	
							}
						else					//minus
							{
							potenciometer_tempo = previous_adc_pitch-2048;
							potenciometer_tempo/=12;	
							potenciometer_tempo*=20;	
							if(potenciometer_tempo>3300)
								{
								potenciometer_tempo = 3300;	
								}		
							potenciometer_tempo = 10000 - potenciometer_tempo;	
							}	
						}
					else		//50%
						{
						if(previous_adc_pitch<2048)	//plus
							{
							potenciometer_tempo = (2047-previous_adc_pitch);
							potenciometer_tempo/=20;	
							potenciometer_tempo*=50;	
							if(potenciometer_tempo>5000)
								{
								potenciometer_tempo = 5000;	
								}		
							potenciometer_tempo+=10000;	
							}
						else					//minus
							{
							potenciometer_tempo = previous_adc_pitch-2048;
							potenciometer_tempo/=20;	
							potenciometer_tempo*=50;	
							if(potenciometer_tempo>5000)
								{
								potenciometer_tempo = 5000;	
								}		
							potenciometer_tempo = 10000 - potenciometer_tempo;	
							}	
						}
					tempo_need_update = 1;	
					}	
				}
			else
				{
				potenciometer_tempo = 10000;						
				}

			if(play_enable)
				{
				//pitch =	potenciometer_tempo;
				}	
			if(previous_potenciometer_tempo != potenciometer_tempo)
				{
				previous_potenciometer_tempo = potenciometer_tempo;	
				tempo_need_update = 1;
				}
			}				
		else if(TIM1_DIV==2)
			{
			HAL_ADC_Start(&hadc1);	
			}			
		else if(TIM1_DIV==3)
			{
			ADC_TEMP = HAL_ADC_GetValue(&hadc1);
			if((ADC_TEMP>ADC_DATA[1])&&((ADC_TEMP-ADC_DATA[1])>FILTER_TH) || (ADC_DATA[1]>ADC_TEMP)&&((ADC_DATA[1]-ADC_TEMP)>FILTER_TH))
				{
				ADC_DATA[1] = ADC_TEMP;	
				}
			else
				{
				ADC_TEMP+=ADC_DATA[1];
				ADC_DATA[1] = ADC_TEMP>>1;						
				}
			ADC_SELECT_CH(ADC_CH2);		
			}		
		else if(TIM1_DIV==4)
			{
			HAL_ADC_Start(&hadc1);	
			}		
		else if(TIM1_DIV==5)
			{
			ADC_TEMP = HAL_ADC_GetValue(&hadc1);
			if((ADC_TEMP>ADC_DATA[2])&&((ADC_TEMP-ADC_DATA[2])>FILTER_TH) || (ADC_DATA[2]>ADC_TEMP)&&((ADC_DATA[2]-ADC_TEMP)>FILTER_TH))
				{
				ADC_DATA[2] = ADC_TEMP;
				}
			else
				{	
				ADC_TEMP+=ADC_DATA[2];
				ADC_DATA[2] = ADC_TEMP>>1;
				}
			ADC_SELECT_CH(ADC_CH3);		
			}		
		else if(TIM1_DIV==6)
			{
			HAL_ADC_Start(&hadc1);	
			}		
		else if(TIM1_DIV==7)
			{
			ADC_TEMP = HAL_ADC_GetValue(&hadc1);
			if((ADC_TEMP>ADC_DATA[3])&&((ADC_TEMP-ADC_DATA[3])>FILTER_TH) || (ADC_DATA[3]>ADC_TEMP)&&((ADC_DATA[3]-ADC_TEMP)>FILTER_TH))
				{
				ADC_DATA[3] = ADC_TEMP;
				}
			else
				{		
				ADC_TEMP+=ADC_DATA[3];
				ADC_DATA[3] = ADC_TEMP>>1;
				}	
			ADC_SELECT_CH(ADC_CH4);		
			}		
		else if(TIM1_DIV==8)
			{
			HAL_ADC_Start(&hadc1);	
			}		
		else if(TIM1_DIV==9)
			{
			ADC_TEMP = HAL_ADC_GetValue(&hadc1);
			if((ADC_TEMP>ADC_DATA[4])&&((ADC_TEMP-ADC_DATA[4])>FILTER_TH) || (ADC_DATA[4]>ADC_TEMP)&&((ADC_DATA[4]-ADC_TEMP)>FILTER_TH))
				{
				ADC_DATA[4] = ADC_TEMP;
				}
			else
				{		
				ADC_TEMP+=ADC_DATA[4];
				ADC_DATA[4] = ADC_TEMP>>1;
				}
			ADC_SELECT_CH(ADC_PITCH);		
			}		
		TIM1_DIV++;	
		}	
	else		//333,(3)Hz
		{
		if((TIM2->CNT)>27000)
			{
			TC_AV_PERIOD = TIM2->CNT;	
			pitch = 0;	
			}
		else
			{
			ptch = TC_AV_PERIOD;	
			if(ptch<125)
				{
				ptch = 125;	
				}
			ptch = 8032128/ptch;
			pitch = ptch;			
			}
		reverse = TC_REVERSE;		

			
///////////////ADC 1///////////////////////////////////////////////////////////////////////////			
		if(ADC_DATA[1]<ADC_TH[0][0])		//CUE
			{
			if((BUTTONS_0&0x0001)==0)
				{
				#if defined(BUTTON_SENDER)		
				sprintf((char*)U_TX_DATA, "%s", "CUE  ");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif		
				BUTTONS_0 = 0x0001;	
				}				
			}
		else if(ADC_DATA[1]<ADC_TH[0][1])		//MEMORY
			{
			if(BUTTONS_0==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "MEMOR");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);	
				#endif	
				BUTTONS_0 = 0x0002;	
				}				
			}
		else if(ADC_DATA[1]<ADC_TH[0][2])		//CPAD1
			{
			if(BUTTONS_0==0)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{
					JUMP_SAMPL = 0;	
					if((originalBPM!=0xFFFF) && (originalBPM!=0x0000))
						{
						JUMP_SAMPL = 2116800000/originalBPM;	
						}			
					if(play_adr>JUMP_SAMPL)
						{
						play_adr-= JUMP_SAMPL;		
						BLINK_INTERFACE(4);	
						}
					}	
				else if(PADS_MODE==PADS_HCUE)
					{	
					if(HCUE_adr[0][4]!=0xFFFF)
						{
						JUMP_SAMPL = 294*HCUE_adr[0][4];
						play_adr = JUMP_SAMPL;
						BLINK_INTERFACE(4);		
						}
					}
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "CPAD1");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_0 = 0x0004;	
				}						
			}
		else if(ADC_DATA[1]<ADC_TH[0][3])		//SPAD1
			{
			if(BUTTONS_0==0)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{
					JUMP_SAMPL = 0;	
					if((originalBPM!=0xFFFF) && (originalBPM!=0x0000))
						{
						JUMP_SAMPL = 529200000/originalBPM;	
						}		
					if(play_adr>JUMP_SAMPL)
						{
						play_adr-= JUMP_SAMPL;	
						BLINK_INTERFACE(0);	
						}
					}
				else if(PADS_MODE==PADS_HCUE)
					{	
					if(HCUE_adr[0][0]!=0xFFFF)
						{
						JUMP_SAMPL = 294*HCUE_adr[0][0];
						play_adr = JUMP_SAMPL;
						BLINK_INTERFACE(0);		
						}
					}	
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "SPAD1");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_0 = 0x0008;	
				}					
			}
		else if(ADC_DATA[1]<ADC_TH[0][4])		//TRIM-
			{
			if(BUTTONS_0==0)
				{	
				if(PADS_MODE==PADS_BEAT_JUMP)
					{
					PADS_MODE = PADS_SLIP_LOOP;		
					}					
				else if(PADS_MODE==PADS_SLIP_LOOP)
					{
					PADS_MODE = PADS_LOOP;	
					}					
				else if(PADS_MODE==PADS_LOOP)
					{
					PADS_MODE = PADS_HCUE;
					}	
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "TRIMM");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_0 = 0x0010;	
				}		
			}
		else if(ADC_DATA[1]<ADC_TH[0][5])		//SAVE
			{
			if(BUTTONS_0==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "SAVE ");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_0 = 0x0020;	
				}			
			}
		else if(ADC_DATA[1]<ADC_TH[0][6])		//VINYL SIM
			{
			if(BUTTONS_0==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "VINYL");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_0 = 0x0040;	
				}		
			}
		else if(ADC_DATA[1]<ADC_TH[0][7])		//BANK+
			{
			if(BUTTONS_0==0)
				{
				if(wfmzoom>1)
					{
					wfmzoom/=2;
					previous_wfmpos = 0xFFFFFFFF;		//forcebly redraw	
					}
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "BANKP");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_0 = 0x0080;	
				}		
			}
		else if(ADC_DATA[1]<ADC_TH[0][8])		//TYPE+
			{
			if(BUTTONS_0==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "TYPEP");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_0 = 0x0100;	
				}		
			}
		else if(ADC_DATA[1]<ADC_TH[0][9])		//INSTANT CHANGE
			{
			if(BUTTONS_0==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "INSTA");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_0 = 0x0200;	
				}		
			}
		else	
			{
			if(BUTTONS_0!=0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "NONE1");	
				U_TX_DATA[5] = 13;
				U_TX_DATA[6] = 10;	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 7, 5);
				#endif	
				BUTTONS_0 = 0;	
				}	
			}
		
///////////////ADC 2///////////////////////////////////////////////////////////////////////////			
		if(ADC_DATA[2]<ADC_TH[1][0])		//PLAY
			{
			if((BUTTONS_1&0x0001)==0)
				{
				play_enable = 1;	
				play_adr = 0;
				LEDS_REGISTER&=0xDB; 		//set 0 play+cue
				LEDS_LOAD_CNT = 0;				//start load HD74HC164P 	
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "PLAY ");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif
				BUTTONS_1 = 0x0001;	
				}		
			}
		else if(ADC_DATA[2]<ADC_TH[1][1])		//REC
			{
			if(BUTTONS_1==0)
				{
				if(PADS_MODE==PADS_HCUE)
					{
					PADS_MODE = PADS_HCUE_REC;		
					}					
				else if(PADS_MODE==PADS_HCUE_REC)
					{
					PADS_MODE = PADS_HCUE;	
					}		
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "REC  ");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_1 = 0x0002;	
				}				
			}
		else if(ADC_DATA[2]<ADC_TH[1][2])		//CPAD2
			{
			if(BUTTONS_1==0)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{
					JUMP_SAMPL = 0;	
					if((originalBPM!=0xFFFF) && (originalBPM!=0x0000))
						{
						JUMP_SAMPL = 2116800000/originalBPM;	
						}	
					play_adr+= JUMP_SAMPL;
					BLINK_INTERFACE(5);
					}
				else if(PADS_MODE==PADS_HCUE)
					{	
					if(HCUE_adr[0][5]!=0xFFFF)
						{
						JUMP_SAMPL = 294*HCUE_adr[0][5];
						play_adr = JUMP_SAMPL;
						BLINK_INTERFACE(5);		
						}
					}
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "CPAD2");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_1 = 0x0004;	
				}			
			}
		else if(ADC_DATA[2]<ADC_TH[1][3])		//SPAD2
			{
			if(BUTTONS_1==0)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{	
					JUMP_SAMPL = 0;	
					if((originalBPM!=0xFFFF) && (originalBPM!=0x0000))
						{
						JUMP_SAMPL = 529200000/originalBPM;	
						}		
					play_adr+= JUMP_SAMPL;		
					BLINK_INTERFACE(1);	
					}
				else if(PADS_MODE==PADS_HCUE)
					{	
					if(HCUE_adr[0][1]!=0xFFFF)
						{
						JUMP_SAMPL = 294*HCUE_adr[0][1];
						play_adr = JUMP_SAMPL;
						BLINK_INTERFACE(1);		
						}
					}
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "SPAD2");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_1 = 0x0008;	
				}	
			}
		else if(ADC_DATA[2]<ADC_TH[1][4])		//TRIM+
			{
			if(BUTTONS_1==0)
				{							
				if(PADS_MODE==PADS_HCUE)
					{
					PADS_MODE = PADS_LOOP;	
					}					
				else if(PADS_MODE==PADS_LOOP)
					{
					PADS_MODE = PADS_SLIP_LOOP;
					}					
				else if(PADS_MODE==PADS_SLIP_LOOP)
					{
					PADS_MODE = PADS_BEAT_JUMP;
					}		
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "TRIMP");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_1 = 0x0010;	
				}	
			}
		else if(ADC_DATA[2]<ADC_TH[1][5])		//S.PADS PANEL (BACK)
			{
			if(BUTTONS_1==0)
				{
				BTN_BACK = 1;
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "SPADS");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_1 = 0x0020;	
				}		
			}
		else if(ADC_DATA[2]<ADC_TH[1][6])		//DYNAMIC FX (LOAD)
			{
			if(BUTTONS_1==0)
				{
				BTN_LOAD = 1;	
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "DYNFX");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_1 = 0x0040;	
				}	
			}
		else if(ADC_DATA[2]<ADC_TH[1][7])		//BANK-
			{
			if(BUTTONS_1==0)
				{
				if(wfmzoom<32)
					{
					wfmzoom*=2;
					previous_wfmpos = 0xFFFFFFFF;		//forcebly redraw	
					}			
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "BANKM");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_1 = 0x0080;	
				}		
			}
		else if(ADC_DATA[2]<ADC_TH[1][8])		//TYPE-
			{
			if(BUTTONS_1==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "TYPEM");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_1 = 0x0100;	
				}		
			}
		else	
			{
			if(BUTTONS_1!=0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "NONE2");	
				U_TX_DATA[5] = 13;
				U_TX_DATA[6] = 10;	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 7, 5);
				#endif	
				BUTTONS_1 = 0;	
				}	
			}		
			
///////////////ADC 3///////////////////////////////////////////////////////////////////////////			
		if(ADC_DATA[3]<ADC_TH[2][0])		//RESET
			{
			if((BUTTONS_2&0x01)==0)
				{
				if(tempo_reset==0)
					{
					LEDS_REGISTER|=0x01;		//set 1	
					tempo_reset = 1;	
					}					
				else
					{
					LEDS_REGISTER&=0xFE; 		//set 0
					tempo_reset = 0;	
					}						
				LEDS_LOAD_CNT = 0;				//start load HD74HC164P 	
				previous_adc_pitch = 0xFFFF;				
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "RESET");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_2 = 0x01;	
				}		
			}
		else if(ADC_DATA[3]<ADC_TH[2][1])		//FREE WHEEL
			{
			if(BUTTONS_2==0)
				{
				if(FREE_MODE==0)		//FREE ON
					{
					TIM4->CCR1 = 0;
					MOTOR_FREE_ON;	
					FREE_MODE = 1;		
					}
				else		//FREE OFF
					{
					TIM4->CCR1 = 2500;	
					MOTOR_FREE_OFF;
					FREE_MODE = 0;		
					}
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "WHEEL");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_2 = 0x02;	
				}	
			}
		else if(ADC_DATA[3]<ADC_TH[2][2])		//CPAD3
			{
			if(BUTTONS_2==0)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{	
					JUMP_SAMPL = 0;	
					if((originalBPM!=0xFFFF) && (originalBPM!=0x0000))
						{
						JUMP_SAMPL = 2116800000/originalBPM;	
						}			
					JUMP_SAMPL*=2;	
					if(play_adr>JUMP_SAMPL)
						{
						play_adr-= JUMP_SAMPL;	
						BLINK_INTERFACE(6);	
						}	
					}
				else if(PADS_MODE==PADS_HCUE)
					{	
					if(HCUE_adr[0][6]!=0xFFFF)
						{
						JUMP_SAMPL = 294*HCUE_adr[0][6];
						play_adr = JUMP_SAMPL;
						BLINK_INTERFACE(6);		
						}
					}
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "CPAD3");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_2 = 0x04;	
				}		
			}
		else if(ADC_DATA[3]<ADC_TH[2][3])		//SPAD3
			{
			if(BUTTONS_2==0)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{	
					JUMP_SAMPL = 0;	
					if((originalBPM!=0xFFFF) && (originalBPM!=0x0000))
						{
						JUMP_SAMPL = 1058400000/originalBPM;	
						}		
					if(play_adr>JUMP_SAMPL)
						{
						play_adr-= JUMP_SAMPL;		
						BLINK_INTERFACE(2);	
						}		
					}
				else if(PADS_MODE==PADS_HCUE)
					{	
					if(HCUE_adr[0][2]!=0xFFFF)
						{
						JUMP_SAMPL = 294*HCUE_adr[0][2];
						play_adr = JUMP_SAMPL;
						BLINK_INTERFACE(2);		
						}
					}
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "SPAD3");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_2 = 0x08;	
				}		
			}
		else if(ADC_DATA[3]<ADC_TH[2][4])		//LOAD
			{
			if(BUTTONS_2==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "LOAD ");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_2 = 0x10;	
				}			
			}
		else	
			{
			if(BUTTONS_2!=0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "NONE3");	
				U_TX_DATA[5] = 13;
				U_TX_DATA[6] = 10;	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 7, 5);
				#endif	
				BUTTONS_2 = 0;	
				}	
			}		
		
///////////////ADC 4///////////////////////////////////////////////////////////////////////////			
		if(ADC_DATA[4]<ADC_TH[3][0])		//PITCH LOCK
			{
			if((BUTTONS_3&0x01)==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "PITCH");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_3 = 0x01;	
				}			
			}
		else if(ADC_DATA[4]<ADC_TH[3][1])		//RANGE
			{				
			if(BUTTONS_3==0)
				{
				if(tempo_range==0)
					{
					tempo_range = 1;
					LEDS_REGISTER&=0x3F;
					LEDS_REGISTER|=0x80;
					}
				else if(tempo_range==1)
					{
					tempo_range = 2;
					LEDS_REGISTER&=0x3F;
					LEDS_REGISTER|=0x40;
					}
				else if(tempo_range==2)
					{
					tempo_range = 3;
					LEDS_REGISTER&=0x3F;
					LEDS_REGISTER|=0xC0;
					}
				else
					{
					tempo_range = 0;
					LEDS_REGISTER&=0x3F;
					}					
				LEDS_LOAD_CNT = 0;				//start load HD74HC164P
				previous_adc_pitch = 0xFFFF;	
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "RANGE");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_3 = 0x02;	
				}		
			}
		else if(ADC_DATA[4]<ADC_TH[3][2])		//CPAD4
			{
			if(BUTTONS_3==0)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{	
					JUMP_SAMPL = 0;	
					if((originalBPM!=0xFFFF) && (originalBPM!=0x0000))
						{
						JUMP_SAMPL = 2116800000/originalBPM;	
						}		
					JUMP_SAMPL*=2;	
					play_adr+= JUMP_SAMPL;
					BLINK_INTERFACE(7);						
					}
				else if(PADS_MODE==PADS_HCUE)
					{	
					if(HCUE_adr[0][7]!=0xFFFF)
						{
						JUMP_SAMPL = 294*HCUE_adr[0][7];
						play_adr = JUMP_SAMPL;
						BLINK_INTERFACE(7);		
						}
					}	
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "CPAD4");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_3 = 0x04;	
				}			
			}
		else if(ADC_DATA[4]<ADC_TH[3][3])		//SPAD4
			{
			if(BUTTONS_3==0)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{	
					JUMP_SAMPL = 0;	
					if((originalBPM!=0xFFFF) && (originalBPM!=0x0000))
						{
						JUMP_SAMPL = 1058400000/originalBPM;	
						}		
					play_adr+= JUMP_SAMPL;	
					BLINK_INTERFACE(3);	
					}
				else if(PADS_MODE==PADS_HCUE)
					{	
					if(HCUE_adr[0][3]!=0xFFFF)
						{
						JUMP_SAMPL = 294*HCUE_adr[0][3];
						play_adr = JUMP_SAMPL;
						BLINK_INTERFACE(3);		
						}
					}	
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "SPAD4");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_3 = 0x08;	
				}		
			}
		else if(ADC_DATA[4]<ADC_TH[3][4])		//SAMPLE EDIT
			{
			if(BUTTONS_3==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "SEDIT");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_3 = 0x10;	
				}		
			}
		else if(ADC_DATA[4]<ADC_TH[3][5])		//EXECUTE
			{
			if(BUTTONS_3==0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "EXECU");	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 5, 5);
				#endif	
				BUTTONS_3 = 0x20;	
				}			
			}
		else	
			{
			if(BUTTONS_3!=0)
				{
				#if defined(BUTTON_SENDER)	
				sprintf((char*)U_TX_DATA, "%s", "NONE4");	
				U_TX_DATA[5] = 13;
				U_TX_DATA[6] = 10;	
				HAL_UART_Transmit(&huart1, U_TX_DATA, 7, 5);	
				#endif	
				BUTTONS_3 = 0;	
				}	
			}			
			
		if(reblink_tim>0)								//blink process
			{
			if(reblink_tim==1)
				{
				if(PADS_MODE==PADS_BEAT_JUMP)
					{
					if((blink_pad>1) && (blink_pad<6)) 
						{
						COLOR_SET(PADS_COLOR[2], blink_pad);		//red
						}
					else
						{
						COLOR_SET(PADS_COLOR[0], blink_pad);	
						}						
					}
				else if(PADS_MODE==PADS_HCUE)
					{
					COLOR_SET(PADS_COLOR[1], blink_pad);	
					}					
				
				need_load_rgb = 1;	
				TIM3->CCR1 = ROUND_PWM_VALUE;
				}							
			reblink_tim--;	
			}			
		TIM1_DIV = 0;	
		}		
  HAL_TIM_IRQHandler(&htim1);
	}		

	
/////////////////////////////////////////////////////////////////////////
//
//	TIM7 2730Hz interrupt	
//	Restart pwm for direct drive motor 
//			
void TIM7_IRQHandler(void)
	{
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);	
  HAL_TIM_IRQHandler(&htim7);
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



