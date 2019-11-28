#include "init.h"/*头文件集合*/

//START 任务
OS_STK START_TASK_STK[128];
//任务函数
void start_task(void *pdata);

//LED0任务
OS_STK LED0_TASK_STK[64];
//任务函数
void led0_task(void *pdata);


int main(void)
{
	OSInit();  		//UCOS初始化

	systemInit();		//底层硬件初始化	
		
	OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[128-1],10); //创建开始任务
	
	OSStart(); 	//开始任务
		    
}

//开始任务
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	
	pdata=pdata;
	
	OSStatInit();  //开启统计任务
	
	OS_ENTER_CRITICAL();  //进入临界区(关闭中断)
	
	OSTaskCreate(rx_task,(void*)0,(OS_STK*)&RX_TASK_STK[64-1],7);//创建串口接收任务

	OSTaskCreate(tx_task,(void*)0,(OS_STK*)&TX_TASK_STK[64-1],8);//创建串口发送任务		
	                          
	OSTaskCreate(cmd_task,(void*)0,(OS_STK*)&CMD_TASK_STK[64-1],9);//创建命令解释任务
	
	OSTaskSuspend(10);//挂起开始任务
	
	OS_EXIT_CRITICAL();  //退出临界区(开中断)
	
}
 


