#ifndef __INIT_H
#define __INIT_H	 


/*底层硬件驱动*/
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "malloc.h" 
#include "ff.h"  
#include "exfuns.h"

/*ucosii相关头文件*/
#include "includes.h"

/*任务相关头文件*/
#include "comlink.h"
#include "MMC_SD.h" 

 void systemInit(void);


#endif
