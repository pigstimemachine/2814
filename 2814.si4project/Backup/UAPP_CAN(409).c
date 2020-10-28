#include "lib.h"
//#include	"CH454CMD.H"
#include "oled.h"
extern CONN_CTRL ConnCtrl;
HEARTBEAT_DATA      HeartBeatData;
FEEDBACK_DATA       FeedBackData;
CAN_STATUS          CanStatus;
ECANID_INTERNAL     ReceiveID;
//DataBufType*        Codedata;
TRANSMIT_CTRL       CAN_CodeTrans,CAN_BinTrans;
static void _CommWatchDog_TASK(void);
static void _CommWatchDog_Feed(void);
#define ADDR_SEL(x) (x==LocalHostAddr1? ADDR_BIN1_OFFSET:ADDR_BIN2_OFFSET)
#define ERR_COMM(x) (x>0? 0:FAIL_COMM)

//u8 TmpFlashbuf[STM_SECTOR_SIZE];

CAN_LAYER can_layer= {0};
struct _AS4_Final_SendData AS4Data={0};
struct _AS4_Final_SendData His_AS4Data={0};

u8 _Read_CanOnlineSta(void)
{
    return CanStatus.OnLineSta;
}

static void _SEND_HartBeat(ECANID_INTERNAL* CID)
{
	short Onlinenum=_Read_OnlineSta();
	CANBufType TxFrame; u32 SYStick;
  SYStick=GetSysTick();
	memset(TxFrame.FrameData,0,sizeof(TxFrame.FrameData));
	TxFrame.MSGID=*(Uint16*)CID;
	TxFrame.FrameData[0]=CMD_Heartbeat;
	TxFrame.FrameData[1]=(SYStick>>10)&0xff;
	TxFrame.FrameData[4]=ERR_COMM(Onlinenum);
	TxFrame.DLC=8;
	Can_TxMsg(&TxFrame);
}








void _SEND_CodeApply(u32 Datalen,u32 Datasum)
{
	 if(CanStatus.OnLineSta==STA_ON)
	 {	 
		 	CANBufType TxFrame;
			TxFrame.MSGID=*(Uint16*)&TransmitID0;
			TxFrame.FrameData[0]=CMD_CodeApply;
            memcpy(&TxFrame.FrameData[1],&Datalen,3);
		    memcpy(&TxFrame.FrameData[4],&Datasum,4);
			TxFrame.DLC=8;
			Can_TxMsg(&TxFrame);
	 }	 
}	

void _SEND_CodeData(u32 Datalen,u8* Dbuf,u32 DataCnt)
{
	 if(CanStatus.OnLineSta==STA_ON)
	 {	 
		 	CANBufType TxFrame;
			TxFrame.MSGID=*(Uint16*)&TransmitID0;
			TxFrame.FrameData[0]=CMD_CodeData;
            TxFrame.FrameData[1]=DataCnt&0xff;
            memcpy(&TxFrame.FrameData[2],Dbuf,Datalen);
			TxFrame.DLC=(Datalen+2)&0xff;
			Can_TxMsg(&TxFrame);
	 }	 
}	

/*
void _CodeApply_Task(void)//发送扫码请求
{
	 u16 cnt; long Checksum=0x10000000;
   if(_ReadDecodeData(&Codedata)==Readok)
	 {
			for(cnt=0;cnt<Codedata->DLC;cnt++)
			{
				 Checksum-=Codedata->CodeData[cnt];
			}
			_SEND_CodeApply(Codedata->DLC,Checksum);
			memset(&CAN_CodeTrans,0,sizeof(CAN_CodeTrans));
			CAN_CodeTrans.Datalen=Codedata->DLC;				
	 }	 
}
*/

/*
static u8 _CodeData_Task(void)
{
	 u8 Tempcnt; short Sendbyte; long Lastbyte;
	 Lastbyte=Codedata->DLC-CAN_CodeTrans.Datacnt;
	 if(Lastbyte<=MaxCanbyte)
	   Sendbyte=Lastbyte;
	 else 
		 Sendbyte=MaxCanbyte;
   if(CAN_CodeTrans.CTSflag==ACK_SUCC)
	 {
		  CAN_CodeTrans.CTSflag=0;
		  if(CAN_CodeTrans.Datacnt<CAN_CodeTrans.Datalen)
			{	
					Tempcnt=CAN_CodeTrans.Framecnt&0xff;
					_SEND_CodeData(Sendbyte,Codedata->CodeData+CAN_CodeTrans.Datacnt,Tempcnt);
					CAN_CodeTrans.Framecnt++; 
				  CAN_CodeTrans.Datacnt+=Sendbyte;
				  return 0;
			}	
			else if(CAN_CodeTrans.Datacnt==CAN_CodeTrans.Datalen)
			{
			    return SEND_OK;
			}						
	 }	
   else if(CAN_CodeTrans.CTSflag==ACK_ERR)	 
	 {
	    memset(&CAN_CodeTrans,0,sizeof(CAN_CodeTrans));
	 }	 
	 return SEND_ERR;
}	
*/

