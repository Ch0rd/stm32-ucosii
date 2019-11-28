#include "init.h"/*ͷ�ļ�����*/

//START ����
OS_STK START_TASK_STK[128];
//������
void start_task(void *pdata);

//LED0����
OS_STK LED0_TASK_STK[64];
//������
void led0_task(void *pdata);


int main(void)
{
	OSInit();  		//UCOS��ʼ��

	systemInit();		//�ײ�Ӳ����ʼ��	
		
	OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_TASK_STK[128-1],10); //������ʼ����
	
	OSStart(); 	//��ʼ����
		    
}

//��ʼ����
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr=0;
	
	pdata=pdata;
	
	OSStatInit();  //����ͳ������
	
	OS_ENTER_CRITICAL();  //�����ٽ���(�ر��ж�)
	
	OSTaskCreate(rx_task,(void*)0,(OS_STK*)&RX_TASK_STK[64-1],7);//�������ڽ�������

	OSTaskCreate(tx_task,(void*)0,(OS_STK*)&TX_TASK_STK[64-1],8);//�������ڷ�������		
	                          
	OSTaskCreate(cmd_task,(void*)0,(OS_STK*)&CMD_TASK_STK[64-1],9);//���������������
	
	OSTaskSuspend(10);//����ʼ����
	
	OS_EXIT_CRITICAL();  //�˳��ٽ���(���ж�)
	
}
 


