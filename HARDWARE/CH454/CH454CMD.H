#ifndef _CH454CMD_H
#define _CH454CMD_H


#include "sys.h"

typedef unsigned char  UINT8;
typedef unsigned short UINT16;


/* CH454�ĳ��������� */
#define CH454_RESET     0x0201					// ��λ
#define CH454_CLR_BIT	0x0180					// ��λ��0,������6λ����
#define CH454_SET_BIT	0x01C0					// ��λ��1,������6λ����
#define CH454_NO_BCD    0x0500					// ����ֱ�����뷽ʽ   
#define CH454_TWINKLE   0x0600		            // ������˸����,������8λ����
#define CH454_GET_KEY	0x0700					// ��ȡ����,���ذ�������
#define CH454_DIG0_LO   0x0800					// �����λ0LO��ʾ,������8λ����
#define CH454_DIG1_LO   0x0900		            // �����λ1LO��ʾ,������8λ����
#define CH454_DIG2_LO   0x0a00		            // �����λ2LO��ʾ,������8λ����
#define CH454_DIG3_LO   0x0b00		            // �����λ3LO��ʾ,������8λ����
#define CH454_DIG4_LO   0x0c00		            // �����λ4LO��ʾ,������8λ����
#define CH454_DIG5_LO   0x0d00					// �����λ5LO��ʾ,������8λ����
#define CH454_DIG6_LO   0x0e00					// �����λ6LO��ʾ,������8λ����
#define CH454_DIG7_LO   0x0f00		            // �����λ7LO��ʾ,������8λ����
#define CH454_DIG0_HI   0x1000					// �����λ0HI��ʾ,������8λ����
#define CH454_DIG1_HI   0x1100		            // �����λ1HI��ʾ,������8λ����
#define CH454_DIG2_HI   0x1200		            // �����λ2HI��ʾ,������8λ����
#define CH454_DIG3_HI   0x1300		            // �����λ3HI��ʾ,������8λ����
#define CH454_DIG4_HI   0x1400		            // �����λ4HI��ʾ,������8λ����
#define CH454_DIG5_HI   0x1500					// �����λ5HI��ʾ,������8λ����
#define CH454_DIG6_HI   0x1600					// �����λ6HI��ʾ,������8λ����
#define CH454_DIG7_HI   0x1700		            // �����λ7HI��ʾ,������8λ����

// 2�߽ӿڵ�CH454����
#define		CH454_I2C_ADDR		0x40			// CH454�ĵ�ַ
#define		CH454_I2C_MASK		0x3E			// CH454��2�߽ӿڸ��ֽ���������


#define ALPHABET_NUM 37
typedef struct
{
    int num;
    char prototype;
    UINT8 DIG_H ;
    UINT8 DIG_L ;
    
}ALPHABET;



#define NoCanConnect "E01"//��ͨ��
#define ERR "ERR"

//#include <reg52.h>

//#include <intrins.h>
//#pragma NOAREGS		// ���MCS51ʹ�ü����жϹ��ܣ���ô�������˱���ѡ��

/* 2�߽ӿڵ�����,��ʵ�ʵ�·�й� */
/*
sbit	CH454_SCL=P1^7;
sbit	CH454_SDA=P1^6;   
sbit	CH454_INT=P3^3;   
*/

#define CH454_SCL    		PAout(0) //SCL
#define CH454_SDA    		PAout(1) //SDA	 
#define CH454_READ_SDA   	PAin(1)  //����SDA 


/* 2�߽ӿڵ�λ����,�뵥Ƭ���й� */
#define		CH454_SCL_SET		{CH454_SCL=1;}
#define		CH454_SCL_CLR		{CH454_SCL=0;}
#define		CH454_SCL_D_OUT		{}				// ����SCLΪ�������,����˫��I/O���л�Ϊ���
#define		CH454_SDA_SET		{CH454_SDA=1;}
#define		CH454_SDA_CLR		{CH454_SDA=0;}
#define		CH454_SDA_IN		(CH454_SDA)
//#define		CH454_SDA_D_OUT		{}				// ����SDAΪ�������,����˫��I/O���л�Ϊ���
//#define		CH454_SDA_D_IN		{CH454_SDA=1;}	// ����SDAΪ���뷽��,����˫��I/O���л�Ϊ����

#define CH454_SDA_D_IN  {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=0x00000080;} // ����SDAΪ���뷽��,����˫��I/O���л�Ϊ����
#define CH454_SDA_D_OUT {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=0x00000030;} 



/* �뵥Ƭ���й�,���ж����ӷ�ʽ�й� */

/*
#define		USE_CH454_KEY		1			// ʹ����CH454�İ����ж�
#ifdef USE_CH454_KEY
#define		DISABLE_KEY_INTERRUPT	{EX1=0;}
#define		ENABLE_KEY_INTERRUPT	{EX1=1;}
#define		CLEAR_KEY_INTER_FLAG	{IE1=0;}
#else
*/

#define		DISABLE_KEY_INTERRUPT	{}
#define		ENABLE_KEY_INTERRUPT	{}
#define		CLEAR_KEY_INTER_FLAG	{}
//#endif

// #endif   


// �����ӳ���
extern	UINT8 CH454_Read( UINT16 read_cmd );		//��ȡ����
extern  void ch454_write( UINT16 cmd );	//д����
void CH454_Init(void);

int CharToNixieTube(char *str);

#endif