u8 _Rx_BinApply(u8* buf,u8 cid)
{
	 u32 TmpDatlen,TmpDatsum; 
	 //读取FLASH 比对len和sum，如果不相同则返回SUCC
	 
	 STMFLASH_Read(STM32_FLASH_BASE+ADDR_PARA_OFFSET,(u16*)MEM_Databuf,MAX_PARA_NUM);

    if(cid==LocalHostAddr2)
   {
	      memcpy(&TmpDatlen,MEM_Databuf+ADDR_BinLen,4);
		  memcpy(&TmpDatsum,MEM_Databuf+ADDR_BinSum,4);
	 }		 
	 memset(&CAN_BinTrans,0,sizeof(CAN_BinTrans));
	 memcpy(&(CAN_BinTrans.Datalen),&buf[1],3);
	 memcpy(&(CAN_BinTrans.Datasum),&buf[4],4);
	 CAN_BinTrans.Tmpsum=0x10000000;
	 if(((TmpDatlen==CAN_BinTrans.Datalen)&&(TmpDatsum==CAN_BinTrans.Datasum))||(CAN_BinTrans.Datalen>MAX_BIN1_NUM))
   {		 
		  memset(&CAN_BinTrans,0,sizeof(CAN_BinTrans));
	    return ACK_ERR;
	 }	 
	 else
	 {
		   // _LED_SetTime(1,30,30,0); 
		  STMFLASH_Erase(STM32_FLASH_BASE+ADDR_BIN1_OFFSET,MAX_BIN1_NUM/2);	
	    return ACK_SUCC;
	 }
}	

u8 _Rx_BinData(u8* buf,u8 DLC,u8 cid)
{
	 u8 cnt,Tmpcnt; u32 AddrOffset; u16 UpdateFlag=0;
	 Tmpcnt=buf[1];
	 if((CAN_BinTrans.Framecnt&0xff)==Tmpcnt)
	 {	 
		 for(cnt=2;cnt<DLC;cnt++)
		 {
				CAN_BinTrans.Tmpsum-=buf[cnt];
		 } 
		 DLC-=2;
		  if(cid==LocalHostAddr2)
			 AddrOffset=STM32_FLASH_BASE+ADDR_BIN1_OFFSET+CAN_BinTrans.Datacnt; 
		 STMFLASH_WriteNoErase(AddrOffset,(u16*)&buf[2],DLC/2);
		 CAN_BinTrans.Datacnt+=DLC;
		 if(CAN_BinTrans.Datacnt>=CAN_BinTrans.Datalen)
		 {
		    if(CAN_BinTrans.Tmpsum==CAN_BinTrans.Datasum)
				{	
					 //向FLASH写入新的Datasum,Datalen,和程序升级标志
					 UpdateFlag=UPDATA_OK;

                    if(cid==LocalHostAddr2)
                    {
                          memcpy(MEM_Databuf+ADDR_BinLen,&CAN_BinTrans.Datalen,4);
                          memcpy(MEM_Databuf+ADDR_BinSum,&CAN_BinTrans.Datasum,4);
						  memcpy(MEM_Databuf+ADDR_Updata,&UpdateFlag,2);
					 }					
           STMFLASH_Write(STM32_FLASH_BASE+ADDR_PARA_OFFSET,(u16*)MEM_Databuf,MAX_PARA_NUM);					 
          //_LED_SetTime(2,100,100,3000);			
                     return ACK_SUCC;
				}	
        else 
           return ACK_ERR;					
		 }
		 CAN_BinTrans.Framecnt++;
     return ACK_SUCC;	 
		 
	 }
   return ACK_ERR;	 
}

/*
u8 _Rx_ResetDevid(u8* buf)
{
   u32 TmpKey=0;
	 memcpy(&TmpKey,buf+5,3);
	 if(TmpKey==ResetKey)
	 {
	    NRF24L01_ModifyDevID(buf+1);
		  memcpy(MEM_Databuf+ADDR_DEVID,buf+1,(TX_ADR_WIDTH-1));
		  STMFLASH_Write(STM32_FLASH_BASE+ADDR_PARA_OFFSET,(u16*)MEM_Databuf,MAX_PARA_NUM);  
		  return ACK_SUCC;
	 }
	 return ACK_ERR;
}
*/
void offline_sts()
{
   //  can_layer.onlinests = 1;
     can_layer.layer = 0 ;
    _SEND_GetReady();
}

