#include "stm32f10x.h"                  // Device header
#include "main.h"

uint8_t status;//状态判断
uint8_t	Rx_buffer[4];//接收缓冲
uint8_t	Tx_buffer[4] = {1,2,3,4};//发送数据
uint8_t	i;

int main(void)
{

	USART1_Configuration();
	NRF24L01_Test_Rx();
		
	while(1)
	{
//		status = NRF24L01_TxPacket(Tx_buffer);
//		if(status == TX_OK)
//			printf("send successfully\r\n");
//		else
//			printf("false\r\n");
		
		
		status = NRF24L01_RxPacket(Rx_buffer);
		if(status == 1)
		{
			printf("receive successfully\r\n"); 
//			printf("%d\r\n",Rx_buffer[0]);
		}
	}
}      
 
