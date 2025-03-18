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
#include "oled.h"
#include "guistatic.h"

#define ABS(x)   ((x) > 0 ? (x) : -(x))
#define OLED_I2C_ADDR         0x78

#define OLED_WIDTH            128
#define OLED_HEIGHT           64
uint8_t OLED_BUF[2][1024];				//0-HIGH DISPLAY (BROWSE) 1-LOW DISPLAY (WAVEFORM)

uint8_t OLED_RAM_SELECT = 0;



/* Private OLED structure */
typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Inverted;
	uint8_t Initialized;
} OLED_t;

/* Private variable */
static OLED_t OLED;

void OLED_00_Init(void) 
	{
	OLED_WRITECOMMAND(0xAE); //display off
	OLED_WRITECOMMAND(0x20); //Set Memory Addressing Mode   
	OLED_WRITECOMMAND(0x02); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_WRITECOMMAND(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	OLED_WRITECOMMAND(0xC0); //Set COM Output Scan Direction				//0xC0(0xC8) - zerkalit!
	OLED_WRITECOMMAND(0x00); //---set low column address
	OLED_WRITECOMMAND(0x10); //---set high column address
	OLED_WRITECOMMAND(0x40); //--set start line address
	OLED_WRITECOMMAND(0x81); //--set contrast control register
	OLED_WRITECOMMAND(0xDF);
	OLED_WRITECOMMAND(0xA0); //--set segment re-map 0 to 127					//changes SSD1305 and OLED			//0xA0(0xA1) - zerkalit!
	OLED_WRITECOMMAND(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_WRITECOMMAND(0xA6); //--set normal display
	OLED_WRITECOMMAND(0xA8); //--set multiplex ratio(1 to 64)
	OLED_WRITECOMMAND(0x3F); //
	OLED_WRITECOMMAND(0xD3); //-set display offset
	OLED_WRITECOMMAND(0x00); //-not offset
	OLED_WRITECOMMAND(0xD5); //--set display clock divide ratio/oscillator frequency
	OLED_WRITECOMMAND(0x70); //--set divide ratio		0x50		//freq display update
	OLED_WRITECOMMAND(0xD9); //--set pre-charge period
	OLED_WRITECOMMAND(0x0F); //														-0x0F more
	OLED_WRITECOMMAND(0xDA); //--set com pins hardware configuration
	OLED_WRITECOMMAND(0x12);
	OLED_WRITECOMMAND(0xDB); //--set vcomh
	OLED_WRITECOMMAND(0x5F); //0x20,0.77xVcc									-0x5F more
	OLED_WRITECOMMAND(0x8D); //--set DC-DC enable
	OLED_WRITECOMMAND(0x14); //																-not necessaru
	OLED_WRITECOMMAND(0xAF); //--turn on OLED panel
	OLED_RAM_SELECT = OLED_BROWSE;
	OLED_Fill(OLED_BLACK);
	OLED_UpdateScreen();
	OLED.CurrentX = 0;
	OLED.CurrentY = 0;
	OLED.Initialized = 1;
	return;
	}
	

void OLED_01_Init(void) 
	{
	OLED_WRITECOMMAND(0xAE); //display off
	OLED_WRITECOMMAND(0x20); //Set Memory Addressing Mode   
	OLED_WRITECOMMAND(0x02); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	OLED_WRITECOMMAND(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	OLED_WRITECOMMAND(0xC8); //Set COM Output Scan Direction				//0xC0(0xC8) - zerkalit!
	OLED_WRITECOMMAND(0x00); //---set low column address
	OLED_WRITECOMMAND(0x10); //---set high column address
	OLED_WRITECOMMAND(0x40); //--set start line address
	OLED_WRITECOMMAND(0x81); //--set contrast control register
	OLED_WRITECOMMAND(0xDF);
	OLED_WRITECOMMAND(0xA1); //--set segment re-map 0 to 127					//changes SSD1305 and OLED			//0xA0(0xA1) - zerkalit!
	OLED_WRITECOMMAND(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	OLED_WRITECOMMAND(0xA6); //--set normal display
	OLED_WRITECOMMAND(0xA8); //--set multiplex ratio(1 to 64)
	OLED_WRITECOMMAND(0x3F); //
	OLED_WRITECOMMAND(0xD3); //-set display offset
	OLED_WRITECOMMAND(0x00); //-not offset
	OLED_WRITECOMMAND(0xD5); //--set display clock divide ratio/oscillator frequency
	OLED_WRITECOMMAND(0x70); //--set divide ratio		0x50		//freq display update
	OLED_WRITECOMMAND(0xD9); //--set pre-charge period
	OLED_WRITECOMMAND(0x0F); //														-0x0F more
	OLED_WRITECOMMAND(0xDA); //--set com pins hardware configuration
	OLED_WRITECOMMAND(0x12);
	OLED_WRITECOMMAND(0xDB); //--set vcomh
	OLED_WRITECOMMAND(0x5F); //0x20,0.77xVcc									-0x5F more
	OLED_WRITECOMMAND(0x8D); //--set DC-DC enable
	OLED_WRITECOMMAND(0x14); //																-not necessaru
	OLED_WRITECOMMAND(0xAF); //--turn on OLED panel
	OLED_RAM_SELECT = OLED_WFM;
	OLED_Fill(OLED_BLACK);
	OLED_UpdateScreen();
	OLED.CurrentX = 0;
	OLED.CurrentY = 0;
	OLED.Initialized = 1;
	return;
}

void OLED_Set_Contrast(uint8_t contrast)
	{
	OLED_WRITECOMMAND(0x81); 			//--set contrast control register
	OLED_WRITECOMMAND(contrast);	
	}

void Display_OFF(void)
	{
	OLED_WRITECOMMAND(0xAE);
	}	
	
void Display_ON(void)
	{
	OLED_WRITECOMMAND(0xAF);
	}

void OLED_UpdateScreen(void) 
	{
	uint8_t m;
	for (m = 0; m < 8; m++) 
		{
		OLED_WRITECOMMAND(0xB0 + m);
		OLED_WRITECOMMAND(0x00);				//0x00 for OLED/0x02 for SH1106
		OLED_WRITECOMMAND(0x10);
		OLED_WriteMulti(&OLED_BUF[OLED_RAM_SELECT][OLED_WIDTH * m], 128);
		}
	}

void OLED_UpdatePart(uint8_t p)	
	{
	OLED_WRITECOMMAND(0xB0 + p);
	OLED_WRITECOMMAND(0x00);		
	OLED_WRITECOMMAND(0x10);
	OLED_WriteMulti(&OLED_BUF[OLED_RAM_SELECT][OLED_WIDTH * p], 128);
	}
	
void COPY_LOGO(uint8_t lg) 
	{
	uint16_t i;
	if(lg==0)					//DISPLAY_0
		{
		for (i = 0; i < 1024; i++)
			{
			OLED_BUF[0][i] = startup00[i]; 
			}			
		}
	else if(lg==1)							//DISPLAY_1
		{
		for (i = 0; i < 1024; i++)
			{
			OLED_BUF[1][i] = startup01[i]; 
			}		
		}
	}

void OLED_ToggleInvert(void) 
	{
	uint16_t i;
	OLED.Inverted = !OLED.Inverted;
	for (i = 0; i < 1024; i++) 
		{
		OLED_BUF[OLED_RAM_SELECT][i] = ~OLED_BUF[OLED_RAM_SELECT][i];
		}
	}

void OLED_Fill(uint8_t color) 
	{
	memset(OLED_BUF[OLED_RAM_SELECT], (color == OLED_BLACK) ? 0x00 : 0xFF, 1024);
	}

void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t color) 
	{
	if (OLED.Inverted) 
		{
		color = (uint8_t)!color;
		}
	
	/* Set color */
	if (color == OLED_WHITE) 
		{
		OLED_BUF[OLED_RAM_SELECT][x + (y / 8) * OLED_WIDTH] |= 1 << (y % 8);
		} 
	else 
		{
		OLED_BUF[OLED_RAM_SELECT][x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
		}
	}

void OLED_GotoXY(uint8_t x, uint8_t y) 
	{
	OLED.CurrentX = x;
	OLED.CurrentY = y;
	}

char OLED_Putc(char ch, FontDef_t* Font, uint8_t color) 
	{
	uint32_t i, b, j;
	uint8_t FW, x_pos;	
	if(Font->data[10]==0x40)			//dynamic font Font7x10
		{
		FW = FNT7x10P[ch-32];
		}
	else if(Font->data[14]==0xA0)			//dynamic font CDJ900
		{
		FW = CDJ900Font[ch-32]+1;
		}	
	else
		{
		FW = Font->FontWidth;		
		}	

	/* Check available space in LCD */
	if((OLED_WIDTH+15)<(OLED.CurrentX+FW))			//cut symbols
		{
			
		}
	else if(OLED_WIDTH <= (OLED.CurrentX+FW))			//cut symbols
		{
		for(i=0;i<Font->FontHeight;i++) 
			{
			b = Font->data[(ch-32)*Font->FontHeight+i];
			for(j=0;j<FW;j++) 
				{
				x_pos = OLED.CurrentX+j;	
				if(x_pos<OLED_WIDTH)
					{
					if((b<<j)&0x80) 
						{
						OLED_DrawPixel(x_pos, (OLED.CurrentY+i), (uint8_t)color);
						} 
					else 
						{
						OLED_DrawPixel(x_pos, (OLED.CurrentY+i), (uint8_t)!color);
						}						
					}
				else					
					{
					j = FW;			//exit	
					}
				}
			}		
		}
	else
		{
		for(i=0;i<Font->FontHeight;i++) 
			{
			b = Font->data[(ch-32)*Font->FontHeight+i];
			for (j=0;j<FW;j++) 
				{
				if((b<<j)&0x80) 
					{
					OLED_DrawPixel(OLED.CurrentX+j, (OLED.CurrentY+i), (uint8_t)color);
					} 
				else 
					{
					OLED_DrawPixel(OLED.CurrentX+j, (OLED.CurrentY+i), (uint8_t)!color);
					}
				}
			}			
		}
	OLED.CurrentX+=FW;
	return ch;
	};

char OLED_Puts(char* str, FontDef_t* Font, uint8_t color) 
	{
	while(((*str)>31) && ((*str)<130)) 
		{
		if(OLED_Putc(*str, Font, color)!= *str) 
			{
			return *str;
			}
		str++;
		}
	return *str;
	}


void OLED_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t c) {
	int16_t dx, dy, sx, sy, err, e2, i, tmp; 
	
	dx = (x0 < x1) ? (x1 - x0) : (x0 - x1); 
	dy = (y0 < y1) ? (y1 - y0) : (y0 - y1); 
	sx = (x0 < x1) ? 1 : -1; 
	sy = (y0 < y1) ? 1 : -1; 
	err = ((dx > dy) ? dx : -dy) / 2; 

	if (dx == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}
		
		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}
		
		/* Vertical line */
		for (i = y0; i <= y1; i++) {
			OLED_DrawPixel(x0, i, c);
		}
		
		/* Return from function */
		return;
	}
	
	if (dy == 0) {
		if (y1 < y0) {
			tmp = y1;
			y1 = y0;
			y0 = tmp;
		}
		
		if (x1 < x0) {
			tmp = x1;
			x1 = x0;
			x0 = tmp;
		}
		
		/* Horizontal line */
		for (i = x0; i <= x1; i++) {
			OLED_DrawPixel(i, y0, c);
		}
		
		/* Return from function */
		return;
	}
	
	while (1) {
		OLED_DrawPixel(x0, y0, c);
		if (x0 == x1 && y0 == y1) {
			break;
		}
		e2 = err; 
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		} 
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		} 
	}
}

