#include "sys.h"   
#include "lib.h"
//////////////////////////////////////////////////////////////////////////////////	
#define MaxLednum          3

BLINK_PARA BlinkPara[MaxLednum];

void LED_Init(void)
{
	  RCC->APB2ENR|=1<<2;    //使能PORTA时钟	   	 

    

    GPIOA->CRL&=0XF0FFFFFF;//系统呼吸pa6
    GPIOA->CRL|=0X03000000;    
	
    memset(BlinkPara,0,sizeof(BlinkPara));
	  BlinkPara[0].LedGPIO=(u32*)&LED1;
    BlinkPara[1].LedGPIO=(u32*)&LED2;
    BlinkPara[2].LedGPIO=(u32*)&LED3;  
}

void _LED_SetTime(u8 Lednum,u16 Ontime,u16 Offtime,u16 Blinktime)
{
	  u32 Systick;
	  Systick=GetSysTick();
	  BlinkPara[Lednum].LedTick=0;
      BlinkPara[Lednum].LedonTime=Ontime;
	  BlinkPara[Lednum].LedoffTime=Offtime;
	  if(Blinktime==0)
		  BlinkPara[Lednum].BlinkTick=0XFFFFFFFF;
    else
      BlinkPara[Lednum].BlinkTick=Blinktime+Systick;
	  BlinkPara[Lednum].LedStatus=LED_STATUS_OFF;
}	

void _LED_Blink_TASK(void)
{
    u8 cnt; u32 Systick;
	  Systick=GetSysTick();
	  for(cnt=0;cnt<MaxLednum;cnt++)
	  {
       if(Systick>BlinkPara[cnt].BlinkTick)
       {
          BlinkPara[cnt].LedStatus=LED_STATUS_INIT;
          *(BlinkPara[cnt].LedGPIO)=0;
       }	 
		   switch(BlinkPara[cnt].LedStatus)
			 {
				  case LED_STATUS_ON:
					   if(Systick>BlinkPara[cnt].LedTick)
						 {
						    BlinkPara[cnt].LedStatus=LED_STATUS_OFF;
							  BlinkPara[cnt].LedTick=Systick+BlinkPara[cnt].LedoffTime;
							  *(BlinkPara[cnt].LedGPIO)=0;
						 }	 
				     break;
					case LED_STATUS_OFF:
						 if(Systick>BlinkPara[cnt].LedTick)
						 {//javascipt:;
						    BlinkPara[cnt].LedStatus=LED_STATUS_ON;
							  BlinkPara[cnt].LedTick=Systick+BlinkPara[cnt].LedonTime;
							  *(BlinkPara[cnt].LedGPIO)=1;
						 }
					   break;
					case LED_STATUS_INIT:
             
					   break;
					
			 }	 
		}
}	


void _LED_TASK10MS(void)
{
    _LED_Blink_TASK();
}	



