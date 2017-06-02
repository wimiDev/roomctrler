#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "global.h"

typedef struct _DATE
{
	unsigned char mon;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;	
}DATE;

extern DATE currenttime;//��ǰʱ��
extern DATE closetime;//�ص�ʱ��
extern DATE opentime;//�ص�ʱ��
extern unsigned char paralist[4]; 
extern unsigned char number;
extern void controllerinit();
extern void parafilter(unsigned char* list,char size);
extern void getcutrrenttime();
extern void cashcard(unsigned char *resdata);

#endif