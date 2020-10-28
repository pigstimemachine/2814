#ifndef __SHOWINTERFACE_H
#define __SHOWINTERFACE_H			  	 
#include "sys.h"
#include "stdlib.h"	

typedef struct
{
	int page;
	int PageChangeFlag;
	
}INTERFACE;
#define PageMain 		1
#define PageEquipment	2
#define PageAbout		3
extern INTERFACE Interface;
int WhichInterface(void);
int IsInterfaceChange(void);
int InterfaceChangeFlag(void);

#endif  
	 



