#include "oled.h"
#include "stdlib.h"
#include "lcdfont.h"
#include "delay.h"
#include "ShowInterface.h"
#include "pic.h"
#include "lib.h"
INTERFACE Interface;

int ShowInterfaceMain(void)
{
	    LCD_ShowChinese(5,20,"����",RED,WHITE,16,0);
	    LCD_ShowString(35,20,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,20,CAN_DataPipe.CodeData,His_AS4Data.WELD_CODE,60,RED,WHITE,16,0);
			
	    LCD_ShowChinese(5,40,"��Ŀ",RED,WHITE,16,0);
	    LCD_ShowString(35,40,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,40,CAN_DataProjectID.CodeData,His_AS4Data.PROJECT_ID,30,RED,WHITE,16,0);

	    
	    LCD_ShowChinese(5,60,"����",RED,WHITE,16,0);
	    LCD_ShowString(35,60,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,60,CAN_DataWelder.CodeData,His_AS4Data.PERSON_CODE,60,RED,WHITE,16,0);

	    LCD_ShowChinese(150,60,"����",RED,WHITE,16,0);
	    LCD_ShowString(180,60,":",RED,WHITE,16,0);
	 	LCDShowStringUpdate( 195,60, CAN_DataTeamCode.CodeData, His_AS4Data.TEAM_CODE,20,RED, WHITE, 16, 0);   


	    LCD_ShowChinese(5,80,"��ѹ",RED,WHITE,16,0);
	    LCD_ShowString(35,80,":",RED,WHITE,16,0);
	    LCD_ShowString(45,80,AS4Data.VOLTAGE,RED,WHITE,16,0); 
	    
		LCD_ShowChinese(120,80,"����",RED,WHITE,16,0);
	    LCD_ShowString(150,80,":",RED,WHITE,16,0);
		LCD_ShowString(165,80,AS4Data.CURRENT,RED,WHITE,16,0);
	    
	    LCD_ShowChinese(235,80,"����",RED,WHITE,16,0);
	    LCD_ShowString(265,80,":",RED,WHITE,16,0);
		LCDShowStringUpdate( 275,80,can_layer.layer_str,His_AS4Data.LAYER,5,RED,WHITE,16,0); 
	    



	    LCD_ShowChinese(5,100,"˿��",RED,WHITE,16,0);
	    LCD_ShowString(35,100,":",RED,WHITE,16,0);
		LCD_ShowString(45,100,AS4Data.SS_SPEED,RED,WHITE,16,0);  
	 
	    LCD_ShowChinese(120,100,"����",RED,WHITE,16,0);
	    LCD_ShowString(150,100,":",RED,WHITE,16,0);
		LCD_ShowString(165,100,AS4Data.HJ_SPEED,RED,WHITE,16,0);

	    LCD_ShowChinese(235,100,"����",RED,WHITE,16,0);
	    LCD_ShowString(265,100,":",RED,WHITE,16,0);
		LCD_ShowIntNum(270,100,AS4Data.LayerTemp,3,RED,WHITE,16);




	    LCD_ShowChinese(5,120,"�¶�",RED,WHITE,16,0);
	    LCD_ShowString(35,120,":",RED,WHITE,16,0);
		LCD_ShowString(45,120,AS4Data.TEMP,RED,WHITE,16,0);     
	    
	    LCD_ShowChinese(120,120,"ʪ��",RED,WHITE,16,0);
	    LCD_ShowString(150,120,":",RED,WHITE,16,0);
		LCD_ShowString(165,120,AS4Data.HUMIDITY,RED,WHITE,16,0);  

	    LCD_ShowChinese(235,120,"λ��",RED,WHITE,16,0);
	    LCD_ShowString(265,120,":",RED,WHITE,16,0);
		LCDShowStringUpdate( 275,120, AS4Data.POSITION, His_AS4Data.POSITION,10,RED, WHITE, 16, 0);


	    LCD_ShowChinese(180,140,"����",RED,WHITE,16,0);
	    LCD_ShowString(210,140,":",RED,WHITE,16,0);
		LCDShowStringUpdate(225,140,CAN_DataHjProcess.CodeData,His_AS4Data.HJ_PROCESS,20,RED,WHITE,16,0);

		LCD_ShowChinese(5,140,"���",RED,WHITE,16,0);
	    LCD_ShowString(35,140,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,140,CAN_DataProcess.CodeData,His_AS4Data.PROCESS,20,RED,WHITE,16,0);    


	    LCD_ShowChinese(5,160,"�豸",RED,WHITE,16,0);
	    LCD_ShowString(35,160,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,160,CAN_DataBoxID.CodeData,His_AS4Data.DATASBOX_CODE,20,RED,WHITE,16,0);  
	 
	    LCD_ShowChinese(5,180,"����",RED,WHITE,16,0);
	    LCD_ShowString(35,180,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,180,CAN_DataEquipCode.CodeData,His_AS4Data.EQUIP_CODE,20,RED,WHITE,16,0);

	    LCD_ShowChinese(5,200,"����",RED,WHITE,16,0);
	    LCD_ShowString(35,200,":",RED,WHITE,16,0);
		LCDShowStringUpdate(45,200,CAN_DataWarning.CodeData,His_AS4Data.workExcep,40,GBLUE,WHITE,16,0);

	    LCD_ShowString(150,220,CAN_DataTime.CodeData,RED,WHITE,16,0);	

		return 0;
}

int ShowInterfaceAbout(void)
{
    LCD_Fill(0,0,LCD_W,LCD_H,BLACK);
	LCD_ShowPicture(40,90,240,46,gImage_3);

	return 0;
}

int WhiceInterface(void)
{
	switch(Interface.page)
	{
		case PageMain:	
			ShowInterfaceMain();
			break;
		case PageAbout:
			ShowInterfaceAbout();
			break;
		default:
			break;
	}
}


