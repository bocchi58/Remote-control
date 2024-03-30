#ifndef __MAIN_H__
#define __MAIN_H__

#define ABS(x) ((x)>0? (x):(-(x))) 
#define LIMIT_MAX_MIN(x, max, min)	(((x) <= (min)) ? (min):(((x) >= (max)) ? (max) : (x)))  //????

//Standard Lib
#include <stm32f4xx.h>	 
#include <stm32f4xx_conf.h>
#include <stm32f4xx_spi.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Mylib
#include "tim.h"
#include "usart1.h"
#include "spi.h"
#include "wifi.h"
#include "lcd.h" 
#include "SD.h"

//Task lib
#include "Start_Task.h"



#endif
