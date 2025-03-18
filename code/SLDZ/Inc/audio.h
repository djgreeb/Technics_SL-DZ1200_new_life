/////////////////////////////////////////////////////////////////////////////////////////////////
// Audio processing variables
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////


/* Audio processing variables ---------------------------------------------------------*/
int16_t LR[2][4];
float c0r, c1r, c2r, c3r, r0r, r1r, r2r, r3r;
int32_t even1r, even2r, odd1r, odd2r;
float c0l, c1l, c2l, c3l, r0l, r1l, r2l, r3l;
int32_t even1l, even2l, odd1l, odd2l;

						//be a [2048]
uint16_t PCM[2046][8192][2]   __attribute__((at(0xD0000000)));
//uint16_t PCM[2046][8192][2]	__attribute__ ((section(".sdram")));;			// 64MB - database memory
uint16_t end_adr_valid_data = 0xFFFF;

//static float COEF[8] = {			//////optimal 2x
//0.45868970870461956,
//0.04131401926395584,
//0.48068024766578432,
//0.17577925564495955,
//-0.246185007019907091, 
//0.24614027139700284,
//-0.36030925263849456,
//0.10174985775982505
//};

static float COEF[8] = {			//////optimal 32x, 4-point, 3rd-order optimal
0.464656,
0.035344,
0.537268,
0.154244,
-0.249982, 
0.249982,
-0.493696,
0.164559
};


uint32_t play_adr = 0xFFFFFFFF;
uint8_t  part = 0;
uint8_t reverse = 0;
uint16_t pitch = 0;
uint32_t position = 0;
uint16_t step_position = 0;
uint32_t sdram_adr = 0;
uint32_t all_long = 0;					//in 1/150s
uint8_t offset_adress = 0;
uint16_t PCM_2[2];
float SAMPLE_BUFFER;
float T;
uint8_t play_enable = 0;						//allow [pitch] variable to change

/* PITCH variables ---------------------------------------------------------*/
uint32_t potenciometer_tempo;
uint32_t previous_potenciometer_tempo;
uint8_t tempo_need_update = 0;




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



