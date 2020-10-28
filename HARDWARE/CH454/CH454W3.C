/* ***************************
 Website:  http://wch.cn
 Email:    tech@wch.cn
 Author:   W.ch 2008.7
******************************/
//#include	"PIN.H"			// �޸ĸ��ļ�����ӦӲ������/��Ƭ���ͺŵ�
#include	"CH454CMD.H"	// CH454��������
#include <string.h>
//#include <INTRINS.h>

//#define DELAY  { _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_(); }
#define DELAY 	{__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");}




ALPHABET alphabet[ALPHABET_NUM] = { 
    
    {0,'0',0x00,0x3f},
    {1,'1',0x00,0x06},
    {2,'2',0x00,0xdb},
    {3,'3',0x00,0xcf},
    {4,'4',0x00,0xe6},
    {5,'5',0x00,0xed},
    {6,'6',0x00,0xfd},
    {7,'7',0x00,0x07},
    {8,'8',0x00,0xff},
    {9,'9',0x00,0xef},
    
    {10,'.',0x40,0x00},
    
    {11,'A',0x00,0xf7}, 
    {12,'B',0X00,0XFC},
    {13,'C',0X00,0X39},//0xd8
    {14,'D',0X00,0XDE},
    {15,'E',0X00,0XF9},
    {16,'F',0X00,0XF1},
    {17,'G',0x00,0xbd},
    {18,'H',0x00,0xf6},
    {19,'I',0x12,0x09},
    {20,'J',0x12,0x19},
    {21,'K',0x0c,0x70},
    {22,'L',0x00,0x38},
    {23,'M',0x05,0x36},
    {24,'N',0x09,0x36},
    {25,'O',0x00,0xdc},
    {26,'P',0x00,0xf3},
    {27,'Q',0x08,0x3f},
    {28,'R',0x08,0x73},
    {29,'S',0x00,0xed},
    {30,'T',0x12,0x01},
    {31,'U',0x00,0x3e},
    {32,'V',0x05,0x00},
    {33,'W',0x28,0x36},
    {34,'X',0x2d,0x00},
    {35,'Y',0x15,0x00},
    {36,'Z',0x24,0x09},  
};


/**

  * @brief   	�ַ���ת�������ʾ
  * @Name	 	int main Name ( void sth)
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/05/22 Create
  * @Version 	1.0 2020/05/22  
  *		     	1.1 2020/05/22 change sth
  * @Note  
  
  **/

int CharToNixieTube(char* str)
{
    char Tube1;
    char Tube2;
    char Tube3;
	int cnt,len;
	len = strlen(str);
    Tube1 = str[0] ;
    Tube2 = str[1] ;
    Tube3 = str[2] ;
	ch454_write(0x441);//����ʾ
	for(cnt=0;cnt<ALPHABET_NUM;cnt++)
	{
		 if( Tube1 == alphabet[cnt].prototype )  
		 	{
			    ch454_write( CH454_DIG0_LO | alphabet[cnt].DIG_L );
		    	ch454_write( CH454_DIG0_HI | alphabet[cnt].DIG_H ); 
				cnt=ALPHABET_NUM;
				break;
		 	}
	}
	for(cnt=0;cnt<ALPHABET_NUM;cnt++)
	{
		 if( Tube2 == alphabet[cnt].prototype  )  
		 	{
			    ch454_write( CH454_DIG1_LO | alphabet[cnt].DIG_L );
		    	ch454_write( CH454_DIG1_HI | alphabet[cnt].DIG_H ); 
				cnt=ALPHABET_NUM;
				break;
		 	}
	}
	for(cnt=0;cnt<ALPHABET_NUM;cnt++)
	{
		 if( Tube3 == alphabet[cnt].prototype  )  
		 	{
			    ch454_write( CH454_DIG2_LO | alphabet[cnt].DIG_L );
		    	ch454_write( CH454_DIG2_HI | alphabet[cnt].DIG_H ); 
				cnt=ALPHABET_NUM;
				break;
		 	}
	}
	if( len == 1 )
	{
			ch454_write( CH454_DIG1_LO );
			ch454_write( CH454_DIG1_HI );	
			ch454_write( CH454_DIG2_LO );
			ch454_write( CH454_DIG2_HI );					
	}
	if( len == 2 )
	{	
		    ch454_write( CH454_DIG2_LO );
	    	ch454_write( CH454_DIG2_HI );					
	}	
	return 0;
}

