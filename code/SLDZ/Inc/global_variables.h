/////////////////////////////////////////////////////////////////////////////////////////////////
// 	global variables
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

/* Audio processing variables ---------------------------------------------------------*/
#include "audio.h"

/* FATFS variables ---------------------------------------------------------*/
FRESULT res;
FIL file;
FILINFO finfo;
FATFS FAT;
unsigned int nbytes;

#define SD_OPEN_DOOR			0
#define SD_SCAN_RB				1
#define SD_MOUNTED				2
#define SD_NEED_REPLACE		3
uint8_t SD_STATUS = SD_OPEN_DOOR;

uint32_t free_mem = 0;
uint32_t used_mem = 0;

uint32_t file_size;
uint32_t N = 0;
uint32_t y;
uint8_t previous_ram = 0;
uint8_t previous_time_pos = 124;
char Buf[24]={0};						//buffer for display symbols
uint8_t need_update_oled0 = 0;
uint8_t need_update_oled1 = 0;

#define WFD_SIZE	90000

//Max audio lenght 16760832 (6m20s64ms) samples 57008 waveform samples

uint8_t WFORMDYNAMIC[WFD_SIZE]; 			//28504		//dyncmic waveform 4bits to sample
#define wfmx2		28504
#define wfmx4		42756
#define wfmx8		49882
#define wfmx16	53445
#define wfmx32	55227
uint32_t BEATGRID[2048];			// beatgrid (0, 3, 7... ) in ms
uint16_t BPMGRID[2048];				// bpmgrit BPM*100
uint8_t GRID_OFFSET = 1;			//ofsset grid 1.2.3.4
uint8_t ST_WFORM[62];

/* REKORDBOX DATABASE variables ---------------------------------------------------------*/
uint8_t playlist[512][55] 		__attribute__((at(0xD3FF0000)));
uint16_t original_tempo[512] 	__attribute__((at(0xD3FF6E00)));
uint16_t rating[512] 	__attribute__((at(0xD3FF7200)));	
uint16_t duration[512] 	__attribute__((at(0xD3FF7600)));
uint8_t key_id[512] 	__attribute__((at(0xD3FF7A00)));
uint32_t parcser_adress[512];	// 	__attribute__ ((section(".sdram")));;
char SDCARD_NAME[20] = "SD CARD";
char SD_DATE[15] = "23-01-2023";
uint16_t TOTAL_TRACKS = 0;
uint16_t TOTAL_TRACKS_IN_CURRENT_PLAYLIST = 0;
uint16_t TRACK_PLAY_IN_CURRENT_PLAYLIST = 0;
uint16_t track_play_now = 0;
uint16_t _TRACK_NUMBER = 0xFFFF;						//	
uint16_t _TRACK_IN_PLAYLIST = 0xFFFF;				//	for loading tracks
uint8_t need_load_track = 0;								//

char path_export[]="0:/PIONEER/rekordbox/export.pdb";
char KEYS[25][4];
const uint32_t COLOR_MAP_RATING[9] = 
{
0xFF404040,
0xFFF870F8,
0xFFF80000,
0xFFF8A030,
0xFFF8E330,
0xFF00E000,
0xFF00C0F8,
0xFF0050F8,
0xFF9808F8};

uint16_t TRACKS_DATABASE[1024];		//database track ID [playlist 1[ID][ID][ID]][playlist 2[ID][ID][ID]][playlist 3[ID][ID][ID]]....
uint8_t TRACKLIST_NAME[20][21];		//20 tracklists max and 20 lengt
uint16_t TRACKLIST_OFFSET[20];		//offset for TRACKS_DATABASE
uint8_t TOTAL_TRACKLISTS = 0;			//maximum 20 tracklists
uint16_t originalBPM = 0xFFFF;						//this original BPM*100 of track (pitch = 0.00%) 
uint32_t JUMP_SAMPL;			//jump in samples


/* HOT CUES and MEMORY variables ---------------------------------------------------------*/
#define NONE_MARK				0
#define MEMORY_MARK			1
#define HOT_CUE_A_MARK	2
#define HOT_CUE_B_MARK	3
#define HOT_CUE_C_MARK	4

uint32_t HCUE_COLOR[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
uint32_t HCUE_adr[2][8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
													 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};  																		//[0] => HCUE in 0.5*frames [1] => loop end in 0.5*frames   150 on 1 sec;  
uint32_t MEMORY_adr[2][10] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
															0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}; 	//[0] => MEMORY CUE in 0.5*frames [1] =>  MEMORY loop end in 0.5*frames   150 on 1 sec;
uint8_t	HCUE_type[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};	 			//b0 (0=cue / 1=loop); b1 (0=inactive / 1=active); 													
uint8_t	MEMORY_type[10] = {0};		//b0 (0=cue / 1=loop); b1 (0=inactive / 1=active); 
uint8_t number_of_hot_cue_points = 0;
uint8_t number_of_memory_cue_points = 0;