static void _CommWatchDog_TASK(void)
{
		CanStatus.OffLineCnt++;
		if(CanStatus.OffLineCnt>MaxOfflinecnt)
		{
			 CanStatus.OnLineSta=STA_OFF;
            
          //  CharToNixieTube(NoCanConnect);
         //   ch454_write( CH454_TWINKLE | 0x07 );
            memset( &can_layer , 0 , sizeof(can_layer));
		}	 
        if( can_layer.rcv_sts == 0 )
        {
             can_layer.layer = 0 ;
            _SEND_GetReady();
        }
}	

static  void _CommWatchDog_Feed()
{
 //  ch454_write( CH454_TWINKLE );
    CanStatus.OffLineCnt=0;
    CanStatus.OnLineSta=STA_ON;
       // CharToNixieTube(can_layer.layer_str);
    
}	

static void _SEND_ACK(u8 CMD,u8 flag,ECANID_INTERNAL* CID)
{
	 u8 Tmpid;
	 Tmpid=CID->source;
	 CID->source=CID->target;
	 CID->target=Tmpid;
   if(CanStatus.OnLineSta==STA_ON)
	 {	 
        CANBufType TxFrame;
        TxFrame.MSGID=*(Uint16*)CID;
        TxFrame.FrameData[0]=CMD_SendAck;
        TxFrame.FrameData[1]=CMD;
        TxFrame.FrameData[2]=flag;
        TxFrame.DLC=3;
        Can_TxMsg(&TxFrame);
	 }	 
}	


/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	_SEND_LayerFeedback 发送焊层参数到数据盒
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/05/18 Create
  * @Version 	1.0 2020/05/18  
  * @Note  
  
  **/
void _SEND_LayerFeedback(void)
{
    if(  can_layer.layer != 0  )
    {
        CANBufType TxFrame;
        TxFrame.MSGID=*(Uint16*)&TransmitID3;
        TxFrame.FrameData[0]=CMD_Layer;
        TxFrame.FrameData[1]=can_layer.layer;
        TxFrame.FrameData[2]=can_layer.max_layer;
        memcpy(&TxFrame.FrameData[3] ,&can_layer.layer_str, 5 );
        TxFrame.DLC=8;
        Can_TxMsg(&TxFrame);         
    }


}

int send_layer_data()
{ 
    if((can_layer.send_sts == NeedToSendData)  )
    {
         _SEND_LayerFeedback();
    }
   return 0;
}

int send_data_succ()
{
    can_layer.send_sts = SendDataSUCC;
    return 0;
}
int can_rcv_layer(CANBufType*  RxData)
{
    can_layer.layer = RxData->FrameData[1];
    can_layer.max_layer =  RxData->FrameData[2] ;    
    memcpy(&can_layer.layer_str , &RxData->FrameData[3] , 5);

   // CharToNixieTube(can_layer.layer_str);
    can_layer.rcv_sts = 1;    
    return 0;
}
/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	CAN通信1hz 温度接收
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/05/22 Create
  * @Version 	1.0 2020/08/24  
  *		     	1.1 2020/08/24 change sth
  * @Note  
  
  **/
int can_rcv_temp(CANBufType*  RxData)
{ 
    memcpy(&AS4Data.TEMP , &RxData->FrameData[1] , 7);
    
    return 0;
}
/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	CAN通信1hz 湿度接收
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/08/24  Create
  * @Version 	1.0 2020/08/24  
  *		     	1.1 2020/08/24 change sth
  * @Note  
  
  **/
int can_rcv_hmi(CANBufType*  RxData)
{ 
    memcpy(&AS4Data.HUMIDITY , &RxData->FrameData[1] , 7);
    
    return 0;
}
/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	CAN通信1hz position
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/08/24  Create
  * @Version 	1.0 2020/08/24  
  *		     	1.1 2020/08/24 change sth
  * @Note  
  
  **/
int can_rcv_position(CANBufType*  RxData)
{ 
    memcpy(&AS4Data.POSITION , &RxData->FrameData[1] , 7);
    
    return 0;
} 
/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	CAN通信1hz time
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/08/24  Create
  * @Version 	1.0 2020/08/24  
  *		     	1.1 2020/08/24 change sth
  * @Note  
  
  **/
