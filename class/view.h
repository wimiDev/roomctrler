#ifndef __VIEW_H_
#define __VIEW_H_

#define MAXPAGE 8

#include "global.h"

sbit _BEEBEE = P2^6;//beebee

extern unsigned char _page;//��ʾ��ҳ,һ���˵�
extern unsigned char lvsecond;//�����˵���0��ʾδ�ڶ����˵�
extern char trybee;
extern bit enablebee;
extern char msginval;//��Ϣ�򵯳���0ΪС��ʧ

extern void trunpage();
extern void beebee(char inval);
extern void beehandler();
extern void showbeeable();
extern void showlightsta();
extern void showtimeval(void* time,char*name);
extern void uiupdater();
extern void showmsg(char str[],char inval);
extern char msgviewhandler();

#endif