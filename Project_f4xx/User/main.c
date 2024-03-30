#include "main.h"

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

void System_Init(void);
void System_Configration(void);
/**
  * @brief  Main Function
  * @param  None
  * @retval None
  */
int main()
{
	
//	System_Configration();
//	System_Init();
//	delay_ms(100);
//	startTast();
//	vTaskStartScheduler();

	while(1)
	{
	}
} 
/**
  * @brief  Configuration 
  * @param  None
  * @retval None
  */
void System_Configration(void)
{

	USART1_Configuration();
}

void System_Init(void)
{
}


