#ifndef __LIGTHCONTROLLER_H_
#define __LIGTHCONTROLLER_H_
#include"global.h"
sbit _LIGHT_1 = P4^6; //Ò»ºÅµÆ
sbit _LIGHT_2 = P4^5; //¶þºÅµÆ
sbit _LIGHT_3 = P2^7; //ÈýºÅµÆ

extern void setlight(char para);
extern void timectrl(void* curr,void* closetime);
extern void numberctrl(unsigned char num);

#endif