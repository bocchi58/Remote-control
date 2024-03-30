#include "main.h"
#include "spi.h"
#include "wifi.h"
#include "SD.h"

/**********************************************************************************************************
*@name: 	SPI1_Init
*@brief: 	SPI1��ʼ�������ó�����ģʽ��Ӧ����NRF24L01
*@param: 	��
*@retval: 	��
**********************************************************************************************************/
void SPI1_Init(void)
{	 
		GPIO_InitTypeDef  GPIO_InitStructure;
		SPI_InitTypeDef SPI_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);//ʹ��SPI1ʱ��

		//GPIO��ʼ��
		GPIO_InitStructure.GPIO_Pin = NRF24L01_CSN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//��ͨ���ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_CSN_GPIO, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_SCK_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//����ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_SCK_GPIO, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_MOSI_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//����ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_MOSI_GPIO, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_MISO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//����ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_MISO_GPIO, &GPIO_InitStructure);
		
		//����ֻ���SPI�ڳ�ʼ��
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);//��λSPI1
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//ֹͣ��λSPI1

		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
		SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
		SPI_Init(SPI1, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���

		SPI_Cmd(SPI1, ENABLE); //ʹ��SPI����

		SPI1_ReadWriteByte(0xff);//��������		 
}  

//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2ʱ��һ��Ϊ84Mhz��
/**********************************************************************************************************
*@name: 	SPI1_SerSpeed
*@brief: 	SPI1�ٶ����ú���		SPI�ٶ�=fAPB2/��Ƶϵ��
*@param: 	<u8>SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256
*@retval: 	��
**********************************************************************************************************/
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI1->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI1->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI1,ENABLE); //ʹ��SPI1
}  


/**********************************************************************************************************
*@name: 	SPI1_ReadWriteByte
*@brief: 	SPI1��дһ���ֽ�
*@param: 	<u8> TxData	Ҫд����ֽ�
*@retval: 	<u8>��ȡ�����ֽ�
**********************************************************************************************************/
u8 SPI1_ReadWriteByte(u8 TxData)
{		 			 
 
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//�ȴ���������  
	
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ��byte  ����
		
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //�ȴ�������һ��byte  
 
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����	
 		    
}

