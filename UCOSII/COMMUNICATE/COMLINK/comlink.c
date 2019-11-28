#include "comlink.h"
#include "led.h"
OS_EVENT *rx_queue;
void *rx_message[USART_REC_LEN];

OS_EVENT *tx_queue;
void *tx_message[USART_REC_LEN];

OS_EVENT *cmd_queue;
void *cmd_message[USART_REC_LEN];

OS_MEM *comlink_buf;
INT8U comlink_part[16][USART_REC_LEN];

OS_STK RX_TASK_STK[64];
OS_STK TX_TASK_STK[64];
OS_STK CMD_TASK_STK[64];

void com_init(void)
{
	INT8U err;
	
	rx_queue = OSQCreate(rx_message[0],USART_REC_LEN);
	tx_queue = OSQCreate(tx_message[0],USART_REC_LEN);
	cmd_queue = OSQCreate(cmd_message[0],USART_REC_LEN);

  comlink_buf = OSMemCreate(comlink_part,16, USART_REC_LEN, &err);	
}


void rx_task(void *pdata)
{
	INT8U *buffer;
	INT8U err;
	while(1)
	{
		buffer = OSMemGet(comlink_buf,&err); 
		if(rx_queue != (OS_EVENT *)0 && buffer != NULL)
		{
			printf("rxqueue ok");
	   	memset(buffer,0,USART_REC_LEN);	//清除缓冲区
			buffer = OSQPend(rx_queue,0,&err);//请求消息rx_queue
			if(buffer != (void *)0)			//接收到消息
      { 
			  OSQPost(cmd_queue,buffer);			//接收到的消息
      }
    }
		memset(USART_RX_BUF,0,USART_REC_LEN);
		OSMemPut(comlink_buf,buffer);		//释放内存*/
    OSTimeDly(10);
	}
}
void tx_task(void *pdata)
{
	INT8U *buffer;
	INT8U err;
	while(1)
	{	
		buffer = OSMemGet(comlink_buf,&err); 
		if(tx_queue != (OS_EVENT *)0 && buffer != NULL)
		{
			printf("txqueue ok");
	   	memset(buffer,0,USART_REC_LEN);	//清除缓冲区
			buffer = OSQPend(tx_queue,0,&err);//请求消息rx_queue			
			if(buffer != (void *)0)			//接收到消息
      { 
				USART1_Send_Data(buffer,7);	
        printf("send ok");				
      }
    }
		memset(USART_RX_BUF,0,USART_REC_LEN);
		OSMemPut(comlink_buf,buffer);		//释放内存
    OSTimeDly(10);

	}
}

void cmd_task(void *pdata)
{
	INT8U *buffer;
	INT8U err;
	while(1)
	{	 

		buffer = OSMemGet(comlink_buf,&err); 
  	if(cmd_queue != (OS_EVENT *)0 && buffer != NULL)
		{
			printf("cmdqueue ok");
	   	memset(buffer,1,USART_REC_LEN);	//清除缓冲区
			buffer = OSQPend(cmd_queue,0,&err);//请求消息rx_queue
			if(buffer != (void *)0)			//接收到消息
      { 
			 //pack_analysis();解释接收到的消息
      }
    }
		OSMemPut(comlink_buf,buffer);		//释放内存
    OSTimeDly(10);
	}	
}