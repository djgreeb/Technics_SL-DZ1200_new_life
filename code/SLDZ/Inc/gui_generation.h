/////////////////////////////////////////////////////////////////////////////////////////////////
// GUI generation
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#define NONE_MARK				0
#define MEMORY_MARK			1
#define HOT_CUE					2


void REDRAW_TIMESCROLL(uint8_t pos); 		//pos 0...124 0-fill 124-none
void DrawMinuteMarkers(void);
void ShowTrackNumber(uint8_t track);
void DrawMemoryMarker(uint8_t p, uint8_t type);
void ShowTempo(uint16_t tempo);
void DrawNewEmpty_TIMESCROLL(void);
void RAMSCROLL(uint8_t pos); 		//pos 0...124 0-fill 124-none
void ShowBPM(uint16_t bpm);			//	show bpm input bpm*10


void SwitchInformationLayer(uint8_t LAY);			//switch displays
void NAVIGATOR(uint8_t UPDOWN);					//Navigate preset list, UTILITY and other
void int_BIx_DRAW_ALL_LINES(uint8_t lvl);
void ReDrawScroll(uint16_t total_elements, uint16_t current_element_pos);
void int_B_DRAW_ALL_LINES(void);
void int_B_DRAW_ONE_LINE(uint8_t UPDOWN);
void int_B1_DRAW_ONE_LINE(uint8_t UPDOWN);
void int_DRAW_CUR_TN(void);					//draw current track nubmer in playlist

/////////////////////////////////////////////////////////////////////////
//
//	pos 0...124 0-fill 124-none
//		
void REDRAW_TIMESCROLL(uint8_t pos)
	{
	if(pos != previous_time_pos)	
		{
		OLED_RAM_SELECT = OLED_WFM;	
		if(pos==0)
			{
			OLED_DrawLine(2, 60, 125, 60, OLED_WHITE);
			OLED_DrawLine(2, 61, 125, 61, OLED_WHITE);		
			}				
		else if(pos>123)
			{
			OLED_DrawLine(2, 60, 125, 60, OLED_BLACK);
			OLED_DrawLine(2, 61, 125, 61, OLED_BLACK);		
			}		
		else
			{
			if(pos>previous_time_pos)			//move >>>
				{
				OLED_DrawLine(2+previous_time_pos, 60, 1+pos, 60, OLED_BLACK);
				OLED_DrawLine(2+previous_time_pos, 61, 1+pos, 61, OLED_BLACK);		
				}	
			else													//move <<<
				{
				OLED_DrawLine(2+pos, 60, 1+previous_time_pos, 60, OLED_WHITE);
				OLED_DrawLine(2+pos, 61, 1+previous_time_pos, 61, OLED_WHITE);		
				}				
			}			
		need_update_oled1|=0x80;		//(7)	
		previous_time_pos = pos;
		}
	return;	
	}
	
	
	
/////////////////////////////////////////////////////////////////////////
//
//	pos 0...62 0-fill 62-none
//		
void RAMSCROLL(uint8_t pos)
	{
	if(pos>previous_ram)	
		{
		OLED_RAM_SELECT = OLED_WFM;
		while(previous_ram<=pos)
			{
			OLED_DrawPixel(3+(previous_ram*2), 60, OLED_WHITE);
			OLED_DrawPixel(3+(previous_ram*2), 61, OLED_WHITE);
			previous_ram++;	
			}
		need_update_oled1|=0x80;		//(7)	
		previous_ram = pos;
		}
	return;	
	}	
	

	
/////////////////////////////////////////////////////////////////////////
//
//
//		
void DrawNewEmpty_TIMESCROLL(void)
	{
	OLED_RAM_SELECT = OLED_WFM;	
	for(uint8_t i=0; i<62;i++)
		{
		OLED_DrawPixel(2+(i*2), 60, OLED_WHITE);
		OLED_DrawPixel(2+(i*2), 61, OLED_WHITE);	
		OLED_DrawPixel(3+(i*2), 60, OLED_BLACK);
		OLED_DrawPixel(3+(i*2), 61, OLED_BLACK);		
		}		
	need_update_oled1|=0x80;		//(7)		
	}
	
/////////////////////////////////////////////////////////////////////////
//
//	
//		
void DrawMinuteMarkers(void)
	{
	OLED_RAM_SELECT = OLED_WFM;	
	OLED_DrawLine(0, 63, 127, 63, OLED_BLACK);
	if(all_long>0)
		{
		uint32_t a = 17856000/all_long;		//124*9000*16
		uint32_t npoint = all_long/9000;
		uint32_t delta;	
		while(npoint>0)
			{
			delta = npoint*a;
			delta>>=4;
			if(delta<124)
				{
				OLED_DrawPixel(2+delta, 63, OLED_WHITE);	
				}	
			npoint--;		
			}			
		}		
	need_update_oled1|=0x80;		//(7)		
	return;
	}

/////////////////////////////////////////////////////////////////////////
//
//SHOW TRACK NUMBER
//
//
void ShowTrackNumber(uint8_t track)
	{
	OLED_RAM_SELECT = OLED_WFM;	
	if(track==0)
		{
		OLED_DrawFilledRectangle(2, 29, 13, 8, OLED_BLACK);	
		}		
	else
		{
		sprintf((char*)Buf, "%02lu", track%100);
		OLED_GotoXY(2, 29);
		OLED_Puts(Buf, &Font_7x10, OLED_WHITE);	
		}		
	need_update_oled1|=0x18;		//(3+4)		
	return;	
	}

	
	
