#ifndef __LIGTHCONTROLLER_H_
#define __LIGTHCONTROLLER_H_
#include"global.h"
sbit _LIGHT_1 = P4^6; //һ�ŵ�
sbit _LIGHT_2 = P4^5; //���ŵ�
sbit _LIGHT_3 = P2^7; //���ŵ�

extern void setlight(char para);
extern void timectrl(void* curr,void* closetime);
extern void numberctrl(unsigned char num);

#endif