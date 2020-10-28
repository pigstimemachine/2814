#include "oled.h"
#include "stdlib.h"
//#include "lcdfont.h"
#include "delay.h"
#include "ShowInterface.h"
#include "UAPP_CAN.h"
#include "key.h"
#include "pic.h"
#include "UAPP_Senser.h"
//#include "lib.h"
INTERFACE Interface;

int ShowInterfaceMain(void)//1
{
	    LCD_ShowChinese(5,20,"����",RED,WHITE,16,0);
	    LCD_ShowString(35,20,":",RED,WHITE,16,0);
		//LCDShowStringUpdate(45,20,CAN_DataPipe.CodeData,His_AS4Data.WELD_CODE,60,RED,WHITE,16,0);//34 275 8
		LCDStrLineFeed(45,20,CAN_DataPipe.CodeData,His_AS4Data.WELD_CODE,His_AS4Data.WELD_CODE_Front,60);
		/*	
	    LCD_ShowChinese(5,40,"��Ŀ",RED,WHITE,16,0);
	    LCD_ShowString(35,40,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,40,CAN_DataProjectID.CodeData,His_AS4Data.PROJECT_ID,30,RED,WHITE,16,0);
*/
	    LCD_ShowChinese(5,60,"����",RED,WHITE,16,0);
	    LCD_ShowString(35,60,":",RED,WHITE,16,0);
		LCDStrLineFeed(45,60,CAN_DataWelder.CodeData,His_AS4Data.PERSON_CODE,His_AS4Data.PERSON_CODE_Front,60);
		//LCDShowStringUpdate(45,60,CAN_DataWelder.CodeData,His_AS4Data.PERSON_CODE,60,RED,WHITE,16,0);
		
	    LCD_ShowChinese(5,100,"��ѹ",RED,WHITE,16,0);
	    LCD_ShowString(35,100,":",RED,WHITE,16,0);
	    LCD_ShowString(45,100,AS4Data.VOLTAGE,RED,WHITE,16,0); 
	    
		LCD_ShowChinese(120,100,"����",RED,WHITE,16,0);
	    LCD_ShowString(150,100,":",RED,WHITE,16,0);
		LCD_ShowString(165,100,AS4Data.CURRENT,RED,WHITE,16,0);
	    
	    LCD_ShowChinese(235,100,"����",RED,WHITE,16,0);
	    LCD_ShowString(265,100,":",RED,WHITE,16,0);
		LCDShowStringUpdate( 275,100,can_layer.layer_str,His_AS4Data.LAYER,5,RED,WHITE,16,0); 
	    
	    LCD_ShowChinese(5,120,"˿��",RED,WHITE,16,0);
	    LCD_ShowString(35,120,":",RED,WHITE,16,0);
		LCD_ShowString(45,120,AS4Data.SS_SPEED,RED,WHITE,16,0);  
	 
	    LCD_ShowChinese(120,120,"����",RED,WHITE,16,0);
	    LCD_ShowString(150,120,":",RED,WHITE,16,0);
		LCD_ShowString(165,120,AS4Data.HJ_SPEED,RED,WHITE,16,0);

	    LCD_ShowChinese(235,140,"����",RED,WHITE,16,0);
	    LCD_ShowString(265,140,":",RED,WHITE,16,0);
		LCD_ShowIntNum(270,140,AS4Data.LayerTemp,3,RED,WHITE,16);


	    LCD_ShowChinese(5,140,"ʪ��",RED,WHITE,16,0);
	    LCD_ShowString(35,140,":",RED,WHITE,16,0);
		LCD_ShowString(45,140,AS4Data.HUMIDITY,RED,WHITE,16,0); 


	    LCD_ShowChinese(120,140,"����",RED,WHITE,16,0);
	    LCD_ShowString(150,140,":",RED,WHITE,16,0);
		LCD_ShowString(165,140,AS4Data.TEMP,RED,WHITE,16,0);     
	    
 

	    LCD_ShowChinese(235,120,"λ��",RED,WHITE,16,0);
	    LCD_ShowString(265,120,":",RED,WHITE,16,0);
		LCDShowStringUpdate( 275,120, AS4Data.POSITION, His_AS4Data.POSITION,10,RED, WHITE, 16, 0);


	    LCD_ShowChinese(200,160,"����",RED,WHITE,16,0);
	    LCD_ShowString(230,160,":",RED,WHITE,16,0);
		LCDShowStringUpdate(245,160,CAN_DataHjProcess.CodeData,His_AS4Data.HJ_PROCESS,20,RED,WHITE,16,0);


	    LCD_ShowChinese(5,160,"����",RED,WHITE,16,0);
	    LCD_ShowString(35,160,":",RED,WHITE,16,0);
	 	LCDShowStringUpdate( 45,160, CAN_DataTeamCode.CodeData, His_AS4Data.TEAM_CODE,20,RED, WHITE, 16, 0);   


		LCD_ShowChinese(5,180,"���",RED,WHITE,16,0);
	    LCD_ShowString(35,180,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,180,CAN_DataProcess.CodeData,His_AS4Data.PROCESS,20,RED,WHITE,16,0);    
/*
	LCD_ShowChinese(5,160,"�豸",RED,WHITE,16,0);
	LCD_ShowString(35,160,":",RED,WHITE,16,0);
	LCDShowStringUpdate(45,160,CAN_DataBoxID.CodeData,His_AS4Data.DATASBOX_CODE,20,RED,WHITE,16,0);  
	
	LCD_ShowChinese(5,180,"����",RED,WHITE,16,0);
	LCD_ShowString(35,180,":",RED,WHITE,16,0);
	LCDShowStringUpdate(45,180,CAN_DataEquipCode.CodeData,His_AS4Data.EQUIP_CODE,20,RED,WHITE,16,0);

		*/
	    LCD_ShowChinese(5,200,"����",RED,WHITE,16,0);
	    LCD_ShowString(35,200,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,200,CAN_DataWarning.CodeData,His_AS4Data.workExcep,40,GBLUE,WHITE,16,0);

	    LCD_ShowString(150,220,CAN_DataTime.CodeData,RED,WHITE,16,0);	
        
        LCD_ShowString(5,220,"4G",RED,WHITE,16,0);
        LCD_ShowChinese(23,220,"�ź�",RED,WHITE,16,0);
        LCD_ShowString(53,220,":",RED,WHITE,16,0);
        LCDShowStringUpdate(65,220,CAN_DataSingalStrength.CodeData,His_AS4Data.DeviceData.SignalSrth,5,RED,WHITE,16,0);
        
		
        return 0;
}



