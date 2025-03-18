/////////////////////////////////////////////////////////////////////////////////////////////////
// 	browser transient animation on oled display
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

	if(need_animation)
		{		
		current_time_animation = HAL_GetTick();
		step_animation = (current_time_animation-start_time_animation)/2;	
		if(step_animation>126)
			{
			need_animation = 0;	
			SwitchInformationLayer(next_DSHOW);		
			}				
		else
			{			
			prev_need_animation = need_animation;	
			need_animation = 128 - step_animation;	
			step_animation-= (128-prev_need_animation);		
		
			if(direct_animation==1)
				{
				for(DU=0;DU<128;DU++)
					{
					if((DU+step_animation)>127)
						{
						OLED_BUF[0][DU] = 0;	
						OLED_BUF[0][DU+128] = 0;
						OLED_BUF[0][DU+256] = 0;
						OLED_BUF[0][DU+384] = 0;
						OLED_BUF[0][DU+512] = 0;
						OLED_BUF[0][DU+640] = 0;
						OLED_BUF[0][DU+768] = 0;
						OLED_BUF[0][DU+896] = 0;							
						}						
					else
						{
						OLED_BUF[0][DU] = OLED_BUF[0][DU+step_animation];
						OLED_BUF[0][DU+128] = OLED_BUF[0][DU+step_animation+128];
						OLED_BUF[0][DU+256] = OLED_BUF[0][DU+step_animation+256];	
						OLED_BUF[0][DU+384] = OLED_BUF[0][DU+step_animation+384];	
						OLED_BUF[0][DU+512] = OLED_BUF[0][DU+step_animation+512];	
						OLED_BUF[0][DU+640] = OLED_BUF[0][DU+step_animation+640];	
						OLED_BUF[0][DU+768] = OLED_BUF[0][DU+step_animation+768];	
						OLED_BUF[0][DU+896] = OLED_BUF[0][DU+step_animation+896];								
						}						
					}
				OLED_RAM_SELECT = OLED_BROWSE;	
				OLED_DrawLine(0, 8, 127, 8, OLED_WHITE);		
				}				
			else
				{
				DU = 128;	
				while(DU>0)	
					{
					DU--;		
					if(DU<step_animation)
						{	
						OLED_BUF[0][DU] = 0;
						OLED_BUF[0][DU+128] = 0;
						OLED_BUF[0][DU+256] = 0;	
						OLED_BUF[0][DU+384] = 0;	
						OLED_BUF[0][DU+512] = 0;	
						OLED_BUF[0][DU+640] = 0;	
						OLED_BUF[0][DU+768] = 0;	
						OLED_BUF[0][DU+896] = 0;	
						}						
					else
						{
						OLED_BUF[0][DU] = OLED_BUF[0][(DU-step_animation)];
						OLED_BUF[0][DU+128] = OLED_BUF[0][(DU-step_animation)+128];
						OLED_BUF[0][DU+256] = OLED_BUF[0][(DU-step_animation)+256];	
						OLED_BUF[0][DU+384] = OLED_BUF[0][(DU-step_animation)+384];	
						OLED_BUF[0][DU+512] = OLED_BUF[0][(DU-step_animation)+512];	
						OLED_BUF[0][DU+640] = OLED_BUF[0][(DU-step_animation)+640];	
						OLED_BUF[0][DU+768] = OLED_BUF[0][(DU-step_animation)+768];	
						OLED_BUF[0][DU+896] = OLED_BUF[0][(DU-step_animation)+896];								
						}	
					}
				OLED_RAM_SELECT = OLED_BROWSE;	
				OLED_DrawLine(0, 8, 127, 8, OLED_WHITE);		
				}
			if(need_animation==0)		//last step
				{
				SwitchInformationLayer(next_DSHOW);		
				}
			else
				{				
				need_update_oled0|=0xFF;		//(all)
				}					
			}	
		}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



