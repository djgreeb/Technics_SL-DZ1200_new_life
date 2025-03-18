/////////////////////////////////////////////////////////////////////////////////////////////////
// Audio processing handler 44100Hz
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////
//
//	AUDIO PROCESS
//
void SPI3_IRQHandler(void)
	{		
	HAL_I2S_IRQHandler(&hi2s3);
	if(part==0)
		{
		part = 1;
		if(LEDS_LOAD_CNT<16)
			{
			if((LEDS_LOAD_CNT%2)==0)
				{
				if(((LEDS_REGISTER>>(LEDS_LOAD_CNT/2))&0x01)==0x01)
					{
					CLK_L_DATA_H;	
					}
				else
					{
					CLK_L_DATA_L;	
					}
				}
			else
				{
				CLK_LED_H;	
				}
			LEDS_LOAD_CNT++;	
			}	
		}
	else
		{	
		HAL_I2S_Transmit_IT(&hi2s3, PCM_2, 2);
		position+= pitch;
	
		if(position>9999)	
			{
			step_position = position/10000;	

			if(reverse==0 && ((play_adr+step_position+3)<=(294*all_long)))					
				{
				play_adr+= step_position;	
				if(step_position==1)
					{
					LR[0][0] = LR[0][1];
					LR[1][0] = LR[1][1];
					LR[0][1] = LR[0][2];
					LR[1][1] = LR[1][2];
					LR[0][2] = LR[0][3];
					LR[1][2] = LR[1][3];					
					}
				else
					{
					sdram_adr = play_adr&0xFFFFFF;						
					LR[0][0] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][0];							
					LR[1][0] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][1];
					sdram_adr = (play_adr+1)&0xFFFFFF;
					LR[0][1] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][0];								
					LR[1][1] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][1];		
					sdram_adr = (play_adr+2)&0xFFFFFF;
					LR[0][2] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][0];									
					LR[1][2] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][1];
					}
				sdram_adr = (play_adr+3)&0xFFFFFF;	
				LR[0][3] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][0];							
				LR[1][3] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][1];		
				}
			else if(reverse==1 && (play_adr>=step_position))
				{
				play_adr-= step_position;
				if(step_position==1)
					{
					LR[0][0] = LR[0][1];
					LR[1][0] = LR[1][1];
					LR[0][1] = LR[0][2];
					LR[1][1] = LR[1][2];
					LR[0][2] = LR[0][3];
					LR[1][2] = LR[1][3];
					}
				else
					{
					sdram_adr = (play_adr+1)&0xFFFFFF;
					LR[0][2] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][0];								
					LR[1][2] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][1];		
					sdram_adr = (play_adr+2)&0xFFFFFF;
					LR[0][1] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][0];									
					LR[1][1] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][1];
					sdram_adr = (play_adr+3)&0xFFFFFF;	
					LR[0][0] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][0];							
					LR[1][0] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][1];			
					}	
				sdram_adr = (play_adr)&0xFFFFFF;	
				LR[0][3] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][0];							
				LR[1][3] = PCM[(sdram_adr>>13)+offset_adress][sdram_adr&0x1FFF][1];			
				}
			position = position%10000;	
				
			even1l = LR[0][2];
			even1l+= LR[0][1];
			odd1l = LR[0][2];
			odd1l-= LR[0][1];
			even2l = LR[0][3];
			even2l+= LR[0][0];
			odd2l = LR[0][3];
			odd2l-= LR[0][0];
			c0l = (float)even1l*COEF[0];
			r0l = (float)even2l*COEF[1];
			c0l+= r0l;
			c1l = (float)odd1l*COEF[2];
			r1l = (float)odd2l*COEF[3];
			c1l+= r1l;
			c2l = (float)even1l*COEF[4]; 
			r2l = (float)even2l*COEF[5];
			c2l+= r2l;
			c3l = (float)odd1l*COEF[6];
			r3l = (float)odd2l*COEF[7];
			c3l+= r3l;	
				
			even1r = LR[1][2];
			even1r+= LR[1][1];
			odd1r = LR[1][2];
			odd1r-= LR[1][1];
			even2r = LR[1][3];
			even2r+= LR[1][0]; 
			odd2r = LR[1][3];
			odd2r-= LR[1][0];
			c0r = (float)even1r*COEF[0];
			r0r = (float)even2r*COEF[1];
			c0r+= r0r;
			c1r = (float)odd1r*COEF[2];
			r1r = (float)odd2r*COEF[3];
			c1r+= r1r;
			c2r = (float)even1r*COEF[4]; 
			r2r = (float)even2r*COEF[5];
			c2r+= r2r;
			c3r = (float)odd1r*COEF[6];
			r3r = (float)odd2r*COEF[7];
			c3r+= r3r;	
			}	
		T = position;
		T = T/10000;
		T = T - 1/2.0F;

		SAMPLE_BUFFER = c0l+T*(c1l+T*(c2l+T*c3l));
		SAMPLE_BUFFER*= 0.90F;
		PCM_2[0] = (int)SAMPLE_BUFFER;		
		
		SAMPLE_BUFFER = c0r+T*(c1r+T*(c2r+T*c3r));
		SAMPLE_BUFFER*= 0.90F;
		PCM_2[1] = (int)SAMPLE_BUFFER;
		part = 0;	
		}
	}



	
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



