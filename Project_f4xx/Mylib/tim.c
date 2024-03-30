#include "main.h"
#include "tim.h"


#include "main.h"

int Tim2_usCnt = 0;
/**********************************************************************************************************
*函 数 名: TIM2_Configuration
*功能说明: TIM2初始化 1ms 一次中断
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef tim2;
    NVIC_InitTypeDef NVIC_TIM;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    tim2.TIM_ClockDivision = TIM_CKD_DIV1;   
    tim2.TIM_Prescaler = 0;          
    tim2.TIM_CounterMode = TIM_CounterMode_Up;
    tim2.TIM_RepetitionCounter = 0;
    tim2.TIM_Period = 65535;                //1ms
	
		NVIC_TIM.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_TIM.NVIC_IRQChannelCmd = ENABLE;
		NVIC_TIM.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_TIM.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_TIM);
			
    TIM_TimeBaseInit(TIM2, &tim2);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); 
    TIM_Cmd(TIM2, DISABLE);
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			Tim2_usCnt++;
    }
}


/**********************************************************************************************************
*函 数 名: delay_ms
*功能说明: ms延时
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void delay_ms(int n)
{
	TIM_SetCounter(TIM2, 0);
	TIM_Cmd(TIM2, ENABLE);
	while (TIM_GetCounter(TIM2) < (72 * n));
	TIM_Cmd(TIM2, DISABLE);
}

//void TIM4_Init(void)
//{
//    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;

//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 

//    TIM_TimeBaseInitStructure.TIM_Period = 1000-1; 	
//    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;  
//    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 

//    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

//    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); 
//    TIM_Cmd(TIM4, ENABLE); 

//    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn; 
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
//}

volatile uint32_t CPU_RunTime = 0UL;

//void  TIM4_IRQHandler (void)
//{
//	if ( TIM_GetITStatus( TIM4, TIM_IT_Update) != RESET ) 
//	{	
//    CPU_RunTime++;
//		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);  		 
//	}		 	
//}