int can_rcv_time(CANBufType*  RxData)
{ 
    memcpy(&AS4Data.CJ_TIME , &RxData->FrameData[1] , 7);
    
    return 0;
}
/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	CAN通信1hz voltage
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/08/24  Create
  * @Version 	1.0 2020/08/24  
  *		     	1.1 2020/08/24 change sth
  * @Note  
  
  **/
int can_rcv_voltage(CANBufType*  RxData)
{ 
    memcpy(&AS4Data.VOLTAGE , &RxData->FrameData[1] , 7);
    
    return 0;
}
/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	CAN通信1hz current
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/08/24 Create
  * @Version 	1.0 2020/08/24  
  *		     	1.1 2020/08/24 change sth
  * @Note  
  
  **/
int can_rcv_current(CANBufType*  RxData)
{ 
    memcpy(&AS4Data.CURRENT , &RxData->FrameData[1] , 7);
    
    return 0;
}
/**

  * @brief   	how to use it ,and where to use it
  * @Name	 	CAN通信1hz current
  * @param   	None
  * @retval  	None
  * @Author  	ZCJ
  * @Date 	 	2020/08/24 Create
  * @Version 	1.0 2020/08/24  
  *		     	1.1 2020/08/24 change sth
  * @Note  
  
  **/
int can_rcv_TeamCode(CANBufType*  RxData)
{ 
    memcpy(&AS4Data.TEAM_CODE , &RxData->FrameData[1] , 7);
    
    return 0;
}
void _SEND_GetReady(void)
{
	CANBufType TxFrame;
	TxFrame.MSGID=*(Uint16*)&TransmitID3;
	TxFrame.FrameData[0]=CMD_GetReady;
	TxFrame.DLC=2;
	Can_TxMsg(&TxFrame); 
}

u8 CanReceiveProcess(void)
{
   u8 Ackflag=0,Tmpid; ECANID_INTERNAL CID;
	 CANBufType  CANRxData,CANTxData;
	 memset(&CANRxData,0,sizeof(CANRxData));	 
	 if(Can_RxMsg(&CANRxData)!=RX_NO_ERR) 
         return 0; 
	 memcpy(&CID,&CANRxData.MSGID,2);
	 switch(CANRxData.FrameData[0])
	 {
		 case CMD_SendAck://0x81
			 switch(CANRxData.FrameData[1])
			 {
                  case RFCMD_ReqConn://0x01 接收到主机发送的应答，则从机上线
                         ConnCtrl.OnLineSta=STA_ON;
                      //  _LED_SetTime(1,60000,0,0);       
                       break;                 
				  case CMD_CodeApply://0x30应答发送扫码数据申请
						CAN_CodeTrans.CTSflag=CANRxData.FrameData[2];
					  break;
					case CMD_CodeData://应答发送扫码数据
						CAN_CodeTrans.CTSflag=CANRxData.FrameData[2];
					  break;
                    case CMD_Layer:
                         send_data_succ();
                            
                        break;
			 }	 
		   break;
		 case CMD_GetReady://0x01

       break; 
     case CMD_WeldingStatusCheck://0x05

       break;
     case CMD_Heartbeat://0x80//
/* 
         0x07C0 2810ID     0000 01111 1000 000? 
         0x07D0 4GboardID  0000 01111 1010 000?
         0X0788 1068-4     0000 01111 0001 000?
         0x00d0            0000 00001 1010 000
         0X0450            0000 01000 1010 001
*/       
    //   LedProcess(CANRxData.MSGID);    
       _CommWatchDog_Feed();			 
       memcpy(&HeartBeatData,&CANRxData.FrameData[1],CANRxData.DLC-1);
       break;
     
     case CMD_FeedBack://0x97
       memcpy(&FeedBackData,&CANRxData.FrameData[1],CANRxData.DLC-1);
       break;
     case CMD_ErrorAlert://0xa0		 
       break;

     
     
     case CMD_RESET://0x42
  //     Ackflag=_Rx_ResetDevid(CANRxData.FrameData);
       break;	
  	 case CMD_Layer:
		//Ackflag = ACK_SUCC ;
        
        can_rcv_layer(&CANRxData);
     _SEND_ACK(CANRxData.FrameData[0],ACK_SUCC,&CID);
	 	break;
     case CMD_Sys_Temp:
        can_rcv_temp(&CANRxData);      
         break;
     case CMD_Sys_Hmi:
        can_rcv_hmi(&CANRxData);  
         break;  
     case CMD_Position:
        can_rcv_position(&CANRxData);  
         break;  
     case CMD_Time:
        can_rcv_time(&CANRxData);  
         break;       
     case CMD_Voltage:
        can_rcv_voltage(&CANRxData);  
         break;
     case CMD_Current:
        can_rcv_current(&CANRxData);  
         break; 
     case CMD_TeamCode:
        can_rcv_TeamCode(&CANRxData);  
         break;     
	 }	
   if(Ackflag!=0)
   {
	    _SEND_ACK(CANRxData.FrameData[0],Ackflag,&CID);
	 }		 
   return 1;	 
}	