////////////////////////////////////////////////	
//Draw MEMORY red triangle on time bar	
// p=0 - disable all triangle	
//	p 1...124	
//#define NONE_MARK				0
//#define MEMORY_MARK			1
//#define HOT_CUE					2
//
void DrawMemoryMarker(uint8_t p, uint8_t type)
	{
	OLED_RAM_SELECT = OLED_WFM;	
	if(type==NONE_MARK)
		{
		OLED_DrawLine(0, 43, 127, 43, OLED_BLACK);	
		OLED_DrawLine(0, 44, 127, 44, OLED_BLACK);
		OLED_DrawLine(0, 45, 127, 45, OLED_BLACK);			
		need_update_oled1|=0x20;		//(5)
		return;
		}
	else if(p<125)
		{
		if(p!=0)
			{
			if(type==1)		//MEMORY_MARK
				{	
				OLED_DrawPixel(1+p, 43, OLED_WHITE);
				OLED_DrawPixel(1+p, 44, OLED_WHITE);	
				OLED_DrawPixel(1+p, 45, OLED_WHITE);						
				OLED_DrawPixel(p-1, 43, OLED_WHITE);	
				OLED_DrawPixel(p, 43, OLED_WHITE);
				OLED_DrawPixel(p+2, 43, OLED_WHITE);	
				OLED_DrawPixel(p+3, 43, OLED_WHITE);	
				OLED_DrawPixel(p, 44, OLED_WHITE);	
				OLED_DrawPixel(p+2, 44, OLED_WHITE);
				}
			else					//HOT_CUE
				{	
				OLED_DrawPixel(1+p, 43, OLED_WHITE);
				OLED_DrawPixel(1+p, 44, OLED_BLACK);	
				OLED_DrawPixel(1+p, 45, OLED_WHITE);	
				OLED_DrawPixel(p, 43, OLED_WHITE);
				OLED_DrawPixel(p, 44, OLED_WHITE);	
				OLED_DrawPixel(p, 45, OLED_WHITE);	
				OLED_DrawPixel(2+p, 43, OLED_WHITE);
				OLED_DrawPixel(2+p, 44, OLED_WHITE);	
				OLED_DrawPixel(2+p, 45, OLED_WHITE);	
				}	
			}	
		else
			{
			OLED_DrawLine(0, 43, 127, 43, OLED_BLACK);	
			OLED_DrawLine(0, 44, 127, 44, OLED_BLACK);
			OLED_DrawLine(0, 45, 127, 45, OLED_BLACK);			
			}
		need_update_oled1|=0x20;		//(5)	
		return;
		}
	else
		{
		return;	
		}
	}		
	

////////////////////////////////////////////////
//	
//		Show tempo func
//
void ShowTempo(uint16_t tempo)
	{
	OLED_RAM_SELECT = OLED_WFM;	
	if(tempo==10000)	
		{
		sprintf((char*)Buf, "%s", " ");			//NONE	
		}	
	else if(tempo>10000)
		{
		sprintf((char*)Buf, "%s", "+");			//PLUS	
		}
	else
		{
		sprintf((char*)Buf, "%s", "-");			//MINUS
		}
	
	if(tempo>10000)	
		{
		tempo = tempo - 10000;	
		}
	else
		{
		tempo = 10000-tempo;	
		}
	OLED_DrawFilledRectangle(93, 35, 30, 7, OLED_BLACK);					//clear tempo area
	if(tempo_range>0)							//16% or 33% or 50% range
		{
		sprintf((char*)&Buf[1], "%1lu", tempo/100);			//PITCH
		if((tempo/100)>9)
			{
			OLED_GotoXY(99, 35);	
			}
		else
			{			
			OLED_GotoXY(105, 35);
			}		
		OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);			
		OLED_DrawPixel(115, 41, OLED_WHITE);		
		sprintf((char*)Buf, "%1lu", (tempo%100)/10);			//PITCH
		OLED_GotoXY(117, 35);
		OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);		
		}
	else
		{
		sprintf((char*)&Buf[1], "%1lu", tempo/100);			//PITCH
		if((tempo/100)>9)
			{
			OLED_GotoXY(93, 35);	
			}
		else
			{			
			OLED_GotoXY(99, 35);
			}				
		OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);			
		OLED_DrawPixel(109, 41, OLED_WHITE);		
		sprintf((char*)Buf, "%02lu", tempo%100);			//PITCH
		OLED_GotoXY(111, 35);
		OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);			
		}
	need_update_oled1|=0x30;		//(4+5)		
	}
	
	
