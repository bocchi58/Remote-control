#ifndef	_LCD_H
#define _LCD_H

// 定义 RS、RW、E 引脚对应的 GPIO 端口和引脚号
#define RS_Pin 			GPIO_Pin_6
#define RS_GPIO_Port 	GPIOB
#define RW_Pin 			GPIO_Pin_7
#define RW_GPIO_Port 	GPIOB
#define E_Pin 			GPIO_Pin_8
#define E_GPIO_Port 	GPIOB

// 定义DB0-DB7引脚对应的GPIO端口和引脚号
#define DB0_Pin			GPIO_Pin_10
#define DB0_GPIO_Port	GPIOC
#define DB1_Pin			GPIO_Pin_3
#define DB1_GPIO_Port	GPIOB
#define DB2_Pin			GPIO_Pin_11
#define DB2_GPIO_Port	GPIOB
#define DB3_Pin			GPIO_Pin_12
#define DB3_GPIO_Port	GPIOB
#define DB4_Pin			GPIO_Pin_13
#define DB4_GPIO_Port	GPIOB
#define DB5_Pin			GPIO_Pin_4
#define DB5_GPIO_Port	GPIOB
#define DB6_Pin			GPIO_Pin_5
#define DB6_GPIO_Port	GPIOB
#define DB7_Pin			GPIO_Pin_2
#define DB7_GPIO_Port	GPIOD


#define	RS	 PBout(6)
#define RW	 PAout(7)
#define E	 PAout(8)

void GPIOInit(void);
void LCD_Write(uint16_t data);
void LCD_WriteCommand(uint8_t cmd);
void LCD_WriteData(uint8_t data);
void LCD_Clear(void);
void Set_cursor(uint8_t position,uint8_t flag);
void Show_String(uint8_t position,uint8_t flag,uint8_t *str);
void Move_String(uint8_t position,uint8_t flag,uint8_t *str);
void LCD_Init(void);

#endif
