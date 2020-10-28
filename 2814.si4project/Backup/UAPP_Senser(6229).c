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
  *��������:
 *�������:                         
 *���ز���:
 *�������ܣ�//�жϺ���λ�����ϻ�����
 *����˵�������Ӵ��ϵ��£�Ϊһ���������ɣ������µ��Ͻ����𻡳ɹ��������Ϊ��һ������
 			�����������£����ʾ��һ�����ڣ������ʼ�������������һ���㣻
            ������ֲ��йصĲ�������Ҫ����洢����ȷ�����������ԣ�
 *��    ע:20191014 -ZCJ&JUJU
 ��ܿڴ��ϵ��º���ʱ��0���ӷ���12���ӷ��򣩣�X���0-��90��0���α仯
                    Z���0-��-90�ȣ�Ȼ��ͻȻ�仯����90�ȵݼ�����
	���Ӵ��ϵ��£������ӷ��򺸽���ɺ�ͣ����
 ************************************************************************/

int weld_angle(void) 
{
     if(  ( SenserVal.AngleX >= angleX0_L)&&( SenserVal.AngleX <= angleX0_H )
        //&&( Weld_Angle.angle_y>=angleY0_L)&&( Weld_Angle.angle_y<=angleY0_H)
        &&( SenserVal.AngleZ >= angleZ0_L )&&( SenserVal.AngleZ <= angleZ0_H))
        return _0clock_position ;
else if(  ( SenserVal.AngleX >= angleX3_L )&&( SenserVal.AngleX <= angleX3_H)
        //&&( Weld_Angle.angle_y>=angleY3_L)&&( Weld_Angle.angle_y<=angleY3_H)
        &&((( SenserVal.AngleZ >= angleZ3_L1 )&&( SenserVal.AngleZ <= angleZ3_H1))
        || (( SenserVal.AngleZ >= angleZ3_L2 )&&( SenserVal.AngleZ <= angleZ3_H2)) ))
        return _3clock_position;
else if(  ( SenserVal.AngleX >= angleX6_L )&&( SenserVal.AngleX <= angleX6_H )
       // &&( Weld_Angle.angle_y>=angleY6_L)&&( Weld_Angle.angle_y<=angleY6_H)
        &&( SenserVal.AngleZ >= angleZ6_L )&&( SenserVal.AngleZ <= angleZ6_H ))
        return _6clock_position;
else
    return Err;
}
 
 
 
 
 