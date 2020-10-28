#ifndef UAPP_SENSER_H
#define UAPP_SENSER_H
#include "sys.h"

typedef struct
{
	short  Current;
	short  Voltage;
  short  Temp1;
	short  Temp2;
	short  TempA;
	short  AngleX;
	short  AngleY;
	short  AngleZ;
	char  AngleStrX[5];
	char  AngleStrY[5];
	char  AngleStrZ[5];	
}SENSER_VAL;

#define Filternum            20

#define _0clock_position 1
#define _3clock_position 2
#define _6clock_position 3


/*角度传感器在下方
#define angleX0_H 40
#define angleX0_L -20
#define angleY0_H 90
#define angleY0_L 0
#define angleZ0_H -1
#define angleZ0_L -60

#define angleX3_H 70
#define angleX3_L -20
#define angleY3_H 90
#define angleY3_L 0
#define angleZ3_H1 90
#define angleZ3_L1 60
#define angleZ3_H2 -50
#define angleZ3_L2 -90

#define angleX6_H 35
#define angleX6_L -20
#define angleY6_H 90
#define angleY6_L 5
#define angleZ6_H 50
#define angleZ6_L 1
*/

/*角度传感器在上方*/
#define angleX0_H 40
#define angleX0_L -20
#define angleY0_H 90
#define angleY0_L 0
#define angleZ0_H 60
#define angleZ0_L 1

#define angleX3_H 70
#define angleX3_L -20
#define angleY3_H 90
#define angleY3_L 0
#define angleZ3_H1 -60
#define angleZ3_L1 -90
#define angleZ3_H2 90
#define angleZ3_L2 50

#define angleX6_H 35
#define angleX6_L -20
#define angleY6_H 90
#define angleY6_L 5
#define angleZ6_H -1
#define angleZ6_L -50

#define SUCC 1
#define Err 0

extern SENSER_VAL   SenserVal,SenserOld;
void _SenserFilter_Task(void);
void _READ_SenserData(SENSER_VAL* Senval);
void _WRITE_SenserData(SENSER_VAL* Senval);
void _SensorVal_Angle(u8* Databuf);
int weld_angle(void) ;
#endif



