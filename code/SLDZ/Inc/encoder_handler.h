/////////////////////////////////////////////////////////////////////////////////////////////////
//	encoder_handler.h
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////


if(enc_need_up)	
	{
	if(dSHOW==TRACKS_DSPL)
		{	
		OLED_RAM_SELECT = OLED_BROWSE;	
		NAVIGATOR(BROWSER0_UP);	
		}
	else if(dSHOW==PLAYLISTS_DSPL)
		{
		OLED_RAM_SELECT = OLED_BROWSE;	
		NAVIGATOR(BROWSER1_UP);	
		}
	enc_need_up = 0;		
	}
else if(enc_need_down)
	{
	if(dSHOW==TRACKS_DSPL)
		{	
		OLED_RAM_SELECT = OLED_BROWSE;	
		NAVIGATOR(BROWSER0_DOWN);	
		}
	else if(dSHOW==PLAYLISTS_DSPL)
		{
		OLED_RAM_SELECT = OLED_BROWSE;	
		NAVIGATOR(BROWSER1_DOWN);	
		}
	enc_need_down = 0;	
	}
else if(BTN_LOAD)
	{
	if(dSHOW==ROOT_DSPL)
		{
		start_time_animation = HAL_GetTick();	
		need_animation = 128;	
		direct_animation = 1;	
		next_DSHOW = PLAYLISTS_DSPL;	
		//SwitchInformationLayer(PLAYLISTS_DSPL);	
		}		
	else if(dSHOW==PLAYLISTS_DSPL)
		{	
		TOTAL_TRACKS_IN_CURRENT_PLAYLIST = TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition] - TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1];
		B0CurrentCursorPosition = 0;
		BCurrentTrackPosition = 1;
		start_time_animation = HAL_GetTick();	
		need_animation = 128;	
		direct_animation = 1;	
		next_DSHOW = TRACKS_DSPL;	
		//SwitchInformationLayer(TRACKS_DSPL);	
		}
	else if(dSHOW==TRACKS_DSPL || dSHOW==TRACKSINFO_DSPL)
		{
		track_play_now = TRACKS_DATABASE[TRACKLIST_OFFSET[B1CurrentCursorPosition+BCurrentPlaylistPosition-1]+B0CurrentCursorPosition + BCurrentTrackPosition - 1];	
		TRACK_PLAY_IN_CURRENT_PLAYLIST = B0CurrentCursorPosition + BCurrentTrackPosition;
		need_load_track = 1;		
		}
	else if(dSHOW==TAG_LIST_DSPL || dSHOW==TAG_LISTINFO_DSPL)
		{		
//		track_play_now = TAG_LIST_BASE[TCurrentCursorPosition + TCurrentTrackPosition-1];
//		TRACK_PLAY_IN_CURRENT_PLAYLIST = TCurrentCursorPosition + TCurrentTrackPosition;
		need_load_track = 1;	
		}
	BTN_LOAD = 0;	
	}		
else if(BTN_BACK)
	{
	if(dSHOW==TRACKS_DSPL)
		{
		start_time_animation = HAL_GetTick();	
		need_animation = 128;	
		direct_animation = 0;	
		next_DSHOW = PLAYLISTS_DSPL;		
		//SwitchInformationLayer(PLAYLISTS_DSPL);	
		}		
	else if(dSHOW==PLAYLISTS_DSPL)
		{	
		start_time_animation = HAL_GetTick();	
		need_animation = 128;	
		direct_animation = 0;	
		next_DSHOW = ROOT_DSPL;		
		//SwitchInformationLayer(ROOT_DSPL);	
		}
	BTN_BACK = 0;	
	}	
	

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



