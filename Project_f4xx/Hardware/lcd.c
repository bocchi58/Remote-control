#include "main.h"

#include "lcd.h"


/**********************************************************************************************************
*@name: 	GPIOInit
*@brief: 	外设GPIO初始化
*@param: 	无
*@retval: 	无
**********************************************************************************************************/
void GPIOInit(void){
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	//开启时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin			= 	DB0_Pin;
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType		=	GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed		=	GPIO_High_Speed;
	GPIO_Init(DB0_GPIO_Port, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin			= 	DB1_Pin | DB2_Pin | DB3_Pin | DB4_Pin | DB5_Pin | DB6_Pin;
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType		=	GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed		=	GPIO_High_Speed;
	GPIO_Init(DB1_GPIO_Port, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin			= 	DB7_Pin;
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType		=	GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed		=	GPIO_High_Speed;
	GPIO_Init(DB7_GPIO_Port, &GPIO_InitStructure);
	

	GPIO_InitStructure.GPIO_Pin			= 	RS_Pin|RW_Pin|E_Pin;
	GPIO_InitStructure.GPIO_Mode		=	GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType		=	GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd		=	GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed		=	GPIO_High_Speed;
	GPIO_Init(RS_GPIO_Port, &GPIO_InitStructure);
	

}

/*向LCD中写入信息（指令/数据）*/
/**********************************************************************************************************
*@name: 	LCD_Write
*@brief: 	向LCD中写入信息（指令/数据）
*@param: 	<uint16_t> data 要写入的数据
*@retval: 	无
**********************************************************************************************************/
void LCD_Write(uint16_t data){  
					//通过操作GPIO端口引脚的方式写入
	GPIO_WriteBit(DB7_GPIO_Port, DB7_Pin,(BitAction)((data & 0x80) >> 7 ));
	GPIO_WriteBit(DB6_GPIO_Port, DB6_Pin,(BitAction)((data & 0x40) >> 6 ));
	GPIO_WriteBit(DB5_GPIO_Port, DB5_Pin,(BitAction)((data & 0x20) >> 5 ));
	GPIO_WriteBit(DB4_GPIO_Port, DB4_Pin,(BitAction)((data & 0x10) >> 4 ));
	GPIO_WriteBit(DB3_GPIO_Port, DB3_Pin,(BitAction)((data & 0x08) >> 3 ));
	GPIO_WriteBit(DB2_GPIO_Port, DB2_Pin,(BitAction)((data & 0x04) >> 2 ));
	GPIO_WriteBit(DB1_GPIO_Port, DB1_Pin,(BitAction)((data & 0x02) >> 1 ));
	GPIO_WriteBit(DB0_GPIO_Port, DB0_Pin,(BitAction)(data & 0x01));	

}


/*写入指令*/
/**********************************************************************************************************
*@name: 	LCD_WriteCommand
*@brief: 	向LCD中写入指令
*@param: 	<uint8_t> cmd 要写入的指令
*@retval: 	无
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
*@brief: 	向LCD中写入数据
*@param: 	<uint8_t> data 要写入的数据
*@retval: 	无
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
*@brief: 	清屏
*@param: 	无
*@retval: 	无
**********************************************************************************************************/
void LCD_Clear(void){
	LCD_WriteCommand(0x01);
}

/**********************************************************************************************************
*@name: 	Set_cursor
*@brief: 	设置光标位置
*@param: 	<uint8_t> position		位置
			<uint8_t> flag			flag=0 第一行  flag=1 第二行
*@retval: 	无
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

/*显示字符串*/
/**********************************************************************************************************
*@name: 	Show_String
*@brief: 	显示字符串
*@param: 	<uint8_t> position		位置
			<uint8_t> flag			flag=0 第一行  flag=1 第二行
			<uint8_t*>str 			要显示的字符串
*@retval: 	无
**********************************************************************************************************/
void Show_String(uint8_t position,uint8_t flag,uint8_t *str){
	Set_cursor(position,flag);
	while(*str != '\0'){
		LCD_WriteData(*str ++);
	}
}

/**********************************************************************************************************
*@name: 	Move_String
*@brief: 	滚动字符
*@param: 	<uint8_t>	position	位置
			<uint8_t>	flag		flag=0 第一行  flag=1 第二行
			<uint8_t*>	str			需要显示的字符串
*@retval: 	无
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
*@brief: 	LCD1602初始化
*@param: 	无
*@retval: 	无
**********************************************************************************************************/
void LCD_Init(void){

	GPIOInit();
	
	LCD_WriteCommand(0x38);	//16*2显示，5*7点阵，8位数据口
	delay_ms(5);
	LCD_WriteCommand(0x38);	//增加延时确保命令可以写入
	delay_ms(15);
	LCD_WriteCommand(0x0c);	//开显示，光标关闭
	delay_ms(5);
	LCD_WriteCommand(0x06);	//文字不动，地址自动加一
	delay_ms(5);
	LCD_WriteCommand(0x01);	//清屏
	delay_ms(5);
}
