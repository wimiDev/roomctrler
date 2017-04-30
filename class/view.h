#ifndef __VIEW_H_
#define __VIEW_H_

#define MAXPAGE 8

#include "global.h"

sbit _BEEBEE = P2^6;//beebee

extern unsigned char _page;//显示的页,一级菜单
extern unsigned char lvsecond;//二级菜单，0表示未在二级菜单
extern char trybee;
extern bit enablebee;
extern char msginval;//消息框弹出，0为小消失

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