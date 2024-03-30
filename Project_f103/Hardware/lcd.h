#ifndef	_LCD_H
#define _LCD_H

// ���� RS��RW��E ���Ŷ�Ӧ�� GPIO �˿ں����ź�
#define RS_Pin 			GPIO_Pin_12
#define RS_GPIO_Port 	GPIOB
#define RW_Pin 			GPIO_Pin_13
#define RW_GPIO_Port 	GPIOB
#define E_Pin 			GPIO_Pin_14
#define E_GPIO_Port 	GPIOB


// ����DB0-DB7���Ŷ�Ӧ��GPIO�˿ں����ź�
#define DB0_Pin			GPIO_Pin_0
#define DB0_GPIO_Port	GPIOA
#define DB1_Pin			GPIO_Pin_1
#define DB1_GPIO_Port	GPIOA
#define DB2_Pin			GPIO_Pin_2
#define DB2_GPIO_Port	GPIOA
#define DB3_Pin			GPIO_Pin_3
#define DB3_GPIO_Port	GPIOA
#define DB4_Pin			GPIO_Pin_4
#define DB4_GPIO_Port	GPIOA
#define DB5_Pin			GPIO_Pin_5
#define DB5_GPIO_Port	GPIOA
#define DB6_Pin			GPIO_Pin_6
#define DB6_GPIO_Port	GPIOA
#define DB7_Pin			GPIO_Pin_7
#define DB7_GPIO_Port	GPIOA


#define	RS	 PBout(12)
#define RW	 PBout(13)
#define E	 PBout(14)


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
