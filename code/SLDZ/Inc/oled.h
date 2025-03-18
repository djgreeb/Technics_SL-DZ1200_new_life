/////////////////////////////////////////////////////////////////////////////////////////////////
// 	Double SPI OLED display driver
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

/* C++ detection */
#ifdef __cplusplus
extern C {
#endif


#include "stm32f4xx_hal.h"
#include "spi.h"
#include "fonts.h"
#include "stdlib.h"
#include "string.h"

#define OLED_BLACK		0x00
#define OLED_WHITE		0x01	
	
#define OLED_BROWSE		0
#define OLED_WFM			1	
	
	
void OLED_00_Init(void);
void OLED_01_Init(void); 	
void OLED_Set_Contrast(uint8_t contrast);
void Display_OFF(void);
void Display_ON(void);	
void OLED_UpdateScreen(void);
void OLED_UpdatePart(uint8_t p);
void COPY_LOGO(uint8_t lg);
void OLED_ToggleInvert(void);
void OLED_Fill(uint8_t color);
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color);
void OLED_GotoXY(uint8_t x, uint8_t y);
char OLED_Putc(char ch, FontDef_t* Font, uint8_t color);
char OLED_Puts(char* str, FontDef_t* Font, uint8_t color);
void OLED_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t c);
void OLED_DrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t c);
void OLED_DrawFilledRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t c);
void OLED_DrawTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint8_t color);
void OLED_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t c);
void OLED_DrawFilledCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t c);
void OLED_WRITECOMMAND(uint8_t data);
void OLED_WriteMulti(uint8_t *data, uint16_t count);


/* C++ detection */
#ifdef __cplusplus
}
#endif


