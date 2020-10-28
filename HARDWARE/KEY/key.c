#include  "lib.h"
#include "ShowInterface.h"


#define  FALSE 	0
#define  TRUE  	1

KEY_PARA ParaKeyLayerMinus,ParaKeyLayerAdd,ParaKeyFunLeft,ParaKeyFunRight;

extern CAN_LAYER can_layer;
void KEY_INIT (void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟
	RCC->APB2ENR|=1<<3;    //使能PORTB时钟

	GPIOA->CRL&=0XFFFFFF00;
	GPIOA->CRL|=0X00000088;
	GPIOA->ODR|=3<<0;//上拉
	
	GPIOB->CRL&=0XFFFFFF00;
	GPIOB->CRL|=0X00000088;
	GPIOB->ODR|=3<<0;//上拉
}

int TaskKeyFun(int key ,KEY_PARA *ParaKey)
{
	int KeyFun;
	switch (key)
	{
		case KeyLeft:
			KeyFun=KeyFunLeft;
			break;
		case KeyRight:
			KeyFun=KeyFunRight;
			break;
		default:
			break;
	}
	if( (KeyFun ) == ButtonPress) //按键 KEY4
	{
	 	ParaKey->sts = 1;
	 	ParaKey->time++;
		 if(ParaKey->time > PressLongTimeFlag)
		{
			ParaKey->long_flag = 1 ;
			ParaKey->cnt++ ;
			ParaKey->time=0;
		}
	} 
	else
	 {
	 	if(ParaKey->time > PressShortTimeFlag)
 		{
 			ParaKey->cnt++ ;
			ParaKey->short_flag=1;
			ParaKey->time = 0;
 		}
		else
		{
			ParaKey->sts = 0;
			ParaKey->time=0;
			ParaKey->short_flag=0;		
		}
		ParaKey->long_flag = 0 ;
	 }
}

int InterfaceChange(void)
{

	if((ParaKeyFunLeft.short_flag == 1) &&(Interface.page > 1) )
	{
		Interface.page--;
		InterfaceChangeFlag();
	}
	if((ParaKeyFunRight.short_flag == 1) &&(Interface.page < MaxPage))
	{
		Interface.page++;
		InterfaceChangeFlag();
	}
	return 0;
}

int KeyCtl(void)
{
       if( ( KeyLayerAdd ) == ButtonRelease) //按键 KEY1
       {
           ParaKeyLayerAdd.sts = 0;
       }
       if( (KeyLayerMinus ) == ButtonRelease) //按键 KEY2
       {
           ParaKeyLayerMinus.sts = 0;
       }
	   TaskKeyFun(KeyLeft,&ParaKeyFunLeft);
	   TaskKeyFun(KeyRight,&ParaKeyFunRight);
	InterfaceChange();
    return 0;   
}
//按键按下去会出现下降沿，设置按键IO口所在的外部端口为下降沿触发中断。
void EXTIX_Init(void)
{
    KEY_INIT();
    Ex_NVIC_Config(GPIO_B,0,FTIR);//FTIR 下降沿触发 RTIR 上升沿触发
    Ex_NVIC_Config(GPIO_B,1,FTIR);//FTIR 下降沿触发 RTIR 上升沿触发
    //Ex_NVIC_Config(GPIO_A,0,FTIR);//FTIR 下降沿触发 RTIR 上升沿触发
    //Ex_NVIC_Config(GPIO_A,1,FTIR);//FTIR 下降沿触发 RTIR 上升沿触发    
    MY_NVIC_Init(2,0,EXTI0_IRQChannel,2);//抢占2，子优先级0，组2
    MY_NVIC_Init(2,1,EXTI1_IRQChannel,2);//抢占2，子优先级0，组2
 
}

/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	两键同时按下焊层置1
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/06/ Create
  * @Version 	1.0 2020/07/09
  *		     	1.1 2020/07/09 change sth
  * @Note  
  
  **/
int doublekey_press_process(void)
{
    if( (ParaKeyLayerAdd.sts == PressDown) && ( ParaKeyLayerMinus.sts == PressDown ) )
    {
        if((can_layer.rcv_sts == 1) && (can_layer.send_sts == SendDataSUCC))
        {
            can_layer.layer =1 ;
            can_layer.send_sts =NeedToSendData;             
        }        
    }
    return 0;
}


/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	长按右键检测
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/06/ Create
  * @Version 	1.0 2020/07/09
  *		     	1.1 2020/07/09 change sth
  * @Note  
  
  **/
int RightKey_LongPress_Process(void)
{
    static int layer_time ;
    if( ParaKeyLayerAdd.sts == PressDown )
    {
        ParaKeyLayerAdd.time ++ ;
		
    }
    else
    {
        ParaKeyLayerAdd.time  = 0 ;
    }
    if( ParaKeyLayerAdd.time > LongPressTimeSts )
    {
        layer_time++;
        if( layer_time > ButtonChangeSpeed )
        {
             if( (can_layer.rcv_sts == 1 ) && (can_layer.send_sts == SendDataSUCC ) )
             {
                 can_layer.layer++;
                 if(can_layer.layer >= can_layer.max_layer)
                {
                    can_layer.layer= can_layer.max_layer ;
                } 
                can_layer.send_sts =NeedToSendData;                
             }
             layer_time =0;
        }
        else
        {
          //  ParaKeyLayerAdd.time = 0 ;
        }
    } 
    return 0 ;
}
/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	长按左键检测
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/06/ Create
  * @Version 	1.0 2020/07/09
  *		     	1.1 2020/07/09 change sth
  * @Note  
  
  **/