////////////////////////////////////////////////
//	
//	show bpm 
// input bpm*10
// input 0xFFFF - none
//	
void ShowBPM(uint16_t bpm)
	{
	OLED_RAM_SELECT = OLED_WFM;		
	OLED_DrawFilledRectangle(103, 25, 25, 7, OLED_BLACK);					//clear tempo area
	if(bpm != 0xFFFF)
		{
		bpm = bpm%10000; 	
		sprintf((char*)Buf, "%1lu", bpm/10);
		if((bpm/10)>99)
			{
			OLED_GotoXY(103, 25);	
			}			
		else if((bpm/10)>9)
			{
			OLED_GotoXY(109, 25);	
			}
		else
			{
			OLED_GotoXY(115, 25);	
			}				
		OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);
		OLED_DrawPixel(121, 31, OLED_WHITE);
		sprintf((char*)Buf, "%01lu", bpm%10);	
		OLED_GotoXY(123, 25);
		OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);		
		}	
	need_update_oled1|=0x08;		//(3)		
	return;	
	};	

	
/////////////////////////////////////////////////////////////////////////////////////	
//Navigate playlists, tracks, UTILITY and other
//
//	 		position -- (cursor up)
//			position ++ (cursor down)
//	
void NAVIGATOR(uint8_t UPDOWN)
	{		
	if(dSHOW==PLAYLISTS_DSPL || dSHOW==TRACKS_DSPL || dSHOW==TRACKSINFO_DSPL)	
		{
		if(UPDOWN==BROWSER0_UP)
			{
			if(B0CurrentCursorPosition==5)												//All lines update++
				{
				if(BCurrentTrackPosition == TOTAL_TRACKS_IN_CURRENT_PLAYLIST-5)
					{
					return;	
					}
				else
					{
					BCurrentTrackPosition++;
					if(dSHOW==TRACKS_DSPL)
						{
						int_BIx_DRAW_ALL_LINES(0);	
						int_DRAW_CUR_TN();	
						}
					else if(dSHOW==TRACKSINFO_DSPL)
						{
						int_BIx_DRAW_ALL_LINES(0);	
						}
					}
				}
			else																								//One line update++
				{
				if(TOTAL_TRACKS_IN_CURRENT_PLAYLIST>6 || B0CurrentCursorPosition<(TOTAL_TRACKS_IN_CURRENT_PLAYLIST-1))
					{
					if(dSHOW==TRACKS_DSPL)
						{
						int_B_DRAW_ONE_LINE(UPDOWN);	
						int_DRAW_CUR_TN();	
						}
					else if(dSHOW==TRACKSINFO_DSPL)
						{
						//int_BI_DRAW_ONE_LINE(UPDOWN);	
						}
					}
				}
			need_update_oled0|=0xFF;		//(all)	
			}
		else if(UPDOWN==BROWSER0_DOWN)
			{
			if(B0CurrentCursorPosition==0)											//All lines update--
				{
				if(BCurrentTrackPosition == 1)
					{
					return;	
					}
				else
					{
					BCurrentTrackPosition--;
					if(dSHOW==TRACKS_DSPL)
						{
						int_BIx_DRAW_ALL_LINES(0);	
						int_DRAW_CUR_TN();	
						}
					else if(dSHOW==TRACKSINFO_DSPL)
						{
						int_BIx_DRAW_ALL_LINES(0);	
						}						
					}	
				}
			else														//One line update--
				{
				if(dSHOW==TRACKS_DSPL)
					{
					int_B_DRAW_ONE_LINE(UPDOWN);
					int_DRAW_CUR_TN();	
					}
				else if(dSHOW==TRACKSINFO_DSPL)
					{
					//int_BI_DRAW_ONE_LINE(UPDOWN);	
					}	
				}	
			need_update_oled0|=0xFF;		//(all)	
			}	
		else if(UPDOWN==BROWSER1_UP)
			{				
			if(B1CurrentCursorPosition==5)												//All lines update++
				{
				if(BCurrentPlaylistPosition==TOTAL_TRACKLISTS-5)
					{
					return;	
					}
				else
					{
					BCurrentPlaylistPosition++;
					int_BIx_DRAW_ALL_LINES(1);
					}
				}
			else																								//One line update++
				{
				if(TOTAL_TRACKLISTS>6 || B1CurrentCursorPosition<(TOTAL_TRACKLISTS-1))
					{
					int_B1_DRAW_ONE_LINE(UPDOWN);	 
					}
				}	
			need_update_oled0|=0xFF;		//(all)
			}
		else if(UPDOWN==BROWSER1_DOWN)
			{
			if(B1CurrentCursorPosition==0)											//All lines update--
				{
				if(BCurrentPlaylistPosition == 1)
					{
					return;	
					}
				else
					{
					BCurrentPlaylistPosition--;
					int_BIx_DRAW_ALL_LINES(1);							
					}	
				}
			else														//One line update--
				{
				int_B1_DRAW_ONE_LINE(UPDOWN);	 		
				}
			need_update_oled0|=0xFF;		//(all)
			}	
		}
	else if(dSHOW==TAG_LIST_DSPL || dSHOW==TAG_LISTINFO_DSPL)	///////////////////TAG LIST mode selected
		{
//		if(UPDOWN==TAGLIST_UP)
//			{
//			if(TCurrentCursorPosition==7)												//All lines update++
//				{
//				if(TCurrentTrackPosition == TOTAL_TRACKS_IN_TAG_LIST-7)
//					{
//					return;	
//					}
//				else
//					{
//					BSP_LCD_SelectLayer(1);	
//					BSP_LCD_SetTransparency(1, 255);
//					BSP_LCD_SetTextColor(0x00000000);
//					BSP_LCD_FillRect(14, 18, 466, 152);		
//					BSP_LCD_SetFont(&Font15P);
//					TCurrentTrackPosition++;
//					if(dSHOW==TAG_LIST)
//						{
//						int_T_DRAW_ALL_LINES();
//						}
//					else
//						{
//						int_TI_DRAW_ALL_LINES();	
//						}
//					}
//				}
//			else																								//One line update++
//				{
//				if(TOTAL_TRACKS_IN_TAG_LIST>8 || TCurrentCursorPosition<(TOTAL_TRACKS_IN_TAG_LIST-1))
//					{
//					if(dSHOW==TAG_LIST)
//						{	
//						int_T_DRAW_ONE_LINE(UPDOWN);
//						}
//					else
//						{
//						int_TI_DRAW_ONE_LINE(UPDOWN);	
//						}
//					}
//				}
//			}
//		else if(UPDOWN==TAGLIST_DOWN)
//			{
//			if(TCurrentCursorPosition==0)											//All lines update--
//				{
//				if(TCurrentTrackPosition == 1)
//					{
//					return;	
//					}
//				else
//					{
//					BSP_LCD_SelectLayer(1);	
//					BSP_LCD_SetTransparency(1, 255);
//					BSP_LCD_SetTextColor(0x00000000);
//					BSP_LCD_FillRect(14, 18, 466, 152);	
//					BSP_LCD_SetFont(&Font15P);
//					TCurrentTrackPosition--;
//					if(dSHOW==TAG_LIST)
//						{
//						int_T_DRAW_ALL_LINES();
//						}
//					else
//						{
//						int_TI_DRAW_ALL_LINES();	
//						}							
//					}	
//				}
//			else														//One line update--
//				{
//				if(dSHOW==TAG_LIST)
//					{	
//					int_T_DRAW_ONE_LINE(UPDOWN);
//					}
//				else
//					{
//					int_TI_DRAW_ONE_LINE(UPDOWN);	
//					}				
//				}	
//			}	
		need_update_oled0|=0xFF;		//(all)
		}
	else if(dSHOW==UTILITY_DSPL)		///////////////////////UTILITY mode selected
		{
//		if(UPDOWN==UTILITY_UP)
//			{
//			if(UCurrentCursorPosition==7)												//All lines update++
//				{
//				if(CurrentUPosition == TOTAL_U_POSITIONS-7)
//					{
//					return;	
//					}
//				else
//					{
//					BSP_LCD_SelectLayer(1);	
//					BSP_LCD_SetTransparency(1, 255);
//					BSP_LCD_SetTextColor(0x00000000);
//					BSP_LCD_FillRect(14, 18, 466, 152);		
//					BSP_LCD_SetFont(&Font15P);
//					CurrentUPosition++;
//					int_U_DRAW_ALL_LINES();
//					}
//				}
//			else if(TOTAL_U_POSITIONS>8 || UCurrentCursorPosition<(TOTAL_U_POSITIONS-1))								//One line update++
//				{
//				int_U_DRAW_ONE_LINE(UPDOWN);
//				}
//			}
//		else if(UPDOWN==UTILITY_DOWN)
//			{
//			if(UCurrentCursorPosition==0)											//All lines update--
//				{
//				if(CurrentUPosition == 1)
//					{
//					return;	
//					}
//				else
//					{
//					BSP_LCD_SelectLayer(1);	
//					BSP_LCD_SetTransparency(1, 255);
//					BSP_LCD_SetTextColor(0x00000000);
//					BSP_LCD_FillRect(14, 18, 466, 152);	
//					BSP_LCD_SetFont(&Font15P);
//					CurrentUPosition--;
//					int_U_DRAW_ALL_LINES();					
//					}	
//				}
//			else														//One line update--
//				{
//				int_U_DRAW_ONE_LINE(UPDOWN);		
//				}	
//			}	
			need_update_oled0|=0xFF;		//(all)
			}
	return;	
	};
		
	
