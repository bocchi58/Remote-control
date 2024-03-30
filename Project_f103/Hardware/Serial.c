//#include "stm32f10x.h"                  // Device header
//#include "stdio.h"
//#include "stdarg.h"

//void Serial_Init(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	
//	USART_InitTypeDef USART_InitStructure;
//	USART_InitStructure.USART_BaudRate = 9600;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	
//	USART_Init(USART1,&USART_InitStructure);
//	
//	USART_Cmd(USART1, ENABLE);
//}

//void Serial_SendByte(uint8_t Byte)
//{
//	USART_SendData(USART1, Byte);
//	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);

//	
//}

//void Serial_SendArray(uint8_t *Array,uint16_t Length)
//{
//	for(int i= 0; i < Length; i++)
//	{
//		Serial_SendByte(Array[i]);
//	}
//	
//}

//void Serial_SendString(char *String)
//{
//	for(int i = 0; String[i] != '\0' ; i++)
//	{
//		Serial_SendByte(String[i]);
//	}
//}

//uint32_t Serial_Pow(uint32_t X,uint32_t Y)
//{
//	uint32_t Result = 1;
//	while(Y--)
//	{
//		Result *= X;
//	}
//	return Result;
//}

//void Serial_SendNumber(uint32_t Number, uint8_t Length)
//{
//	uint8_t i;
//	for(i =0 ; i < Length; i++)
//	{
//		Serial_SendByte(Number / Serial_Pow(10 , Length - i - 1) % 10 + '0');
//	}
//}

//int fputc(int ch, FILE *f)//重定向fputc函数到串口，移植printf函数
//{
//	Serial_SendByte(ch);
//	return ch;
//}

//void Serial_Printf(char *format,...) //format用来接收格式化字符串，...用来接收可变参数列表
//{
//	char String[100];
//	va_list arg;//定义参数列表变量
//	va_start (arg,format);
//	vsprintf(String, format, arg );//打印位置String，格式化字符串format，参数表是arg
//	va_end(arg);//释放可变参数列表
//	Serial_SendString(String);
//}
