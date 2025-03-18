/////////////////////////////////////////////////////////////////////////////////////////////////
// 	DAC PCM1734E configuration
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////

/* DAC variables ---------------------------------------------------------*/	
uint8_t DAC_CONFIGURATION[8] = {0x07, 0x82, 0x04, 0x00, 0x02, 0xFF, 0x01, 0xFF};

void DAC_INIT(void);


/////////////////////////////////////////////////////////////////////////
//
//	DAC CONFIGURATION
//	call after starting I2S	
//
void DAC_INIT(void)
	{
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_RESET);	
	HAL_SPI_Transmit(&hspi5, &DAC_CONFIGURATION[0], 2, 2);		
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_RESET);	
	HAL_SPI_Transmit(&hspi5, &DAC_CONFIGURATION[2], 2, 2);		
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_RESET);	
	HAL_SPI_Transmit(&hspi5, &DAC_CONFIGURATION[4], 2, 2);		
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_RESET);	
	HAL_SPI_Transmit(&hspi5, &DAC_CONFIGURATION[6], 2, 2);		
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_SET);	
	}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