int LeftKey_LongPress_Process(void)
{
    static int layer_time ;
    if( ParaKeyLayerMinus.sts == PressDown )
    {
        ParaKeyLayerMinus.time ++ ;
    }
    else
    {
        ParaKeyLayerMinus.time  = 0 ;
    }
    if( ParaKeyLayerMinus.time > LongPressTimeSts )
    {
        layer_time++;
        if( layer_time > ButtonChangeSpeed )
        {
             if( (can_layer.rcv_sts == 1 ) && (can_layer.send_sts == SendDataSUCC ) )
             {
                 can_layer.layer--;
                 if(can_layer.layer <= 1)
                {
                    can_layer.layer=1;
                } 
                can_layer.send_sts =NeedToSendData;                
             }
             layer_time =0;
        }
        else
        {
          //  ParaKeyLayerMinus.time = 0 ;
        }
    }    
    return 0 ;
}
int RightKeyProcess(void)
{
    if( ( KeyLayerAdd ) == ButtonPress) //按键right KEY2
    {
		ParaKeyLayerAdd.sts = 1;
        ParaKeyLayerAdd.cnt++;
        if( (can_layer.rcv_sts == 1 ) && can_layer.send_sts == SendDataSUCC )
        {
            can_layer.layer++;
            if( can_layer.layer > can_layer.max_layer )
            {
                can_layer.layer =  can_layer.max_layer;
            }
            can_layer.send_sts =NeedToSendData;            
        }            

    }
        return 0;
}
void EXTI0_IRQHandler(void)
{
    delay_ms(10);
    RightKeyProcess();
 //   EXTI_ClearITPendingBit(EXTI_Line2); //清除 LINE2 上的中断标志位
    EXTI->PR=1<<0;
}
int LeftKeyProcess()
{
     if( (KeyLayerMinus ) == ButtonPress) //按键 KEY2
    {
		ParaKeyLayerMinus.sts = 1;
        ParaKeyLayerMinus.cnt++;
        
        if((can_layer.rcv_sts == 1) && (can_layer.send_sts == SendDataSUCC))
        {
            can_layer.layer--;
            if(can_layer.layer <= 1)
            {
                can_layer.layer=1;
            }
            can_layer.send_sts =NeedToSendData;             
        }
     
    }   
    return 0;
}

void EXTI1_IRQHandler(void)
{
    delay_ms(10);
    LeftKeyProcess();
 //   EXTI_ClearITPendingBit(EXTI_Line2); //清除 LINE2 上的中断标志位
    EXTI->PR=1<<1;
}



//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
/*
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //按键按松开标志
    if(mode)
        key_up = 1; //支持连按

    if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
    {
        delay_ms(10);//去抖动
        key_up = 0;

        if(KEY0 == 0)
            return 1;
        else if(KEY1 == 0)
            return 2;
        else if(KEY2 == 0)
            return 3;
        else if(WK_UP == 1)
            return 4;
    }
    else if(KEY0 == 1 && KEY1 == 1 && KEY2 == 1 && WK_UP == 0)key_up = 1;
    return 0;// 无按键按下
}
*/
/*
void TIM3_IRQHandler(void) //TIM3 中断
{
   
    static u16 keyupCnt = 0;//按键弹起后计数值
	static u16 key_holdon_ms = 0;//按下的时长
	u16 keyUpFlag = TRUE;//按键弹起标志
	
    if(TIM3->SR&0X01)//是更新中断
	{	 		   

		TIM3->SR&=~(1<<0);		//清除中断标志位		   
	


        if(key_fall_flag == 1) //发生按键按下事件
        {
            if( (PBin(0) ) == 0) //按键持续按下
            {
				
                if(key_holdon_ms <= 2000)
                {
                    key_holdon_ms++;
                }
				else if(key_holdon_ms > 2000) //按键按下到2000ms就判断长按时间成立，生成长按标志
                {
                    key_holdon_ms = 0;	//清除时间单位
                    short_key_flag = 0; //清短按键标志
                    key_long_down = 1;  //长按键标志置位
                    key_fall_flag = 0;  //清按键按下标志
					keyUpFlag = FALSE;  //标记按下
					keyupCnt = 0;
				//	LED1 = ~LED1;
                }
				 //距离上次单击时间在100~500ms之间，则认为发生连击事件
				if((keyupCnt > 300) && (keyupCnt < 500))
				{
					keyupCnt = 0;
					doubleClick = 1;	//标记发生了连击事件
					//BEEP = ~BEEP;
				}
			
            }
            else //按键抬起
            {
				
				keyupCnt = 0;
                if(key_holdon_ms > 50) //按下时间大于50ms，生成单击标志
                {
                    key_holdon_ms = 0;
                    short_key_flag = 1;	//标记短按标志
                    key_long_down = 0;	//清除长按标志
                    key_fall_flag = 0;
					//LED0 = ~LED0;
					keyupCnt = 0;
                
					//距离上次单击时间在100~500ms之间，则认为发生连击事件
					if(keyupCnt>100 && keyupCnt<500)
					{ 
					   doubleClick = TRUE;
					   short_key_flag=0;
					} 
					keyUpFlag = TRUE;//单击抬起按键后，生成按键抬起标志 
			  }
                else  //按键持续时间小于50ms，忽略
                {
                    key_holdon_ms = 0;//按键按下时间的位
                    short_key_flag = 0;//短按
                    key_long_down = 0;//长按标志
                    key_fall_flag = 0;//按键按下标志
					keyupCnt = 0;
                }
				
            }

        }

        if(keyUpFlag)//单击抬起后，启动计数，计数到500ms
            keyupCnt++;

        if(keyupCnt > 500)
        {
            keyupCnt = 0;
            keyUpFlag = FALSE;//标记为弹起
        }

    }

}
*/