/**

 DP   M 	L 	K 	 J 	  I 	H 	  G2 	 G1 	F 	E 	 D 	  C    B 	A 
XSG6 XSG5 XSG4 XSG3 XSG2 XSG1 XSG0   SEG7   SEG6  SEG5 SEG4 SEG3 SEG2 SEG1 SEG01
0000000111001

*/


//UINT8 mBCD[16] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 
//	  		   	   0x77, 0x7c, 0x58, 0x5e, 0x79, 0x71 };//BCD
UINT8 mBCD[19] = { 0x3f, 0x06, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0x07, 0xff, 0xef, //0-9
	  		   	   0xf7, 0xfc, 0xd8, 0xde, 0xf9, 0xf1,  //a-f
                  0xbd , 0xf6, 0x09//g-h
};//


UINT8 ch454_key = 0xff;//������ֵ

void delayms( UINT8 i )//��ʱmS
{	
    UINT16	j;
	do
	{	
	    for( j = 0; j != 1000; j++ )
		{
		   ;
		}
	}
	while( --i );
}

void CH454_Init(void)
{		
	RCC->APB2ENR|=1<<2;//��ʹ������IO PORTAʱ�� 							 
	GPIOA->CRL&=0XFFFFFF00;//PA0 1 �������
	GPIOA->CRL|=0X00000033;	   
	GPIOA->ODR|=3<<0;     // �����  
    
 
     ch454_write(0x441);//����ʾDDD
     ch454_write(CH454_NO_BCD);//ֱ�����뷽ʽ

//  ch454_write(0x0201);//оƬ�ڲ���λ
////  ch451_write(0x0202);//����˯��״̬
//  ch454_write(0x0401);//�ؿ��Ź�������ʾɨ��
//  ch454_write(0x0500);//�����룬ɨ�輫��8���Զ�8/16
//  ch454_write(0x0600);//����˸��ʾ    
}

void CH454_I2c_Start( void )  // ������ʼ
{
	DISABLE_KEY_INTERRUPT;  //��ֹ�����ж�,��ֹ��ʼʱ��CH454�ж϶������жϷ�������е�START
	CH454_SDA_SET;   /*������ʼ�����������ź�*/
    CH454_SDA_D_OUT;   /* ����SDAΪ������� */
	DELAY;
	CH454_SCL_SET;
    CH454_SCL_D_OUT;   /* ����SCLΪ������� */
	DELAY;

	CH454_SDA_CLR;   /*������ʼ�ź�*/
	DELAY;    

	CH454_SCL_CLR;   /*ǯסI2C���ߣ�׼�����ͻ�������� */
	DELAY;	
}

void CH454_I2c_Stop( void )  // ��������
{
	CH454_SDA_CLR;
    CH454_SDA_D_OUT;   /* ����SDAΪ������� */
	DELAY;

	CH454_SCL_SET;
	DELAY;

	CH454_SDA_SET;  /*����I2C���߽����ź�*/
	DELAY;

    CH454_SDA_D_IN;   /* ����SDAΪ���뷽�� */
    DELAY;

  	ENABLE_KEY_INTERRUPT;
}

