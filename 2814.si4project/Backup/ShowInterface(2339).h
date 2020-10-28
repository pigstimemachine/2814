#ifndef __SHOWINTERFACE_H
#define __SHOWINTERFACE_H			  	 
#include "sys.h"
#include "stdlib.h"	

typedef struct
{
	int page;
	
}INTERFACE;
#define PageMain 	1
#define PageAbout	3
extern INTERFACE Interface;
int WhiceInterface(void);

#endif  
	 



