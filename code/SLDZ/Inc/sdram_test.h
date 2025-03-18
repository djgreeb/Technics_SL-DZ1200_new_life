/////////////////////////////////////////////////////////////////////////////////////////////////
// 	sdram_test.h
//	product: Technics SL-DZ1200 new life
//
//
//
//
//	Author: Anatska Andrei
//
/////////////////////////////////////////////////////////////////////////////////////////////////


#define test_lenght	33521664	

#if defined(USART_STATUS_SENDER)		
sprintf((char*)U_TX_DATA, "Start SDRAM test\n\r");	
HAL_UART_Transmit(&huart1, U_TX_DATA, 18, 5);	
#endif	
for(y=0;y<test_lenght;y++)
	{
	PCM[(y/16384)%2048][(y/2)%8192][y%2] = 0xFFFF;	
	}	
#if defined(USART_STATUS_SENDER)		
sprintf((char*)U_TX_DATA, "SDRAM filled 0xFFFF\n\r");	
HAL_UART_Transmit(&huart1, U_TX_DATA, 21, 5);	
#endif		
for(y=0;y<test_lenght;y++)
	{
	if(PCM[(y/16384)%2048][(y/2)%8192][y%2] != 0xFFFF)	
		{
		#if defined(USART_STATUS_SENDER)		
		sprintf((char*)U_TX_DATA, "Error ADDR %08lu Read value %05lu \n\r", y , PCM[(y/16384)%2048][(y/2)%8192][y%2]);	
		HAL_UART_Transmit(&huart1, U_TX_DATA, 39, 45);
		HAL_Delay(200);		
		#endif	
		}		
	}	
for(y=0;y<test_lenght;y++)
	{
	PCM[(y/16384)%2048][(y/2)%8192][y%2] = 0x55AA;	
	}	
#if defined(USART_STATUS_SENDER)		
sprintf((char*)U_TX_DATA, "SDRAM filled 0x55AA\n\r");	
HAL_UART_Transmit(&huart1, U_TX_DATA, 21, 5);	
#endif		
for(y=0;y<test_lenght;y++)
	{
	if(PCM[(y/16384)%2048][(y/2)%8192][y%2] != 0x55AA)	
		{
		#if defined(USART_STATUS_SENDER)		
		sprintf((char*)U_TX_DATA, "Error ADDR %08lu Read value %05lu \n\r", y , PCM[(y/16384)%2048][(y/2)%8192][y%2]);	
		HAL_UART_Transmit(&huart1, U_TX_DATA, 39, 45);
		HAL_Delay(200);		
		#endif	
		}		
	}	
for(y=0;y<test_lenght;y++)
	{
	PCM[(y/16384)%2048][(y/2)%8192][y%2] = 0xAA55;	
	}	
#if defined(USART_STATUS_SENDER)		
sprintf((char*)U_TX_DATA, "SDRAM filled 0xAA55\n\r");	
HAL_UART_Transmit(&huart1, U_TX_DATA, 21, 5);	
#endif		
for(y=0;y<test_lenght;y++)
	{
	if(PCM[(y/16384)%2048][(y/2)%8192][y%2] != 0xAA55)	
		{
		#if defined(USART_STATUS_SENDER)		
		sprintf((char*)U_TX_DATA, "Error ADDR %08lu Read value %05lu \n\r", y , PCM[(y/16384)%2048][(y/2)%8192][y%2]);	
		HAL_UART_Transmit(&huart1, U_TX_DATA, 39, 45);
		HAL_Delay(200);		
		#endif	
		}		
	}	
for(y=0;y<test_lenght;y++)
	{
	PCM[(y/16384)%2048][(y/2)%8192][y%2] = 0;	
	}	
#if defined(USART_STATUS_SENDER)		
sprintf((char*)U_TX_DATA, "SDRAM filled 0x0000\n\r");	
HAL_UART_Transmit(&huart1, U_TX_DATA, 21, 5);	
#endif			
for(y=0;y<test_lenght;y++)
	{
	if(PCM[(y/16384)%2048][(y/2)%8192][y%2] != 0)	
		{
		#if defined(USART_STATUS_SENDER)		
		sprintf((char*)U_TX_DATA, "Error ADDR %08lu Read value %05lu \n\r", y , PCM[(y/16384)%2048][(y/2)%8192][y%2]);	
		HAL_UART_Transmit(&huart1, U_TX_DATA, 39, 45);
		HAL_Delay(200);		
		#endif	
		}		
	}	
#if defined(USART_STATUS_SENDER)		
sprintf((char*)U_TX_DATA, "End SDRAM test\n\r");	
HAL_UART_Transmit(&huart1, U_TX_DATA, 16, 5);	
#endif	





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



