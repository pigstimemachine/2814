#ifndef __KEY_H__
#define __KEY_H__


#define PB0_ON  (!(PBin(0)))
#define PB0_OFF (PBin(0))

#define PB1_ON  (!(PBin(1)))
#define PB1_OFF (PBin(1))

#define PA0_ON  (!(PAin(0)))
#define PA0_OFF (PAin(0))

#define PA1_ON  (!(PAin(1)))
#define PA1_OFF (PAin(1))

/*下面方式是通过位带操作方式读取IO*/

#define KEY1 		(PBin(0))  //焊层右键 	
#define KEY2 		(PBin(1))	//焊层左键	
#define KEY3 		(PAin(0))   //界面右键	
#define KEY4 		(PAin(1))		//界面左键


#define KeyLayerAdd		KEY1
#define KeyLayerMinus	KEY2
#define KeyFunRight		KEY3
#define	KeyFunLeft		KEY4

#define ButtonRelease	1//
typedef struct
{
    int sts;
    int short_flag;
    int long_flag;
    int cnt;
    int time;
    int DoubleClick;
}KEY_PARA;

#define PressDown 1
#define LongPressTimeSts 1000
#define ButtonChangeSpeed 250


#define KEY0_PRES 	1
#define KEY1_PRES	2
#define KEY2_PRES	3
#define WKUP_PRES   4

void KEY_Init(void);	//IO初始化
u8 KEY_Scan(u8);  		//按键扫描函数	
void EXTIX_Init(void);
//void TIM3_Int_Init(u16 arr, u16 psc);
void KEY_INIT (void);

int KeyCtl(void);
int RightKey_LongPress_Process(void);
int LeftKey_LongPress_Process(void);
int doublekey_press_process(void);
#endif