/* TIMECODE variables ---------------------------------------------------------*/
uint8_t TC_REVERSE = 0;
uint32_t TC_PERIOD = 0xFFFFFFFF;
uint32_t TC_AV_PERIOD = 0xFFFFFFFF;
uint8_t TIM_PERIOD = 0;

/* OLED variables ---------------------------------------------------------*/
//////////////////////////////////////0x[reset][set]
#define OLED_CS0				GPIOB->BSRR = 0x10002000				//CS0=0 CS1=1
#define OLED_CS1				GPIOB->BSRR = 0x20001000				//CS0=1 CS1=0
#define OLED_CS_NONE		GPIOB->BSRR = 0x00003000				//CS0=1 CS1=1
#define ROUND_PWM_VALUE	230						//pwm bridgness round
uint8_t wfmzoom = 2;				//1-2-4-8-16-32

uint32_t wfmpos = 0;
uint32_t previous_wfmpos = 0xFFFFFFFF;
uint32_t timepos = 0;
uint32_t previous_timepos = 0xFFFFFFFF;
uint32_t wpos;		//for dynamic waveform
uint16_t wf_ofs;	//for dynamic waveform
uint32_t a_div_v;	//for dynamic waveform
/* Display Browser variables ---------------------------------------------------------*/
#define ROOT_DSPL 					0
#define PLAYLISTS_DSPL 			1
#define TRACKS_DSPL					2
#define TRACKSINFO_DSPL			3
#define TAG_LIST_DSPL				4
#define TAG_LISTINFO_DSPL		5
#define UTILITY_DSPL				6
#define PADS_INFO_DSPL			7
uint8_t dSHOW = 0xFF;	

#define BROWSER0_DOWN		0
#define BROWSER0_UP			1
#define TAGLIST_DOWN		2
#define TAGLIST_UP			3
#define UTILITY_DOWN		4
#define UTILITY_UP			5
#define BROWSER1_DOWN		6
#define BROWSER1_UP			7

uint8_t ScrollLong = 52;								//4...54
uint8_t ScrollPosition = 0;							//0...54-ScrollLong
uint8_t B0CurrentCursorPosition = 0;		//0...5 position
uint8_t B1CurrentCursorPosition = 0;		//0...5 position
uint16_t BCurrentPlaylistPosition = 1;			//1....TOTAL_TRACKLISTS-5
uint16_t BCurrentTrackPosition = 1;			//1....TOTAL_TRACKS-5

/* TRANSIENT ANIMATION variables ---------------------------------------------------------*/
uint8_t need_animation = 0;   //0..128
uint8_t prev_need_animation = 0;   //0..128
uint8_t step_animation;
uint8_t DU;
uint32_t current_time_animation = 0;
uint32_t start_time_animation = 0;
uint8_t direct_animation = 0;		//0 back, 1 enter
uint8_t next_DSHOW = 0xFFFF;

/* ENCODER variables ---------------------------------------------------------*/


/* Display Browse ANIMATION variables ---------------------------------------------------------*/	
uint8_t BROWSE_LEVEL = 2;								//0 - tracklist, 1 - playlists, 2 - menu playlist, filename 3 - root display	

/* HD74HC164P LEDs variables ---------------------------------------------------------*/
////////////////////////////////////0x[reset][set]
#define DATA_LED_H		GPIOE->BSRR = 0x00000010	//HAL_GPIO_WritePin(GPIOE, DATA_LED_Pin, GPIO_PIN_SET)
#define DATA_LED_L		GPIOE->BSRR = 0x00100000	//HAL_GPIO_WritePin(GPIOE, DATA_LED_Pin, GPIO_PIN_RESET)
#define CLK_LED_H			GPIOE->BSRR = 0x00000020	//HAL_GPIO_WritePin(GPIOE, CLK_LED_Pin, GPIO_PIN_SET)
#define CLK_LED_L			GPIOE->BSRR = 0x00200000	//HAL_GPIO_WritePin(GPIOE, CLK_LED_Pin, GPIO_PIN_RESET)
#define CLK_L_DATA_L	GPIOE->BSRR = 0x00300000
#define CLK_L_DATA_H	GPIOE->BSRR = 0x00200010
uint8_t LEDS_REGISTER = 0x24;					//[A0][A1][/CUE][ext1][ext2][/play][lock][reset]
uint8_t LEDS_LOAD_CNT = 0xFF;

