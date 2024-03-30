#include "main.h"
#include "spi.h"
#include "wifi.h"
#include "SD.h"

/**********************************************************************************************************
*@name: 	SPI1_Init
*@brief: 	SPI1初始化，配置成主机模式，应用于NRF24L01
*@param: 	无
*@retval: 	无
**********************************************************************************************************/
void SPI1_Init(void)
{	 
		GPIO_InitTypeDef  GPIO_InitStructure;
		SPI_InitTypeDef SPI_InitStructure;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//使能GPIOA时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);//使能SPI1时钟

		//GPIO初始化
		GPIO_InitStructure.GPIO_Pin = NRF24L01_CSN_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//普通输出模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_CSN_GPIO, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_SCK_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_SCK_GPIO, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_MOSI_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_MOSI_GPIO, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = NRF24L01_MISO_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//复用模式
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(NRF24L01_MISO_GPIO, &GPIO_InitStructure);
		
		//这里只针对SPI口初始化
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,ENABLE);//复位SPI1
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1,DISABLE);//停止复位SPI1

		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为高电平
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
		SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式
		SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

		SPI_Cmd(SPI1, ENABLE); //使能SPI外设

		SPI1_ReadWriteByte(0xff);//启动传输		 
}  

//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2时钟一般为84Mhz：
/**********************************************************************************************************
*@name: 	SPI1_SerSpeed
*@brief: 	SPI1速度设置函数		SPI速度=fAPB2/分频系数
*@param: 	<u8>SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256
*@retval: 	无
**********************************************************************************************************/
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
	SPI1->CR1&=0XFFC7;//位3-5清零，用来设置波特率
	SPI1->CR1|=SPI_BaudRatePrescaler;	//设置SPI1速度 
	SPI_Cmd(SPI1,ENABLE); //使能SPI1
}  


/**********************************************************************************************************
*@name: 	SPI1_ReadWriteByte
*@brief: 	SPI1读写一个字节
*@param: 	<u8> TxData	要写入的字节
*@retval: 	<u8>读取到的字节
**********************************************************************************************************/
u8 SPI1_ReadWriteByte(u8 TxData)
{		 			 
 
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  
	
	SPI_I2S_SendData(SPI1, TxData); //通过外设SPIx发送一个byte  数据
		
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  
 
	return SPI_I2S_ReceiveData(SPI1); //返回通过SPIx最近接收的数据	
 		    
}

