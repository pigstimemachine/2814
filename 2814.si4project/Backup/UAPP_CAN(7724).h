#ifndef UAPP_CAN_H
#define UAPP_CAN_H
#include "sys.h"
typedef struct
{
   u8 count;
   u8 status;
   u8 workmode;
   u8 error;
   u8 stage;
   u8 speedfeedback;	
}HEARTBEAT_DATA;

typedef struct
{
   u16 WeldingCurrent;
   u16 WeldingVoltage;
   u16 PAR1;	
}FEEDBACK_DATA;


typedef struct
{
   u8 CANTxReady;
   u8 CANRxReady;
   u8 CANWaitAck;
   u8 OnLineSta;
	 u8 OffLineCnt;
   u8 MemSyncSign;
}CAN_STATUS;

#define Readok               0
#define Readerr              1

#define NRead                0x55



#define MaxDatalen           100
#define MaxErrNum            10

typedef struct {
	u8   CodeData[MaxDatalen];
	u16  DLC;
	u8   Readflag;
}DataBufType;


typedef struct 
{
	int layer;
	int max_layer;
	char layer_str[5];    
	char id;
	int rcv_sts;
    int send_sts;
    long cnt;
    int onlinests;
}CAN_LAYER;


#if !TRANSMIT_FLAG  
#define TRANSMIT_FLAG         1

//typedef struct
//{
//	u8   CTSflag;
//	u32  Datasum;
//	u32  Framecnt;
//	u32  Datalen;
//	u32  Datacnt;
//	long long Tmpsum;
//}TRANSMIT_CTRL;

#endif
typedef struct
{
	u8   CTSflag;
	long Datasum;
	u32  Framecnt;
	u32  Datalen;
	u32  Datacnt;
	long Tmpsum;
}TRANSMIT_CTRL;

struct _AS4_Final_SendData
{
	char PROJECT_ID[30];	//��Ŀ����
	char TEAM_CODE[20];		//������
	char PROCESS[20];		//���չ��
	char EQUIP_CODE[20];	//�豸���
	char DATASBOX_CODE[20];	//���ݺб��
	char HJ_PROCESS[20];	//���ӹ���
	char PERSON_CODE[60];	//��Ա���
	char PERSON_CODE_Front[60];	//��Ա��Ż���ǰ��
	char WELD_CODE[60];		//���ڱ��
	char WELD_CODE_Front[60];		//���ڱ��ǰ��
	char POSITION[10];		//����λ��
	char LAYER[10];			//����
	char CURRENT[20];		//���ӵ���
	char VOLTAGE[20];		//��ǹ��ѹ
	char SS_SPEED[20];		//��˿�ٶ�
	char TEMP[20];			//�����¶�	
	char HUMIDITY[20];		//����ʪ��	
	char HJ_SPEED[20];		//�����ٶ�	
	int LayerTemp;		//�����¶�	
	char workExcep[40];		//�����쳣	
	char CJ_TIME[30];		//ʱ��		
};

#define MaxCanbyte            6  

#define ResetKey              0xabcdef

#define FAIL_COMM             130


#define NeedToSendData		1
#define SendDataSUCC		0

extern CAN_LAYER can_layer;
extern struct _AS4_Final_SendData AS4Data;
extern struct _AS4_Final_SendData His_AS4Data;


extern DataBufType DecodeData,CAN_DataPipe,CAN_DataWelder,CAN_DataProjectID,CAN_DataTeamCode,CAN_DataProcess,CAN_DataEquipCode,
						CAN_DataBoxID,CAN_DataHjProcess,CAN_DataWarning,CAN_DataTime;
extern TRANSMIT_CTRL       CAN_CodeTrans,CAN_BinTrans,CAN_CodeTrans_Pipe,CAN_CodeTrans_Welder,CAN_CodeTrans_ProjectID,
					CAN_CodeTrans_TeamCode,CAN_CodeTrans_Process,CAN_CodeTrans_EquipCode,CAN_CodeTrans_BoxID,
					CAN_CodeTrans_HjProcess,CAN_CodeTrans_Warning,CAN_CodeTrans_Time;

void CAN_TASK1ms(void);  //1000HZ
void CAN_TASK1000ms(void);  //1HZ
void _CAN_TASK10ms(void); //100HZ
void _CAN_TASK250ms(void);

void _SEND_LayerFeedback(void);
int send_layer_data(void);
void _SEND_GetReady(void);
void _SensorVal_Angle(u8* Databuf);
#endif





