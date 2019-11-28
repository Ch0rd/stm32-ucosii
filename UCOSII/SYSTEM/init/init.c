#include "init.h"

 void systemInit(void)
 {
	 u32 total,free;
	 delay_init();       //延时初始化
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //中断分组配置
	 uart_init(9600);    //串口波特率设置
	 LED_Init();  	//LED初始化
	 com_init();
	 printf("初始化\n");
   exfuns_init();		//为fatfs相关变量申请内存				 
   mem_init();			//初始化内存池			
	 while(SD_Initialize())printf("SD Card Error!\n");					//检测SD卡				   				 
   f_mount(fs[0],"0:",1); 					//挂载SD卡 	
	 while(exf_getfree("0:",&total,&free))	printf("Fatfs Error!\n");	//得到SD卡的总容量和剩余容量		
	 printf("FATFS OK!\n");	 
	 printf("SD Total Size: ");		    
 	 printf("%d MB\n",total>>10);					//显示SD卡总容量 MB
	 printf("SD  Free Size: "); 
   printf("%d MB\n",free>>10);						//显示SD卡剩余容量 MB	
 }