void OLED_DrawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t c) 
	{
	if(x >= OLED_WIDTH || y >= OLED_HEIGHT) 
		{
		return;
		}
	if ((x + w) >= OLED_WIDTH) 
		{
		w = OLED_WIDTH - x;
		}
	if ((y + h) >= OLED_HEIGHT) 
		{
		h = OLED_HEIGHT - y;
		}
	/* Draw 4 lines */
	OLED_DrawLine(x, y, x + w-1, y, c);         /* Top line */
	OLED_DrawLine(x, y + h-1, x + w-1, y + h-1, c); /* Bottom line */
	OLED_DrawLine(x, y, x, y + h-1, c);         /* Left line */
	OLED_DrawLine(x + w-1, y, x + w-1, y + h-1, c); /* Right line */
	}

void OLED_DrawFilledRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t c) {
	uint8_t i;
	
	/* Check input parameters */
	if (
		x >= OLED_WIDTH ||
		y >= OLED_HEIGHT
	) {
		/* Return error */
		return;
	}
	
	/* Check width and height */
	if ((x + w) >= OLED_WIDTH) {
		w = OLED_WIDTH - x;
	}
	if ((y + h) >= OLED_HEIGHT) {
		h = OLED_HEIGHT - y;
	}
	
	/* Draw lines */
	for (i = 0; i<h; i++) {
		/* Draw lines */
		OLED_DrawLine(x, y + i, x+w-1, y + i, c);
	}
}