///////////////////////////////////////////////	
//Switch Displays
//
//	
void SwitchInformationLayer(uint8_t LAY)
	{
	uint8_t update_all_page = 0;	
		
	if(dSHOW != LAY)
		{
		dSHOW = LAY;
		update_all_page = 1;	
		}		
		
	if(LAY==ROOT_DSPL)		//X => ROOT_DSPL
		{	
		if(update_all_page==1)
			{
			OLED_RAM_SELECT = OLED_BROWSE;	
			OLED_Fill(OLED_BLACK);	
			OLED_DrawLine(0, 8, 127, 8, OLED_WHITE);	
			if(SD_STATUS==SD_OPEN_DOOR)
				{
				sprintf((char*)Buf, "+NO SD CARD");	
				}	
			else
				{				
				sprintf((char*)Buf, "+SD CARD INFO");
				}
			Buf[0] = 0x80; //sd symbol	
			OLED_GotoXY(0, 0);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);
			//Draw SD card symbol
			OLED_DrawLine(4, 21, 4, 28, OLED_WHITE);		
			OLED_DrawLine(5, 28, 5, 31, OLED_WHITE);
			OLED_DrawLine(4, 31, 4, 55, OLED_WHITE);
			OLED_DrawLine(5, 56, 34, 56, OLED_WHITE);
			OLED_DrawLine(35, 33, 35, 55, OLED_WHITE);
			OLED_DrawLine(34, 33, 34, 27, OLED_WHITE);
			OLED_DrawLine(35, 29, 35, 16, OLED_WHITE);	
			OLED_DrawLine(10, 15, 34, 15, OLED_WHITE);	
			OLED_DrawLine(7, 21, 7, 25, OLED_WHITE);	
			OLED_DrawLine(8, 21, 8, 25, OLED_WHITE);	
			OLED_DrawLine(10, 17, 10, 21, OLED_WHITE);	
			OLED_DrawLine(11, 17, 11, 21, OLED_WHITE);				
			OLED_DrawLine(13, 17, 13, 21, OLED_WHITE);	
			OLED_DrawLine(14, 17, 14, 21, OLED_WHITE);
			OLED_DrawLine(16, 17, 16, 21, OLED_WHITE);	
			OLED_DrawLine(17, 17, 17, 21, OLED_WHITE);
			OLED_DrawLine(19, 17, 19, 21, OLED_WHITE);	
			OLED_DrawLine(20, 17, 20, 21, OLED_WHITE);
			OLED_DrawLine(22, 17, 22, 21, OLED_WHITE);	
			OLED_DrawLine(23, 17, 23, 21, OLED_WHITE);	
			OLED_DrawLine(25, 17, 25, 21, OLED_WHITE);	
			OLED_DrawLine(26, 17, 26, 21, OLED_WHITE);	
			OLED_DrawLine(28, 17, 28, 21, OLED_WHITE);	
			OLED_DrawLine(29, 17, 29, 21, OLED_WHITE);	
			OLED_DrawLine(31, 17, 31, 21, OLED_WHITE);	
			OLED_DrawLine(32, 17, 32, 21, OLED_WHITE);	
			OLED_DrawPixel(5, 20, OLED_WHITE);
			OLED_DrawPixel(6, 19, OLED_WHITE);
			OLED_DrawPixel(7, 18, OLED_WHITE);	
			OLED_DrawPixel(8, 17, OLED_WHITE);
			OLED_DrawPixel(9, 16, OLED_WHITE);
			sprintf((char*)Buf, "%s", SDCARD_NAME);	
			OLED_GotoXY(51, 11);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);				
			sprintf((char*)Buf, "%1lu tracks", TOTAL_TRACKS);	
			OLED_GotoXY(51, 20);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);		
			sprintf((char*)Buf, "%1lu playlists", TOTAL_TRACKLISTS);	
			OLED_GotoXY(51, 29);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);		
			sprintf((char*)Buf, "%s", SD_DATE);	
			OLED_GotoXY(51, 38);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);	
			if(used_mem>999)
				{
				if(used_mem>9999)
					{
					sprintf((char*)Buf, "%1lu"".""%01lu"" GB used", used_mem/1000, (used_mem%1000)/100);		
					}
				else
					{
					sprintf((char*)Buf, "%1lu"".""%02lu"" GB used", used_mem/1000, (used_mem%1000)/10);		
					}
				}
			else
				{
				sprintf((char*)Buf, "%1lu"" MB used", used_mem);	
				}	
			OLED_GotoXY(51, 47);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);	
			if(free_mem>999)
				{	
				if(free_mem>9999)
					{
					sprintf((char*)Buf, "%1lu"".""%01lu"" GB free", free_mem/1000, (free_mem%1000)/100);		
					}
				else
					{
					sprintf((char*)Buf, "%1lu"".""%02lu"" GB free", free_mem/1000, (free_mem%1000)/10);		
					}
				}
			else
				{
				sprintf((char*)Buf, "%1lu"" MB free", free_mem);	
				}
			OLED_GotoXY(51, 56);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);			
			need_update_oled0|=0xFF;		//(all)				
			}
		}
	else if(LAY==PLAYLISTS_DSPL)		//X => PLAYLISTS_DSPL
		{	
		if(update_all_page==1)
			{
			OLED_RAM_SELECT = OLED_BROWSE;
			OLED_Fill(OLED_BLACK);		
			OLED_DrawLine(0, 8, 127, 8, OLED_WHITE);
			sprintf((char*)Buf, "+PLAYLISTS");
			Buf[0] = 0x80; //playlist symbol	
			OLED_GotoXY(0, 0);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);
			int_BIx_DRAW_ALL_LINES(1);		
			need_update_oled0|=0xFF;		//(all)		
			}
		}	
	else if(LAY==TRACKS_DSPL)		//X => TRACKS_DSPL
		{	
		if(update_all_page==1)
			{
			OLED_RAM_SELECT = OLED_BROWSE;
			OLED_Fill(OLED_BLACK);		
			OLED_DrawLine(0, 8, 127, 8, OLED_WHITE);
			sprintf((char*)&Buf[1], TRACKLIST_NAME[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]);
			Buf[0] = 0x81; //playlist symbol	
			OLED_GotoXY(0, 0);
			OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);	
			int_DRAW_CUR_TN();				
			int_BIx_DRAW_ALL_LINES(0);	
			}		
		need_update_oled0|=0xFF;		//(all)	
		}	
	else if(TRACKSINFO_DSPL)		//X => TRACKSINFO_DSPL
		{	
		OLED_RAM_SELECT = OLED_BROWSE;
			
		}
	else if(TAG_LIST_DSPL)		//X => TAG_LIST_DSPL
		{	
		OLED_RAM_SELECT = OLED_BROWSE;
			
		}
	else if(TAG_LISTINFO_DSPL)		//X => TAG_LISTINFO_DSPL
		{	
		OLED_RAM_SELECT = OLED_BROWSE;
			
		}
	else if(UTILITY_DSPL)		//X => UTILITY_DSPL
		{	
		OLED_RAM_SELECT = OLED_BROWSE;
			
		}
	else if(PADS_INFO_DSPL)		//X => PADS_INFO_DSPL
		{	
		OLED_RAM_SELECT = OLED_BROWSE;
			
		}
	return;	
	};	
	
	
	
