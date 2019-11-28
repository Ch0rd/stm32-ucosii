#ifndef __COMLINK_H
#define __COMLINK_H	 



#include "usart.h"

/*ucosii相关头文件*/
#include "includes.h"



extern OS_EVENT *rx_queue;
extern OS_EVENT *tx_queue;
extern OS_EVENT *cmd_queue;

extern void *rx_message[USART_REC_LEN];
extern void *tx_message[USART_REC_LEN];
extern void *cmd_message[USART_REC_LEN];

extern OS_STK RX_TASK_STK[64];
extern OS_STK TX_TASK_STK[64];
extern OS_STK CMD_TASK_STK[64];


void com_init(void);
void rx_task(void *pdata);
void tx_task(void *pdata);
void cmd_task(void *pdata);
#endif
