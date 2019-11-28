#include "init.h"

 void systemInit(void)
 {
	 u32 total,free;
	 delay_init();       //��ʱ��ʼ��
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //�жϷ�������
	 uart_init(9600);    //���ڲ���������
	 LED_Init();  	//LED��ʼ��
	 com_init();
	 printf("��ʼ��\n");
   exfuns_init();		//Ϊfatfs��ر��������ڴ�				 
   mem_init();			//��ʼ���ڴ��			
	 while(SD_Initialize())printf("SD Card Error!\n");					//���SD��				   				 
   f_mount(fs[0],"0:",1); 					//����SD�� 	
	 while(exf_getfree("0:",&total,&free))	printf("Fatfs Error!\n");	//�õ�SD������������ʣ������		
	 printf("FATFS OK!\n");	 
	 printf("SD Total Size: ");		    
 	 printf("%d MB\n",total>>10);					//��ʾSD�������� MB
	 printf("SD  Free Size: "); 
   printf("%d MB\n",free>>10);						//��ʾSD��ʣ������ MB	
 }