#include "main.h"

#include "lcd.h"


/**********************************************************************************************************
*@name: 	GPIOInit
*@brief: 	����GPIO��ʼ��
*@param: 	��
*@retval: 	��
**********************************************************************************************************/
void GPIOInit(void){
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	//����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin			= 	DB0_Pin;
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType		=	GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed		=	GPIO_High_Speed;
	GPIO_Init(DB0_GPIO_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin			= 	DB1_Pin | DB2_Pin | DB3_Pin | DB4_Pin | DB5_Pin | DB6_Pin;
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType		=	GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed		=	GPIO_High_Speed;
	GPIO_Init(DB1_GPIO_Port, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin			= 	DB7_Pin;
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType		=	GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed		=	GPIO_High_Speed;
	GPIO_Init(DB7_GPIO_Port, &GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin			= 	RS_Pin|RW_Pin|E_Pin;
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType		=	GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed		=	GPIO_High_Speed;
	GPIO_Init(RS_GPIO_Port, &GPIO_InitStructure);
	

}

/*��LCD��д����Ϣ��ָ��/���ݣ�*/
/**********************************************************************************************************
*@name: 	LCD_Write
*@brief: 	��LCD��д����Ϣ��ָ��/���ݣ�
*@param: 	<uint16_t> data Ҫд�������
*@retval: 	��
**********************************************************************************************************/
void LCD_Write(uint16_t data){  
					//ͨ������GPIO�˿����ŵķ�ʽд��
	GPIO_WriteBit(DB7_GPIO_Port, DB7_Pin,(BitAction)((data & 0x80) >> 7 ));
	GPIO_WriteBit(DB6_GPIO_Port, DB6_Pin,(BitAction)((data & 0x40) >> 6 ));
	GPIO_WriteBit(DB5_GPIO_Port, DB5_Pin,(BitAction)((data & 0x20) >> 5 ));
	GPIO_WriteBit(DB4_GPIO_Port, DB4_Pin,(BitAction)((data & 0x10) >> 4 ));
	GPIO_WriteBit(DB3_GPIO_Port, DB3_Pin,(BitAction)((data & 0x08) >> 3 ));
	GPIO_WriteBit(DB2_GPIO_Port, DB2_Pin,(BitAction)((data & 0x04) >> 2 ));
	GPIO_WriteBit(DB1_GPIO_Port, DB1_Pin,(BitAction)((data & 0x02) >> 1 ));
	GPIO_WriteBit(DB0_GPIO_Port, DB0_Pin,(BitAction)(data & 0x01));	

}


/*д��ָ��*/
/**********************************************************************************************************
*@name: 	LCD_WriteCommand
*@brief: 	��LCD��д��ָ��
*@param: 	<uint8_t> cmd Ҫд���ָ��
*@retval: 	��
**********************************************************************************************************/
void LCD_WriteCommand(uint8_t cmd){
	
	RS = 0;
	RW = 0;
	E = 0;
	
	LCD_Write(cmd);
	delay_ms(5);
	E = 1;
	delay_ms(5);
	E = 0;	
}
/**********************************************************************************************************
*@name: 	LCD_WriteData
*@brief: 	��LCD��д������
*@param: 	<uint8_t> data Ҫд�������
*@retval: 	��
**********************************************************************************************************/
void LCD_WriteData(uint8_t data){
	
	RS = 1;
	RW = 0;
	E = 0;
	
	LCD_Write(data);
	delay_ms(5);
	E = 1;
	delay_ms(5);
	E = 0;	
}

/**********************************************************************************************************
*@name: 	LCD_Clear
*@brief: 	����
*@param: 	��
*@retval: 	��
**********************************************************************************************************/
void LCD_Clear(void){
	LCD_WriteCommand(0x01);
}

/**********************************************************************************************************
*@name: 	Set_cursor
*@brief: 	���ù��λ��
*@param: 	<uint8_t> position		λ��
			<uint8_t> flag			flag=0 ��һ��  flag=1 �ڶ���
*@retval: 	��
**********************************************************************************************************/
void Set_cursor(uint8_t position,uint8_t flag){
	uint8_t addr;
	if(flag == 0){
		addr = 0x00 + position;
	}else{
		addr = 0x40 + position;
	}
	
	LCD_WriteCommand(addr | 0x80);
	
}

/*��ʾ�ַ���*/
/**********************************************************************************************************
*@name: 	Show_String
*@brief: 	��ʾ�ַ���
*@param: 	<uint8_t> position		λ��
			<uint8_t> flag			flag=0 ��һ��  flag=1 �ڶ���
			<uint8_t*>str 			Ҫ��ʾ���ַ���
*@retval: 	��
**********************************************************************************************************/
void Show_String(uint8_t position,uint8_t flag,uint8_t *str){
	Set_cursor(position,flag);
	while(*str != '\0'){
		LCD_WriteData(*str ++);
	}
}

/**********************************************************************************************************
*@name: 	Move_String
*@brief: 	�����ַ�
*@param: 	<uint8_t>	position	λ��
			<uint8_t>	flag		flag=0 ��һ��  flag=1 �ڶ���
			<uint8_t*>	str			��Ҫ��ʾ���ַ���
*@retval: 	��
**********************************************************************************************************/
void Move_String(uint8_t position,uint8_t flag,uint8_t *str){
	
	LCD_WriteCommand(0x1c);
	Set_cursor(position,flag);
	while(*str != '\0'){
		LCD_WriteData(*str ++);
	}
}

/**********************************************************************************************************
*@name: 	LCD_Init
*@brief: 	LCD1602��ʼ��
*@param: 	��
*@retval: 	��
**********************************************************************************************************/
void LCD_Init(void){

	GPIOInit();
	
	LCD_WriteCommand(0x38);	//16*2��ʾ��5*7����8λ���ݿ�
	delay_ms(5);
	LCD_WriteCommand(0x38);	//������ʱȷ���������д��
	delay_ms(15);
	LCD_WriteCommand(0x0c);	//����ʾ�����ر�
	delay_ms(5);
	LCD_WriteCommand(0x06);	//���ֲ�������ַ�Զ���һ
	delay_ms(5);
	LCD_WriteCommand(0x01);	//����
	delay_ms(5);
}