void OLED_DrawTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint8_t color) {
	/* Draw lines */
	OLED_DrawLine(x1, y1, x2, y2, color);
	OLED_DrawLine(x2, y2, x3, y3, color);
	OLED_DrawLine(x3, y3, x1, y1, color);
}


void OLED_DrawFilledTriangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t x3, uint8_t y3, uint8_t color) {
	int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
	yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
	curpixel = 0;
	
	deltax = ABS(x2 - x1);
	deltay = ABS(y2 - y1);
	x = x1;
	y = y1;

	if (x2 >= x1) {
		xinc1 = 1;
		xinc2 = 1;
	} else {
		xinc1 = -1;
		xinc2 = -1;
	}

	if (y2 >= y1) {
		yinc1 = 1;
		yinc2 = 1;
	} else {
		yinc1 = -1;
		yinc2 = -1;
	}

	if (deltax >= deltay){
		xinc1 = 0;
		yinc2 = 0;
		den = deltax;
		num = deltax / 2;
		numadd = deltay;
		numpixels = deltax;
	} else {
		xinc2 = 0;
		yinc1 = 0;
		den = deltay;
		num = deltay / 2;
		numadd = deltax;
		numpixels = deltay;
	}

	for (curpixel = 0; curpixel <= numpixels; curpixel++) {
		OLED_DrawLine(x, y, x3, y3, color);

		num += numadd;
		if (num >= den) {
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

void OLED_DrawCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t c) 
	{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    OLED_DrawPixel(x0, y0 + r, c);
    OLED_DrawPixel(x0, y0 - r, c);
    OLED_DrawPixel(x0 + r, y0, c);
    OLED_DrawPixel(x0 - r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        OLED_DrawPixel(x0 + x, y0 + y, c);
        OLED_DrawPixel(x0 - x, y0 + y, c);
        OLED_DrawPixel(x0 + x, y0 - y, c);
        OLED_DrawPixel(x0 - x, y0 - y, c);
        OLED_DrawPixel(x0 + y, y0 + x, c);
        OLED_DrawPixel(x0 - y, y0 + x, c);
        OLED_DrawPixel(x0 + y, y0 - x, c);
        OLED_DrawPixel(x0 - y, y0 - x, c);
    }
	}

void OLED_DrawFilledCircle(uint8_t x0, uint8_t y0, uint8_t r, uint8_t c) 
	{
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

    OLED_DrawPixel(x0, y0 + r, c);
    OLED_DrawPixel(x0, y0 - r, c);
    OLED_DrawPixel(x0 + r, y0, c);
    OLED_DrawPixel(x0 - r, y0, c);
    OLED_DrawLine(x0 - r, y0, x0 + r, y0, c);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        OLED_DrawLine(x0 - x, y0 + y, x0 + x, y0 + y, c);
        OLED_DrawLine(x0 + x, y0 - y, x0 - x, y0 - y, c);
        OLED_DrawLine(x0 + y, y0 + x, x0 - y, y0 + x, c);
        OLED_DrawLine(x0 + y, y0 - x, x0 - y, y0 - x, c);
    }
	}
 
void OLED_ON(void) 
	{
	OLED_WRITECOMMAND(0x8D);  
	OLED_WRITECOMMAND(0x14);  
	OLED_WRITECOMMAND(0xAF);  
	}
	
void OLED_OFF(void) 
	{
	OLED_WRITECOMMAND(0x8D);  
	OLED_WRITECOMMAND(0x10);
	OLED_WRITECOMMAND(0xAE);  
	}



void OLED_WriteMulti(uint8_t* data, uint16_t count) 
	{
	//HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);
	//HAL_GPIO_WritePin(GPIOB, DC_Pin, GPIO_PIN_SET);
  GPIOB->BSRR = 0x00004000;
	HAL_SPI_Transmit(&hspi2, data, count, 100);
	//HAL_GPIO_WritePin(GPIOB, CS_Pin|DC_Pin, GPIO_PIN_SET);
	}

void OLED_WRITECOMMAND(uint8_t data) 
	{
	//HAL_GPIO_WritePin(GPIOB, DC_Pin, GPIO_PIN_RESET);
  GPIOB->BSRR = 0x40000000;
	HAL_SPI_Transmit(&hspi2, &data, 1, 10);
	//HAL_GPIO_WritePin(GPIOB, CS_Pin|DC_Pin, GPIO_PIN_SET);
	}
