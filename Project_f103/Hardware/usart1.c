#include "main.h"
#define USART1_RX_BUFFER 50
u8 rx_buffer[USART1_RX_BUFFER];
uint8_t Flag;

/**********************************************************************************************************
*�� �� ��: USART1_Configuration
*����˵��: ���ڳ�ʼ��
*��    ��: ��                   
*�� �� ֵ: ��
**********************************************************************************************************/
void USART1_Configuration(void)
{
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef usart1;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	//��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	gpio.GPIO_Pin = USART_TX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP; //�����������ģʽ
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_GPIO,&gpio);
	
	gpio.GPIO_Pin = USART_RX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_IPU; //��������ģʽ
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_RX_GPIO,&gpio);

	usart1.USART_BaudRate = 115200;  //������
	usart1.USART_WordLength = USART_WordLength_8b;  //�ֳ�8λ
	usart1.USART_StopBits = USART_StopBits_1;
	usart1.USART_Parity = USART_Parity_No;  //У��λ
	usart1.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
	usart1.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	USART_Init(USART1,&usart1);

	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
	USART_Cmd(USART1,ENABLE);	
	
	//����NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;   //ѡ��USART2���ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;		//�ж�ʹ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
                        

}
/**********************************************************************************************************
*�� �� ��: USART1_IRQHandler
*����˵��: USART1������ʱ�ж�
*��    ��: ��
*�� �� ֵ: ��
**********************************************************************************************************/
void USART1_IRQHandler(void)
{
if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)   //RXNE ��־λΪ1 ��ʾ���Խ�������
	{
		rx_buffer[0]=USART_ReceiveData(USART1);
		Flag=1;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);  //���RXNE��־λ
	}
}
/**********************************************************************************************************
*�� �� ��: Serial_SendByte
*����˵��: ���ڷ����ֽ�����
*��    ��: <uint8_t> Byte
*�� �� ֵ: ��
**********************************************************************************************************/
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);

	
}
/**********************************************************************************************************
*�� �� ��: Serial_SendArray
*����˵��: ���ڷ�������
*��    ��: <uint8_t*> Array
		   <uint16_t> Length
*�� �� ֵ: ��
**********************************************************************************************************/
void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	for(int i= 0; i < Length; i++)
	{
		Serial_SendByte(Array[i]);
	}
	
}
/**********************************************************************************************************
*�� �� ��: Serial_SendString
*����˵��: ���ڷ����ַ���
*��    ��: <char*> String
*�� �� ֵ: ��
**********************************************************************************************************/
void Serial_SendString(char *String)
{
	for(int i = 0; String[i] != '\0' ; i++)
	{
		Serial_SendByte(String[i]);
	}
}
/**********************************************************************************************************
*�� �� ��: fputc
*����˵��: �ض���fput���������ڣ���ֲprintf����
*��    ��: <int> 	ch
		   <FILE*>	f
*�� �� ֵ: ��
**********************************************************************************************************/
int fputc(int ch, FILE *f)//�ض���fputc���������ڣ���ֲprintf����
{
	Serial_SendByte(ch);
	return ch;
}
