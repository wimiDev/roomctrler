#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_
#define MAXPAGE 4

#include"global.h"



typedef struct _DATE
{
	unsigned char mon;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;	
}DATE;

extern DATE currenttime;//当前时间
extern DATE closetime;//关灯时间
extern unsigned char _page;//显示的页,一级菜单
extern unsigned char lvsecond;//二级菜单，0表示未在二级菜单
extern unsigned char paralist[4]; 
extern unsigned char number;
extern void controllerinit();
extern void setparas(char*list);
extern void parafilter(unsigned char* list,char size);
extern void getcutrrenttime();
extern void showtimeval(DATE* time,char*name);
extern void uiupdater();
extern void cashcard(unsigned char *resdata);
extern void trunpage();


#endif