/////////////////////////////////	
//
//internal function for Browser + INFO
void int_BIx_DRAW_ALL_LINES(uint8_t lvl)
	{
	uint16_t E, j, k;
	if(lvl==0)					//tracks
		{
		OLED_DrawFilledRectangle(3, 10, 125, 54, OLED_BLACK);		////clear text area
		OLED_DrawFilledRectangle(3, 10+(9*B0CurrentCursorPosition), 125, 9, OLED_WHITE);		////Draw selected cursor	
		for(E=0;(E<6) && (TOTAL_TRACKS_IN_CURRENT_PLAYLIST>(E+BCurrentTrackPosition-1));E++)
			{				
			OLED_GotoXY(4, 11+(9*E));
			if(E==B0CurrentCursorPosition)
				{
				OLED_Puts(playlist[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]+E+BCurrentTrackPosition-1]-1], &Font_CDJ900, OLED_BLACK);	
				}
			else
				{
				OLED_Puts(playlist[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]+E+BCurrentTrackPosition-1]-1], &Font_CDJ900, OLED_WHITE);
				}
			}	
		ReDrawScroll(TOTAL_TRACKS_IN_CURRENT_PLAYLIST, BCurrentTrackPosition);		
		}
	else if(lvl==1)						//playlists
		{
		OLED_DrawFilledRectangle(3, 10, 125, 54, OLED_BLACK);		////clear text area	
		OLED_DrawFilledRectangle(3, 10+(9*B1CurrentCursorPosition), 125, 9, OLED_WHITE);	
		Buf[0] = 0x81; //playlist symbol
		Buf[1] = 0;	
		for(E=0;E<6 && TOTAL_TRACKLISTS>(E+BCurrentPlaylistPosition-1);E++)
			{
			if(E==B1CurrentCursorPosition)
				{
				OLED_GotoXY(4, 11+(9*E));		
				OLED_Puts(Buf, &Font_CDJ900, OLED_BLACK);	
				OLED_GotoXY(10, 11+(9*E));		
				OLED_Puts(TRACKLIST_NAME[E+BCurrentPlaylistPosition-1], &Font_CDJ900, OLED_BLACK);			
				}
			else
				{
				OLED_GotoXY(4, 11+(9*E));		
				OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);	
				OLED_GotoXY(10, 11+(9*E));			
				OLED_Puts(TRACKLIST_NAME[E+BCurrentPlaylistPosition-1], &Font_CDJ900, OLED_WHITE);		
				}	
			}	
		ReDrawScroll(TOTAL_TRACKLISTS, BCurrentPlaylistPosition);		
		}
	else if(lvl==2)
		{
//		for(E=0;E<4;E++)
//			{
//			if(E==B2CurrentCursorPosition)
//				{
//				BSP_LCD_SetTextColor(LCD_COLOR_BLACK);	
//				}
//			else
//				{
//				BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
//				}	
//			if(E==0)
//				{
//				sprintf((char*)Buf, "%s", "[FILENAME]");			
//				}
//			else if(E==1)
//				{
//				sprintf((char*)Buf, "%s", "[FOLDER]");			
//				}	
//			else if(E==2)
//				{
//				sprintf((char*)Buf, "%s", "[PLAYLIST]");			
//				}	
//			else if(E==3)
//				{
//				sprintf((char*)Buf, "%s", "[TRACK]");			
//				}				
//			BSP_LCD_DisplayStringAt(20, 20+(19*E), Buf, INFO_MODE);			
//			}
//		BSP_LCD_SetTextColor(0x00000000);					//Draw paper rectangle
//		BSP_LCD_FillRect(272, 18, 208, 152);	

//		for(j=0;j<7;j++)							////Dots
//			{
//			for(k=0;k<99;k++)
//				{
//				BSP_LCD_DrawPixel(276+2*k, 36+19*j, LCD_COLOR_DARK_1);
//				}
//			}	
//		BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);	
//			
//		for(E=0;E<8;E++)
//			{
//			if(B2CurrentCursorPosition==0 || B2CurrentCursorPosition==3)
//				{
//				if(E<TOTAL_TRACKS)
//					{
//					BSP_LCD_DisplayStringAt(299,21+(19*E), playlist[E], TRANSPARENT_MODE);	
//					sprintf((char*)Buf, "%s", "~");		
//					BSP_LCD_DisplayStringAt(280, 21+(19*E),Buf, TRANSPARENT_MODE);		
//					}
//				}
//			else if(B2CurrentCursorPosition==1)				
//				{
//				if(E==0)
//					{
//					sprintf((char*)Buf, "%s", "EMPTY");		
//					BSP_LCD_DisplayStringAt(345, 59 ,Buf, TRANSPARENT_MODE);
//					sprintf((char*)Buf, "%s", "or not support");		
//					BSP_LCD_DisplayStringAt(319, 78 ,Buf, TRANSPARENT_MODE);	
//					}
//				}
//			else if(B2CurrentCursorPosition==2)				
//				{
//				if(E<TOTAL_TRACKLISTS)
//					{
//					BSP_LCD_DisplayStringAt(299,21+(19*E), TRACKLIST_NAME[E], TRANSPARENT_MODE);
//					sprintf((char*)Buf, "%s", "|");		
//					BSP_LCD_DisplayStringAt(280, 21+(19*E),Buf, TRANSPARENT_MODE);		
//					}
//				}			
//			}	
//		BSP_LCD_SelectLayer(0);	
//		ReDrawScroll(4, 0);	
		}	
	else if(lvl==3)
		{
//		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);				
//		sprintf((char*)Buf, "%s", "/");		
//		BSP_LCD_DisplayStringAt(20,20, Buf, TRANSPARENT_MODE);					
//		sprintf((char*)Buf, "%s", "SD card");						
//		BSP_LCD_DisplayStringAt(39, 20, Buf, TRANSPARENT_MODE);	
//		BSP_LCD_SetTextColor(0x00000000);					//Draw paper rectangle
//		BSP_LCD_FillRect(272, 18, 208, 152);	
//		for(j=0;j<7;j++)							////Dots
//			{
//			for(k=0;k<99;k++)
//				{
//				BSP_LCD_DrawPixel(276+2*k, 36+19*j, LCD_COLOR_DARK_1);
//				}
//			}	
//		BSP_LCD_SetTextColor(LCD_COLOR_DARK_1);						
//		BSP_LCD_DisplayStringAt(280, 21, SDCARD_NAME, TRANSPARENT_MODE);				//Flash name
//		sprintf((char*)Buf, "%1lu"" songs", TOTAL_TRACKS);						
//		BSP_LCD_DisplayStringAt(280, 40, Buf, TRANSPARENT_MODE);		
//		sprintf((char*)Buf, "%1lu"" playlists", TOTAL_TRACKLISTS);						
//		BSP_LCD_DisplayStringAt(280, 59, Buf, TRANSPARENT_MODE);	
//		//sprintf((char*)Buf, "%s", "DATE");		
//		BSP_LCD_DisplayStringAt(280, 78, SD_DATE, TRANSPARENT_MODE);			//DATE
//		if(used_mem>999)
//			{
//			if(used_mem>9999)
//				{
//				sprintf((char*)Buf, "%1lu"".""%01lu"" GB used", used_mem/1000, (used_mem%1000)/100);		
//				}
//			else
//				{
//				sprintf((char*)Buf, "%1lu"".""%02lu"" GB used", used_mem/1000, (used_mem%1000)/10);		
//				}
//			}
//		else
//			{
//			sprintf((char*)Buf, "%1lu"" MB used", used_mem);	
//			}		
//		BSP_LCD_DisplayStringAt(280, 97, Buf, TRANSPARENT_MODE);	
//		if(free_mem>999)
//			{	
//			if(free_mem>9999)
//				{
//				sprintf((char*)Buf, "%1lu"".""%01lu"" GB free", free_mem/1000, (free_mem%1000)/100);		
//				}
//			else
//				{
//				sprintf((char*)Buf, "%1lu"".""%02lu"" GB free", free_mem/1000, (free_mem%1000)/10);		
//				}
//			}
//		else
//			{
//			sprintf((char*)Buf, "%1lu"" MB free", free_mem);	
//			}							
//		BSP_LCD_DisplayStringAt(280, 116, Buf, TRANSPARENT_MODE);	
//		BSP_LCD_SelectLayer(0);
//		ReDrawScroll(1, 0);			
		}	
	return;	
	}	
	