void CH454_I2c_WrByte( UINT8 dat )	//дһ���ֽ�����
{
	UINT8 i;
	CH454_SDA_D_OUT;   /* ����SDAΪ������� */
	DELAY;

	for( i = 0; i != 8; i++ )  // ���8λ����
	{
		if( dat & 0x80 ) 
		{
		    CH454_SDA_SET;
		}
		else 
		{
		    CH454_SDA_CLR;
		}
		DELAY;

		CH454_SCL_SET;
		dat <<= 1;
		DELAY;

		CH454_SCL_CLR;
		DELAY;
	}
	CH454_SDA_D_IN;   /* ����SDAΪ���뷽�� */
    CH454_SDA_SET;
	DELAY;

	CH454_SCL_SET;  // ����Ӧ��
	DELAY;

	CH454_SCL_CLR;
	DELAY;
}

UINT8  CH454_I2c_RdByte( void )		//��һ���ֽ�����
{
	UINT8 dat,i;
    CH454_SDA_SET;
	CH454_SDA_D_IN;   /* ����SDAΪ���뷽�� */
    DELAY;

	dat = 0;
	for( i = 0; i != 8; i++ )  // ����8λ����
	{
		CH454_SCL_SET;
		DELAY;

		dat <<= 1;
		if( CH454_SDA_IN ) dat++;  // ����1λ

		CH454_SCL_CLR;
		DELAY;
	}

	CH454_SDA_SET;
    
	DELAY;

	CH454_SCL_SET;  // ������ЧӦ��

	DELAY;

	CH454_SCL_CLR;
	DELAY;

	return dat;
}

void ch454_write( UINT16 cmd )	//д����
{
	CH454_I2c_Start();               /*��������*/

   	CH454_I2c_WrByte((UINT8)(cmd>>7)&CH454_I2C_MASK|CH454_I2C_ADDR); 

   	CH454_I2c_WrByte((UINT8)cmd);     /*��������*/
  	CH454_I2c_Stop();                 /*��������*/ 
}




/*
��CH454pdf�ĵ�5ҳ�Ĳ�����������趨ϵͳ������Ϊ����λ12-λ9 ��0x04�� 
����ch454_write��������0x0401���������CH454����һ���ֽ���0x04���ڶ����ֽ���0x01�� 
ch454_write�������ȵ���CH454_I2c_WrByte�����͵�һ���ֽڣ� 
CH454_I2c_WrByte((UINT8)(cmd>>7)&CH454_I2C_MASK|CH454_I2C_ADDR); 
����CH454pdf�ĵ�4ҳβ��ʱ��ͼ��������((UINT8)(cmd>>7)&CH454_I2C_MASK|CH454_I2C_ADDR����任��
ʵ�ʷ��͵Ĳ�������ĵ�һ���ֽ�0x04��Ϊ0x48 
����ʵ�ʷ��͵Ĳ���������0x4801��

*/
UINT8 CH454_Read( UINT16 read_cmd )		//��ȡ����
{
	UINT8 keycode;
   	CH454_I2c_Start();                /*��������*/

	CH454_I2c_WrByte((UINT8)(read_cmd>>7)&CH454_I2C_MASK|CH454_I2C_ADDR|0x01);
	
   	keycode = CH454_I2c_RdByte();      /*��ȡ����*/
	CH454_I2c_Stop();                /*��������*/ 

	return keycode;
}


/*
void init( void )//��ʼ��
{	
	IE1 = 0;
	EX1 = 1;
	EA = 1;
}
*/

