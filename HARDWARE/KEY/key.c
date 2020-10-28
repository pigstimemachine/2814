#include  "lib.h"
#include "ShowInterface.h"


#define  FALSE 	0
#define  TRUE  	1

KEY_PARA ParaKeyLayerMinus,ParaKeyLayerAdd,ParaKeyFunLeft,ParaKeyFunRight;

extern CAN_LAYER can_layer;
void KEY_INIT (void)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ��

	GPIOA->CRL&=0XFFFFFF00;
	GPIOA->CRL|=0X00000088;
	GPIOA->ODR|=3<<0;//����
	
	GPIOB->CRL&=0XFFFFFF00;
	GPIOB->CRL|=0X00000088;
	GPIOB->ODR|=3<<0;//����
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
	if( (KeyFun ) == ButtonPress) //���� KEY4
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
       if( ( KeyLayerAdd ) == ButtonRelease) //���� KEY1
       {
           ParaKeyLayerAdd.sts = 0;
       }
       if( (KeyLayerMinus ) == ButtonRelease) //���� KEY2
       {
           ParaKeyLayerMinus.sts = 0;
       }
	   TaskKeyFun(KeyLeft,&ParaKeyFunLeft);
	   TaskKeyFun(KeyRight,&ParaKeyFunRight);
	InterfaceChange();
    return 0;   
}
//��������ȥ������½��أ����ð���IO�����ڵ��ⲿ�˿�Ϊ�½��ش����жϡ�
void EXTIX_Init(void)
{
    KEY_INIT();
    Ex_NVIC_Config(GPIO_B,0,FTIR);//FTIR �½��ش��� RTIR �����ش���
    Ex_NVIC_Config(GPIO_B,1,FTIR);//FTIR �½��ش��� RTIR �����ش���
    //Ex_NVIC_Config(GPIO_A,0,FTIR);//FTIR �½��ش��� RTIR �����ش���
    //Ex_NVIC_Config(GPIO_A,1,FTIR);//FTIR �½��ش��� RTIR �����ش���    
    MY_NVIC_Init(2,0,EXTI0_IRQChannel,2);//��ռ2�������ȼ�0����2
    MY_NVIC_Init(2,1,EXTI1_IRQChannel,2);//��ռ2�������ȼ�0����2
 
}

/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	����ͬʱ���º�����1
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
  * @Name	 	�����Ҽ����
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
  * @Name	 	����������
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
    if( ( KeyLayerAdd ) == ButtonPress) //����right KEY2
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
 //   EXTI_ClearITPendingBit(EXTI_Line2); //��� LINE2 �ϵ��жϱ�־λ
    EXTI->PR=1<<0;
}
int LeftKeyProcess()
{
     if( (KeyLayerMinus ) == ButtonPress) //���� KEY2
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
 //   EXTI_ClearITPendingBit(EXTI_Line2); //��� LINE2 �ϵ��жϱ�־λ
    EXTI->PR=1<<1;
}



//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2����
//4��WKUP���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>WK_UP!!
/*
u8 KEY_Scan(u8 mode)
{
    static u8 key_up = 1; //�������ɿ���־
    if(mode)
        key_up = 1; //֧������

    if(key_up && (KEY0 == 0 || KEY1 == 0 || KEY2 == 0 || WK_UP == 1))
    {
        delay_ms(10);//ȥ����
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
    return 0;// �ް�������
}
*/
/*
void TIM3_IRQHandler(void) //TIM3 �ж�
{
   
    static u16 keyupCnt = 0;//������������ֵ
	static u16 key_holdon_ms = 0;//���µ�ʱ��
	u16 keyUpFlag = TRUE;//���������־
	
    if(TIM3->SR&0X01)//�Ǹ����ж�
	{	 		   

		TIM3->SR&=~(1<<0);		//����жϱ�־λ		   
	


        if(key_fall_flag == 1) //�������������¼�
        {
            if( (PBin(0) ) == 0) //������������
            {
				
                if(key_holdon_ms <= 2000)
                {
                    key_holdon_ms++;
                }
				else if(key_holdon_ms > 2000) //�������µ�2000ms���жϳ���ʱ����������ɳ�����־
                {
                    key_holdon_ms = 0;	//���ʱ�䵥λ
                    short_key_flag = 0; //��̰�����־
                    key_long_down = 1;  //��������־��λ
                    key_fall_flag = 0;  //�尴�����±�־
					keyUpFlag = FALSE;  //��ǰ���
					keyupCnt = 0;
				//	LED1 = ~LED1;
                }
				 //�����ϴε���ʱ����100~500ms֮�䣬����Ϊ���������¼�
				if((keyupCnt > 300) && (keyupCnt < 500))
				{
					keyupCnt = 0;
					doubleClick = 1;	//��Ƿ����������¼�
					//BEEP = ~BEEP;
				}
			
            }
            else //����̧��
            {
				
				keyupCnt = 0;
                if(key_holdon_ms > 50) //����ʱ�����50ms�����ɵ�����־
                {
                    key_holdon_ms = 0;
                    short_key_flag = 1;	//��Ƕ̰���־
                    key_long_down = 0;	//���������־
                    key_fall_flag = 0;
					//LED0 = ~LED0;
					keyupCnt = 0;
                
					//�����ϴε���ʱ����100~500ms֮�䣬����Ϊ���������¼�
					if(keyupCnt>100 && keyupCnt<500)
					{ 
					   doubleClick = TRUE;
					   short_key_flag=0;
					} 
					keyUpFlag = TRUE;//����̧�𰴼������ɰ���̧���־ 
			  }
                else  //��������ʱ��С��50ms������
                {
                    key_holdon_ms = 0;//��������ʱ���λ
                    short_key_flag = 0;//�̰�
                    key_long_down = 0;//������־
                    key_fall_flag = 0;//�������±�־
					keyupCnt = 0;
                }
				
            }

        }

        if(keyUpFlag)//����̧�������������������500ms
            keyupCnt++;

        if(keyupCnt > 500)
        {
            keyupCnt = 0;
            keyUpFlag = FALSE;//���Ϊ����
        }

    }

}
*/