/////////////////////////////////	
//	
//Redraw scroll on new position	
void ReDrawScroll(uint16_t total_elements, uint16_t current_element_pos)
	{
	OLED_DrawLine(1, ScrollPosition+10, 1, ScrollPosition+ScrollLong+9, OLED_BLACK);
	OLED_DrawLine(0, ScrollPosition+10, 0, ScrollPosition+ScrollLong+9, OLED_BLACK);	
	///Calculate scroll	
	if(total_elements<7)
		{
		ScrollLong = 54;
		ScrollPosition = 0;	
		OLED_DrawLine(1, 10, 1, 63, OLED_BLACK);
		OLED_DrawLine(0, 10, 0, 63, OLED_BLACK);		
		}
	else
		{
		ScrollLong = 324/total_elements;
		if(ScrollLong>54)
			{
			ScrollLong = 54;	
			}
		else if(ScrollLong<4)
			{
			ScrollLong = 4;	
			}	
		ScrollPosition = ((current_element_pos-1)*(54-ScrollLong))/(total_elements-6);
		OLED_DrawLine(1, ScrollPosition+10, 1, ScrollPosition+ScrollLong+9, OLED_WHITE);
		OLED_DrawLine(0, ScrollPosition+10, 0, ScrollPosition+ScrollLong+9, OLED_WHITE);	
		}
	}	
	
	
	