void CAN_TASK1ms(void)  //1000HZ
{
     CanReceiveProcess();
	 TASK_CAN_AutoSend();
     KeyCtl();
     send_layer_data();
     
}
	
void CAN_TASK1000ms(void)  //1HZ
{
     _CommWatchDog_TASK();	
	 _SEND_HartBeat((ECANID_INTERNAL*)&TransmitID3); 
    _LED_SetTime(2,500,0,1000);  
    

    LCD_ShowChinese(5,20,"焊口",RED,WHITE,16,0);
    LCD_ShowString(35,20,":",RED,WHITE,16,0);
	LCD_ShowString(45,20,"GDNGG3E-01-HHRP097+008-HN01-SB-LW",RED,WHITE,16,0);
		

    
    LCD_ShowChinese(5,60,"焊工",RED,WHITE,16,0);
    LCD_ShowString(35,60,":",RED,WHITE,16,0);
	LCD_ShowString(45,60,"GDJ-WPS-100",RED,WHITE,16,0);

    LCD_ShowChinese(150,60,"机组",RED,WHITE,16,0);
    LCD_ShowString(180,60,":",RED,WHITE,16,0);
 	LCDShowStringUpdate( 195,60, AS4Data.TEAM_CODE, His_AS4Data.TEAM_CODE,20,RED, WHITE, 16, 0);   

 
	LCD_ShowChinese(5,120,"工艺",RED,WHITE,16,0);
    LCD_ShowString(35,120,":",RED,WHITE,16,0);
	LCD_ShowString(45,120,"YDXB-WPS-01-916",RED,WHITE,16,0);    

    LCD_ShowChinese(5,140,"设备",RED,WHITE,16,0);
    LCD_ShowString(35,140,":",RED,WHITE,16,0);
	LCD_ShowString(45,140,"04500190666K",RED,WHITE,16,0);  
 

    LCD_ShowChinese(5,160,"电压",RED,WHITE,16,0);
    LCD_ShowString(35,160,":",RED,WHITE,16,0);
    LCD_ShowString(45,160,AS4Data.VOLTAGE,RED,WHITE,16,0); 
    
	LCD_ShowChinese(120,160,"电流",RED,WHITE,16,0);
    LCD_ShowString(150,160,":",RED,WHITE,16,0);
	LCD_ShowString(165,160,AS4Data.CURRENT,RED,WHITE,16,0);
    
    LCD_ShowChinese(235,160,"焊层",RED,WHITE,16,0);
    LCD_ShowString(265,160,":",RED,WHITE,16,0);
    LCD_ShowString(275,160,can_layer.layer_str,RED,WHITE,16,0); 
	LCDShowStringUpdate( 275,160,can_layer.layer_str,His_AS4Data.LAYER,5,RED,WHITE,16,0); 
    
    
    
    LCD_ShowChinese(235,180,"位置",RED,WHITE,16,0);
    LCD_ShowString(265,180,":",RED,WHITE,16,0);
	LCDShowStringUpdate( 275,180, AS4Data.POSITION, His_AS4Data.POSITION,10,RED, WHITE, 16, 0);


    LCD_ShowChinese(5,180,"温度",RED,WHITE,16,0);
    LCD_ShowString(35,180,":",RED,WHITE,16,0);
	LCD_ShowString(45,180,AS4Data.TEMP,RED,WHITE,16,0);     
    
    LCD_ShowChinese(120,180,"湿度",RED,WHITE,16,0);
    LCD_ShowString(150,180,":",RED,WHITE,16,0);
	LCD_ShowString(165,180,AS4Data.HUMIDITY,RED,WHITE,16,0);  

    LCD_ShowString(5,220,AS4Data.CJ_TIME,RED,WHITE,16,0);
     
}


void _CAN_TASK10ms(void) //100HZ
{
   
    /*
	 _CodeApply_Task();
   if(_CodeData_Task()==SEND_OK)
	 {
	    _LED_SetTime(2,100,100,3000);//接收到扫码成功的回传
	 }
*/    
}

void _CAN_TASK250ms(void) //3HZ
{
//    _SEND_TempFeedback();//发送温度
//	_SEND_AngleFeedback();//发送角度
}
