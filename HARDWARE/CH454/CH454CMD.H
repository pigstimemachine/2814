#ifndef _CH454CMD_H
#define _CH454CMD_H


#include "sys.h"

typedef unsigned char  UINT8;
typedef unsigned short UINT16;


/* CH454的常用命令码 */
#define CH454_RESET     0x0201					// 复位
#define CH454_CLR_BIT	0x0180					// 段位清0,需另加6位数据
#define CH454_SET_BIT	0x01C0					// 段位置1,需另加6位数据
#define CH454_NO_BCD    0x0500					// 设置直接译码方式   
#define CH454_TWINKLE   0x0600		            // 设置闪烁控制,需另加8位数据
#define CH454_GET_KEY	0x0700					// 获取按键,返回按键代码
#define CH454_DIG0_LO   0x0800					// 数码管位0LO显示,需另加8位数据
#define CH454_DIG1_LO   0x0900		            // 数码管位1LO显示,需另加8位数据
#define CH454_DIG2_LO   0x0a00		            // 数码管位2LO显示,需另加8位数据
#define CH454_DIG3_LO   0x0b00		            // 数码管位3LO显示,需另加8位数据
#define CH454_DIG4_LO   0x0c00		            // 数码管位4LO显示,需另加8位数据
#define CH454_DIG5_LO   0x0d00					// 数码管位5LO显示,需另加8位数据
#define CH454_DIG6_LO   0x0e00					// 数码管位6LO显示,需另加8位数据
#define CH454_DIG7_LO   0x0f00		            // 数码管位7LO显示,需另加8位数据
#define CH454_DIG0_HI   0x1000					// 数码管位0HI显示,需另加8位数据
#define CH454_DIG1_HI   0x1100		            // 数码管位1HI显示,需另加8位数据
#define CH454_DIG2_HI   0x1200		            // 数码管位2HI显示,需另加8位数据
#define CH454_DIG3_HI   0x1300		            // 数码管位3HI显示,需另加8位数据
#define CH454_DIG4_HI   0x1400		            // 数码管位4HI显示,需另加8位数据
#define CH454_DIG5_HI   0x1500					// 数码管位5HI显示,需另加8位数据
#define CH454_DIG6_HI   0x1600					// 数码管位6HI显示,需另加8位数据
#define CH454_DIG7_HI   0x1700		            // 数码管位7HI显示,需另加8位数据

// 2线接口的CH454定义
#define		CH454_I2C_ADDR		0x40			// CH454的地址
#define		CH454_I2C_MASK		0x3E			// CH454的2线接口高字节命令掩码


#define ALPHABET_NUM 37
typedef struct
{
    int num;
    char prototype;
    UINT8 DIG_H ;
    UINT8 DIG_L ;
    
}ALPHABET;



#define NoCanConnect "E01"//无通信
#define ERR "ERR"

//#include <reg52.h>

//#include <intrins.h>
//#pragma NOAREGS		// 如果MCS51使用键盘中断功能，那么建议加入此编译选项

/* 2线接口的连接,与实际电路有关 */
/*
sbit	CH454_SCL=P1^7;
sbit	CH454_SDA=P1^6;   
sbit	CH454_INT=P3^3;   
*/

#define CH454_SCL    		PAout(0) //SCL
#define CH454_SDA    		PAout(1) //SDA	 
#define CH454_READ_SDA   	PAin(1)  //输入SDA 


/* 2线接口的位操作,与单片机有关 */
#define		CH454_SCL_SET		{CH454_SCL=1;}
#define		CH454_SCL_CLR		{CH454_SCL=0;}
#define		CH454_SCL_D_OUT		{}				// 设置SCL为输出方向,对于双向I/O需切换为输出
#define		CH454_SDA_SET		{CH454_SDA=1;}
#define		CH454_SDA_CLR		{CH454_SDA=0;}
#define		CH454_SDA_IN		(CH454_SDA)
//#define		CH454_SDA_D_OUT		{}				// 设置SDA为输出方向,对于双向I/O需切换为输出
//#define		CH454_SDA_D_IN		{CH454_SDA=1;}	// 设置SDA为输入方向,对于双向I/O需切换为输入

#define CH454_SDA_D_IN  {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=0x00000080;} // 设置SDA为输入方向,对于双向I/O需切换为输入
#define CH454_SDA_D_OUT {GPIOA->CRL&=0XFFFFFF0F;GPIOA->CRL|=0x00000030;} 



/* 与单片机有关,与中断连接方式有关 */

/*
#define		USE_CH454_KEY		1			// 使用了CH454的按键中断
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


// 对外子程序
extern	UINT8 CH454_Read( UINT16 read_cmd );		//读取按键
extern  void ch454_write( UINT16 cmd );	//写命令
void CH454_Init(void);

int CharToNixieTube(char *str);

#endif
