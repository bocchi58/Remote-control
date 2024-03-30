#include "main.h"
#include "key.h"

/**********************************************************************************************************
*@name: 	Key_Init
*@brief: 	������ʼ��
*@param: 	��
*@retval: 	��
**********************************************************************************************************/
void Key_Init(void)	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 
 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOB,Gʱ��
	
	//��ʼ������
//	GPIO_InitStructure.GPIO_Pin = KEY_1_PIN;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
//	GPIO_Init(KEY_1_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_2_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(KEY_2_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_3_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(KEY_3_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_4_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(KEY_4_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_5_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(KEY_5_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_6_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(KEY_6_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_7_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(KEY_7_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_8_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(KEY_8_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_9_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(KEY_9_GPIO, &GPIO_InitStructure);
}

/**********************************************************************************************************
*@name: 	Key_Scan
*@brief: 	ɨ�谴���õ�������״̬
*@param: 	<u8> 	number �����ı��
*@retval: 	<u8>	������״̬
**********************************************************************************************************/
u8 Key_Scan(u8 number)
{
	u8 status;
	switch(number){
//		case 1:
//			status = GPIO_ReadInputDataBit(KEY_1_GPIO,KEY_1_PIN);
//			break;
		case 2:
			status = GPIO_ReadInputDataBit(KEY_2_GPIO,KEY_2_PIN);
			break;
		case 3:
			status = GPIO_ReadInputDataBit(KEY_3_GPIO,KEY_3_PIN);
			break;
		case 4:
			status = GPIO_ReadInputDataBit(KEY_4_GPIO,KEY_4_PIN);
			break;
		case 5:
			status = GPIO_ReadInputDataBit(KEY_5_GPIO,KEY_5_PIN);
			break;
		case 6:
			status = GPIO_ReadInputDataBit(KEY_6_GPIO,KEY_6_PIN);
			break;
		case 7:
			status = GPIO_ReadInputDataBit(KEY_7_GPIO,KEY_7_PIN);
			break;
		case 8:
			status = GPIO_ReadInputDataBit(KEY_8_GPIO,KEY_8_PIN);
			break;
		case 9:
			status = GPIO_ReadInputDataBit(KEY_9_GPIO,KEY_9_PIN);
			break;
		default:
			status = 2;
	}
	return status;
}