/* PADS ---------------------------------------------------------*/
#include "pads_color.h"
uint8_t need_load_rgb = 0;		//flag for start load rgb leds from spi		
uint32_t load_rgb_prev_tim;
uint32_t load_rgb_tim;
uint8_t PADS_MODE = 1;
uint8_t previous_PADS_MODE = 0xFF;
#define PADS_HCUE_REC			0
#define PADS_HCUE					1
#define PADS_LOOP					2
#define PADS_SLIP_LOOP		3
#define PADS_BEAT_JUMP		4
uint8_t reblink_tim = 0;			//for timer blinking
uint8_t blink_pad = 0xFF; 		//number of PAD ois blinking

/* USART DEBUG ---------------------------------------------------------*/
//usart is always enabled, but for added debugging commands, use the definitions
#define USART_INPUT_CMD_HANDLER		//Receiving, processing and preparing a response to external commands			
#define USART_BTN_SENDER					//Sending button states to uart
#define USART_STATUS_SENDER				//sending work status to uart
		
uint8_t usart_data_cnt = 0;
char U_RX_DATA[16] = {0};
uint8_t usart_new_data = 0;					//usart new data flag
uint8_t m;
uint32_t usart_timeout = 0;
char U_TX_DATA[64] = {0};	
uint16_t uart_tmp = 0;
			
/* TIM1 variables ---------------------------------------------------------*/
uint32_t ptch;
uint8_t TIM1_DIV = 0;

/* ENCODER variables ---------------------------------------------------------*/
uint8_t enc_prev_dir = 0;
uint32_t enc_prev_time = 0;
uint8_t enc_need_up = 0;
uint8_t enc_need_down = 0;
uint32_t enc_time, enc_curr_time;

/* ADCs variables ---------------------------------------------------------*/
#define ADC_PITCH			ADC_CHANNEL_0		//pitch
#define ADC_CH1				ADC_CHANNEL_1		//CUE, MEMORY, CPAD1, SPAD1, TRIMM, SAVE, VINYL SIM, BANKP, TYPEP, INSTANT CHANGE
#define ADC_CH2				ADC_CHANNEL_2		//PLAY, REC, CPAD2, SPAD2, TRIMP, S.PADS PANEL, DYNAMIC FX, BANKM, TYPEM
#define ADC_CH3				ADC_CHANNEL_3		//RESET, FREE WHEEL, CPAD3, SPAD3, LOAD  
#define ADC_CH4				ADC_CHANNEL_4		//PITCH LOCK, RANGE, CPAD4, SPAD4, SAMPLE EDIT, EXECUTE  
uint16_t ADC_DATA[5] = {2048, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
uint32_t ADC_TEMP;
#define FILTER_TH			100
static const uint16_t ADC_TH[4][10] = {160, 618, 1052, 1484, 1926, 2369, 2790, 3230, 3658, 4012,									//measure + 300
																160, 624, 1053, 1475, 1926, 2367, 2777, 3228, 3660, 0xFFFF,
																160, 610, 2404, 3405, 3946, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
																160, 620, 1856, 2814, 3523, 3972, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF };
#define HYSTERESIS		9
uint16_t previous_adc_pitch = 0xFFFF;																
													
/* BUTTONS variables ---------------------------------------------------------*/
uint16_t BUTTONS_0 = 0;
uint16_t BUTTONS_1 =0;
uint8_t BUTTONS_2 = 0;
uint8_t BUTTONS_3 = 0;
uint8_t FREE_MODE = 0;																
uint8_t tempo_range = 0;			//8% default
uint8_t tempo_reset = 0;															
uint8_t lock_control = 1;			//lock buttons, when track not loading or in process
uint8_t BTN_LOAD = 0;
uint8_t BTN_BACK = 0;

																
/* DIRECT DRIVE variables ---------------------------------------------------------*/
////////////////////////////////////0x[reset][set]								
#define MOTOR_ON				GPIOA->BSRR = 0x01000000  	//HAL_GPIO_WritePin(TT_ON_GPIO_Port, TT_ON_Pin, GPIO_PIN_RESET);	
#define MOTOR_OFF				GPIOA->BSRR = 0x00000100  	//HAL_GPIO_WritePin(TT_ON_GPIO_Port, TT_ON_Pin, GPIO_PIN_SET);
#define MOTOR_REV_OFF 	GPIOA->BSRR = 0x08000000		//HAL_GPIO_WritePin(GPIOA, TT_REV_Pin, GPIO_PIN_SET);												
#define MOTOR_REV_ON 		GPIOA->BSRR = 0x00000800		//HAL_GPIO_WritePin(GPIOA, TT_REV_Pin, GPIO_PIN_RESET);			
#define MOTOR_FREE_ON		GPIOA->BSRR = 0x00001000		//HAL_GPIO_WritePin(GPIOA, FREE_Pin, GPIO_PIN_SET);											
#define MOTOR_FREE_OFF	GPIOA->BSRR = 0x10000000		//HAL_GPIO_WritePin(GPIOA, FREE_Pin, GPIO_PIN_RESET);																	

/* TEMPORARY FOR TEST ---------------------------------------------------------*/									



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////