// INT1�жϷ������
/*
void int1( void ) interrupt 2 using 1
{
	ch454_key = CH454_Read( 0x0700 );  
}

*/
void TEST( void )//������
{
   UINT8 a,b;
   UINT8 vL[4],vH[4];

   delayms(40);

#ifdef USE_CH454_KEY
   init();//��ʼ��
   ch454_write(0x443);//����ʾ����
#else
   ch454_write(0x441);//����ʾ
#endif

   ch454_write(CH454_NO_BCD);//ֱ�����뷽ʽ   
  
   //������ʾ����
   ch454_write( CH454_DIG0_LO | mBCD[0] );
   ch454_write( CH454_DIG1_LO | mBCD[1] ); 
   ch454_write( CH454_DIG2_LO | mBCD[2] ); 
   ch454_write( CH454_DIG3_LO | mBCD[3] );
   ch454_write( CH454_DIG4_LO | mBCD[4] );
   ch454_write( CH454_DIG5_LO | mBCD[5] );
   ch454_write( CH454_DIG6_LO | mBCD[6] );
   ch454_write( CH454_DIG7_LO | mBCD[7] );
   ch454_write( CH454_DIG0_HI | mBCD[8] );
   ch454_write( CH454_DIG1_HI | mBCD[9] ); 
   ch454_write( CH454_DIG2_HI | mBCD[10] );
   ch454_write( CH454_DIG3_HI | mBCD[11] );
   ch454_write( CH454_DIG4_HI | mBCD[12] );
   ch454_write( CH454_DIG5_HI | mBCD[13] );
   ch454_write( CH454_DIG6_HI | mBCD[14] );
   ch454_write( CH454_DIG7_HI | mBCD[15] );

   delayms(240);
         
#ifdef USE_CH454_KEY
   //��ʾ0
   ch454_write( CH454_DIG0_LO | mBCD[0]);
   ch454_write( CH454_DIG1_LO | mBCD[0]); 
   ch454_write( CH454_DIG2_LO | mBCD[0]); 
   ch454_write( CH454_DIG3_LO | mBCD[0]);
   ch454_write( CH454_DIG4_LO | mBCD[0]);
   ch454_write( CH454_DIG5_LO | mBCD[0]);
   ch454_write( CH454_DIG6_LO | mBCD[0]);
   ch454_write( CH454_DIG7_LO | mBCD[0]);
   ch454_write( CH454_DIG0_HI );
   ch454_write( CH454_DIG1_HI ); 
   ch454_write( CH454_DIG2_HI );
   ch454_write( CH454_DIG3_HI );
   ch454_write( CH454_DIG4_HI );
   ch454_write( CH454_DIG5_HI );
   ch454_write( CH454_DIG6_HI );
   ch454_write( CH454_DIG7_HI );
   vL[0]=0; 
   vL[1]=0; 
   vL[2]=0; 
   vL[3]=0;
   vH[0]=0; 
   vH[1]=0; 
   vH[2]=0; 
   vH[3]=0;
 
   while(1)
   {
       ch454_key = 0xff;
       while( ch454_key == 0xff );	                //�ȴ��ж�

       a = ch454_key & 0x3F;//������ֵ	            
       b = a;//ת��ʮ��������
       a /= 10;//ʮλ
	   b %= 10;//��λ

	   //��λ
	   vL[3] = vL[2]; vL[2] = vL[1]; vL[1] = vL[0]; vL[0] = a;
	   vH[3] = vH[2]; vH[2] = vH[1]; vH[1] = vH[0]; vH[0] = b;
       ch454_write( CH454_DIG1_LO | mBCD[vL[0]] );
       ch454_write( CH454_DIG0_LO | mBCD[vH[0]] );
       ch454_write( CH454_DIG3_LO | mBCD[vL[1]] );
       ch454_write( CH454_DIG2_LO | mBCD[vH[1]] );
	   ch454_write( CH454_DIG5_LO | mBCD[vL[2]] );
       ch454_write( CH454_DIG4_LO | mBCD[vH[2]] );
	   ch454_write( CH454_DIG7_LO | mBCD[vL[3]] );
       ch454_write( CH454_DIG6_LO | mBCD[vH[3]] );

	   while(1)
	   {
			
		    a = CH454_Read( 0x0700 );
			if( a & 0x40 )//δ�ͷ�
			{
                    	ch454_write( CH454_TWINKLE | 0x07 );//ȫ��˸
				ch454_write( CH454_TWINKLE | 0x03 );//ȫ��˸
			}
			else//�ͷ�
			{
				ch454_write( CH454_TWINKLE );//ȫ����˸
			    break;
			}
		}
   }
#else
   while(1);
#endif
}