int ShowInterfaceEquipment(void)//2
{
	int AngleSts;
	AngleSts = weld_angle() ;
	LCD_ShowChinese(5,40,"�豸",RED,WHITE,16,0);
	LCD_ShowString(35,40,":",RED,WHITE,16,0);
	LCDShowStringUpdate(45,40,CAN_DataBoxID.CodeData,His_AS4Data.DATASBOX_CODE,20,RED,WHITE,16,0);  
	
    LCD_ShowChinese(5,20,"��Ŀ",RED,WHITE,16,0);
    LCD_ShowString(35,20,":",RED,WHITE,16,0);
	LCDShowStringUpdate(45,20,CAN_DataProjectID.CodeData,His_AS4Data.PROJECT_ID,30,RED,WHITE,16,0);	
	
	LCD_ShowChinese(5,60,"����",RED,WHITE,16,0);
	LCD_ShowString(35,60,":",RED,WHITE,16,0);
	LCDShowStringUpdate(45,60,CAN_DataEquipCode.CodeData,His_AS4Data.EQUIP_CODE,20,RED,WHITE,16,0);

	LCD_ShowString(5,80,"AngleX",RED,WHITE,16,0);
	LCD_ShowString(55,80,":",RED,WHITE,16,0);
	LCDShowStringUpdate(65,80,SenserVal.AngleStrX,HisSenserVal.AngleStrX,5,RED,WHITE,16,0);
	
	LCD_ShowString(105,80,"AngleY",RED,WHITE,16,0);
	LCD_ShowString(155,80,":",RED,WHITE,16,0);
	LCDShowStringUpdate(165,80,SenserVal.AngleStrY,HisSenserVal.AngleStrY,5,RED,WHITE,16,0);

	LCD_ShowString(205,80,"AngleZ",RED,WHITE,16,0);
	LCD_ShowString(255,80,":",RED,WHITE,16,0);
	LCDShowStringUpdate(265,80,SenserVal.AngleStrZ,HisSenserVal.AngleStrZ,5,RED,WHITE,16,0);


	LCD_ShowChinese(5,100,"��ǰ��������",RED,WHITE,16,0);
	LCD_ShowString(105,100,":",RED,WHITE,16,0);
	switch (AngleSts)
	{
		case _0clock_position:
			LCD_ShowChinese(115,100,"�����һ���ӷ���",RED,WHITE,16,0);//�����һ���ӷ���
			break;
		case _3clock_position:
			LCD_ShowChinese(115,100,"����������ӷ���",RED,WHITE,16,0);//�����һ���ӷ���//����������ӷ���
			break;
		case _6clock_position:
			LCD_ShowChinese(115,100,"����������ӷ���",RED,WHITE,16,0);//�����һ���ӷ���//����������ӷ���
			break;
		default:
			LCD_ShowChinese(115,100,"���������������",RED,WHITE,16,0);//�����һ���ӷ���//����������ӷ���
			break;
	}


	//LCDStrLine3Feed(5, 120, CAN_DataCPSI.CodeData, His_AS4Data.DeviceData.CPSI, His_AS4Data.DeviceData.FrontCPSI,His_AS4Data.DeviceData.MiddleCPSI, 90);
		
	//LCDStrLineFeed(5, 120, CAN_DataCPSI.CodeData, His_AS4Data.DeviceData.CPSI, His_AS4Data.DeviceData.FrontCPSI, 90);
	

	LCD_ShowString(5,140,CAN_DataICCID.CodeData,RED,WHITE,16,0);

	LCD_ShowString(5,160,"IMEI:",RED,WHITE,16,0);
	LCD_ShowString(50,160,CAN_DataIMEI.CodeData,RED,WHITE,16,0);

	LCD_ShowString(5,180,"LBSx",RED,WHITE,16,0);
	LCD_ShowString(50,180,CAN_DataLBSx.CodeData,RED,WHITE,16,0);

	LCD_ShowString(5,200,"LBSy",RED,WHITE,16,0);
	LCD_ShowString(50,200,CAN_DataLBSy.CodeData,RED,WHITE,16,0);

	
	LCD_ShowString(150,220,CAN_DataTime.CodeData,RED,WHITE,16,0);	
	return 0;
}