/////////////////////////////////	
//
//internal function for Browser
void int_B_DRAW_ALL_LINES(void)
	{
	uint16_t E;
	OLED_DrawFilledRectangle(3, 10, 125, 54, OLED_BLACK);		////clear text area
	OLED_DrawFilledRectangle(3, 10+(9*B0CurrentCursorPosition), 125, 9, OLED_WHITE);		////Draw selected cursor		
	for(E=0;E<6 && TOTAL_TRACKS_IN_CURRENT_PLAYLIST>(E+BCurrentTrackPosition-1);E++)
		{					
		OLED_GotoXY(4, 11+(9*E));
		if(E==B0CurrentCursorPosition)
			{
			OLED_Puts(playlist[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]+E+BCurrentTrackPosition-1]-1], &Font_CDJ900, OLED_BLACK);	
			}
		else
			{
			OLED_Puts(playlist[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]+E+BCurrentTrackPosition-1]-1], &Font_CDJ900, OLED_WHITE);
			}	
		}	
	ReDrawScroll(TOTAL_TRACKS_IN_CURRENT_PLAYLIST, BCurrentTrackPosition);	
	};	
	
	

/////////////////////////////////	
//
//internal function for Browser
void int_B_DRAW_ONE_LINE(uint8_t UPDOWN)							
	{
	OLED_DrawFilledRectangle(3, 10+(9*B0CurrentCursorPosition), 125, 9, OLED_BLACK);		////Draw selected cursor
	OLED_GotoXY(4, 11+(9*B0CurrentCursorPosition));
	OLED_Puts(playlist[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]+BCurrentTrackPosition+B0CurrentCursorPosition-1]-1], &Font_CDJ900, OLED_WHITE);	
	
	if(UPDOWN==BROWSER0_UP)
		{
		B0CurrentCursorPosition++;
		}
	else
		{
		B0CurrentCursorPosition--;	
		}
	OLED_DrawFilledRectangle(3, 10+(9*B0CurrentCursorPosition), 125, 9, OLED_WHITE);		////Draw selected cursor	
	OLED_GotoXY(4, 11+(9*B0CurrentCursorPosition));
	OLED_Puts(playlist[TRACKS_DATABASE[TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]+BCurrentTrackPosition+B0CurrentCursorPosition-1]-1], &Font_CDJ900, OLED_BLACK);
	return;			
	};	
	
