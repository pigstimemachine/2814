#include "lib.h"

SENSER_VAL   SenserVal,SenserOld;

short filter_1(short NEW_DATA,short OLD_DATA,short k)   
{
    long result;
    if(NEW_DATA<OLD_DATA)
    {
        result=OLD_DATA-NEW_DATA;
        result=result*k;
        result=result+128;
        result=result>>8;
        result=OLD_DATA-result;
    }
    else if(NEW_DATA>OLD_DATA)
    {
        result=NEW_DATA-OLD_DATA;
        result=result*k;
        result=result+128;
        result=result>>8;
        result=OLD_DATA+result;
    }
    else result=OLD_DATA;
    return((short)result);
}

/*
void _SenserFilter_Task(void)    //10HZ
{
	  short Tempdata1,TempdataA,AngleXdata,AngleYdata,AngleZdata,Currdata,Voltdata;
	  Tempdata1=_READ_Tempdata1();
    TempdataA=_READ_TempdataA();	
	  AngleXdata=Get_Angle_Average(1,Angx);
	  AngleYdata=Get_Angle_Average(1,Angy);
	  AngleZdata=Get_Angle_Average(1,Angz);
    SenserVal.AngleX= filter_1(AngleXdata,SenserOld.AngleX,Filternum);
	  SenserOld.AngleX=AngleXdata;
	  SenserVal.AngleY= filter_1(AngleYdata,SenserOld.AngleY,Filternum);
	  SenserOld.AngleY=AngleYdata;
	  SenserVal.AngleZ= filter_1(AngleZdata,SenserOld.AngleZ,Filternum);
	  SenserOld.AngleZ=AngleZdata;
	  SenserVal.Temp1= filter_1(Tempdata1,SenserOld.Temp1,Filternum);
	  SenserOld.Temp1=Tempdata1;
	  SenserVal.TempA= filter_1(TempdataA,SenserOld.TempA,Filternum);
	  SenserOld.TempA=TempdataA;
}	
*/

void _READ_SenserData(SENSER_VAL* Senval)
{
    memcpy(Senval,&SenserVal,sizeof(SenserVal));
}	
void _WRITE_SenserData(SENSER_VAL* Senval)
{
    memcpy(&SenserVal,Senval,sizeof(SenserVal));
}	
void _SensorVal_Angle(u8* Databuf)
{
	 SENSER_VAL SenserVal;
//	 if(ConnCtrl.ValidDev==Addr)//
	 {	 
		  _READ_SenserData(&SenserVal);
		  memcpy(&SenserVal.AngleX,&Databuf[1],2);
		  memcpy(&SenserVal.AngleY,&Databuf[3],2);
		  memcpy(&SenserVal.AngleZ,&Databuf[5],2);
		  _WRITE_SenserData(&SenserVal);
	 }
 }

 
 /*
  *函数名称:
 *输入参数:                         
 *返回参数:
 *函数功能：//判断焊接位置在上或者下
 *函数说明：焊接从上到下，为一个焊层的完成，当从下到上进行起弧成功，则更改为另一个焊层
 			如果焊口码更新，则表示另一个焊口，焊层初始化，否则继续下一焊层；
            所有与分层有关的参数都需要掉电存储，以确保数据完整性；
 *备    注:20191014 -ZCJ&JUJU
 外管口从上到下焊接时（0点钟方向到12点钟方向），X轴从0-》90》0依次变化
                    Z轴从0-》-90度，然后突然变化，从90度递减到零
	焊接从上到下，六点钟方向焊接完成后停弧，
 ************************************************************************/

int weld_angle(void) 
{
     if(  ( as4_comm_result->Weld_Angle.angle_x>=angleX0_L)&&( as4_comm_result->Weld_Angle.angle_x<=angleX0_H)
        //&&( Weld_Angle.angle_y>=angleY0_L)&&( Weld_Angle.angle_y<=angleY0_H)
        &&( as4_comm_result->Weld_Angle.angle_z>=angleZ0_L)&&( as4_comm_result->Weld_Angle.angle_z<=angleZ0_H))
        return _0clock_position ;
else if(  ( as4_comm_result->Weld_Angle.angle_x>=angleX3_L)&&( as4_comm_result->Weld_Angle.angle_x<=angleX3_H)
        //&&( Weld_Angle.angle_y>=angleY3_L)&&( Weld_Angle.angle_y<=angleY3_H)
        &&((( as4_comm_result->Weld_Angle.angle_z>=angleZ3_L1)&&( as4_comm_result->Weld_Angle.angle_z<=angleZ3_H1))
        || (( as4_comm_result->Weld_Angle.angle_z>=angleZ3_L2)&&( as4_comm_result->Weld_Angle.angle_z<=angleZ3_H2)) ))
        return _3clock_position;
else if(  ( as4_comm_result->Weld_Angle.angle_x>=angleX6_L)&&( as4_comm_result->Weld_Angle.angle_x<=angleX6_H)
       // &&( Weld_Angle.angle_y>=angleY6_L)&&( Weld_Angle.angle_y<=angleY6_H)
        &&( as4_comm_result->Weld_Angle.angle_z>=angleZ6_L)&&( as4_comm_result->Weld_Angle.angle_z<=angleZ6_H))
        return _6clock_position;
else
    return Err;
}
 
 
 
 
 