int ShowInterfaceAbout(void)//3
{	
	//LCD_ShowPicture(40,20,240,46,gImage_3);
	LCD_ShowPicture(40,20,240,46,gImage_black);
	LCD_ShowChinese(70,100,"�ɶ��ܹȼ����������޹�˾",RED,WHITE,16,0);
	//LCD_ShowString(150,220,CAN_DataTime.CodeData,RED,WHITE,16,0);
	

    LCD_ShowChinese(70,130,"�ɶ��и��������·",RED,WHITE,16,0);   
	LCD_ShowString(217,130,"100",RED,WHITE,16,0);
    LCD_ShowChinese(247,130,"��",RED,WHITE,16,0);
	
    LCD_ShowString(75,160,"http://www.xionggu.com",RED,WHITE,16,0);
    LCD_ShowString(68,190,"E-mail:welder@xionggu.com",RED,WHITE,16,0); 
	
	LCD_ShowString(110,220,"+86 400 8080 663",RED,WHITE,16,0);
	return 0;
}
int IsInterfaceChange(void)
{
	if(Interface.PageChangeFlag == 1)
	{
		LCD_Fill(0,0,LCD_W,LCD_H,WHITE);	
		Interface.PageChangeFlag = 0;
	}
}
int InterfaceChangeFlag(void)
{
	Interface.PageChangeFlag = 1;
}
int ChooseInterface(void)
{
	switch(Interface.page)
	{
		case PageMain:	
			ShowInterfaceMain();
			break;
		case PageEquipment:
			ShowInterfaceEquipment();
			break;
		case PageAbout:
			ShowInterfaceAbout();
			break;
		default:
			break;
	}
    return 0 ;
}
int WhichInterface(void)
{
	if(Interface.PageChangeFlag == 0)
	{
		ChooseInterface();
	}
}