/////////////////////////////////	
//
//internal function for Browser level 1
void int_B1_DRAW_ONE_LINE(uint8_t UPDOWN)							
	{
	Buf[0] = 0x81; //playlist symbol
	Buf[1] = 0;			
	OLED_DrawFilledRectangle(3, 10+(9*B1CurrentCursorPosition), 125, 9, OLED_BLACK);		////Draw selected cursor	
	OLED_GotoXY(4, 11+(9*B1CurrentCursorPosition));	
	OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);		
	OLED_GotoXY(10, 11+(9*B1CurrentCursorPosition));
	OLED_Puts(TRACKLIST_NAME[B1CurrentCursorPosition+BCurrentPlaylistPosition-1], &Font_CDJ900, OLED_WHITE);		
	if(UPDOWN==BROWSER1_UP)
		{
		B1CurrentCursorPosition++;
		}
	else if(UPDOWN==BROWSER1_DOWN)
		{
		B1CurrentCursorPosition--;	
		}
	OLED_DrawFilledRectangle(3, 10+(9*B1CurrentCursorPosition), 125, 9, OLED_WHITE);		////Draw selected cursor	
	OLED_GotoXY(4, 11+(9*B1CurrentCursorPosition));		
	OLED_Puts(Buf, &Font_CDJ900, OLED_BLACK);		
	OLED_GotoXY(10, 11+(9*B1CurrentCursorPosition));	
	OLED_Puts(TRACKLIST_NAME[B1CurrentCursorPosition+BCurrentPlaylistPosition-1], &Font_CDJ900, OLED_BLACK);		
	return;			
	};			
	
	
/////////////////////////////////	
//
//draw current track nubmer in playlist	
//
void int_DRAW_CUR_TN(void)
	{
	uint8_t posx = 89;
	if((TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition] - TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1])<10)
		{
		posx+=12;	
		OLED_DrawFilledRectangle(113, 0, 14, 7, OLED_BLACK);	
		}
	else if((TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition] - TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1])<100)
		{
		posx+=6;	
		OLED_DrawFilledRectangle(101, 0, 26, 7, OLED_BLACK);		
		}	
	else
		{
		OLED_DrawFilledRectangle(89, 0, 38, 7, OLED_BLACK);		
		}		
	if((B0CurrentCursorPosition + BCurrentTrackPosition)<10)
		{
		posx+=12;	
		}
	else if((B0CurrentCursorPosition + BCurrentTrackPosition)<100)
		{
		posx+=6;	
		}	
	sprintf((char*)Buf, "%1lu/%1lu", B0CurrentCursorPosition + BCurrentTrackPosition, TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition] - TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]);		
	OLED_GotoXY(posx, 0);
	OLED_Puts(Buf, &Font_CDJ900, OLED_WHITE);		
	return;	
	};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

