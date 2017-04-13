#ifndef __LIGTHCONTROLLER_H_
#define __LIGTHCONTROLLER_H_
#include"global.h"
sbit _LIGHT_1 = P4^6; //一号灯
sbit _LIGHT_2 = P4^5; //二号灯
sbit _LIGHT_3 = P2^7; //三号灯

extern char lightvalue;//开几盏灯
extern bit lightsval[4];//灯状态映射
extern bit timeout; 
extern void setlight(char para);//设置开几盏灯++
extern void timectrl();
//根据时间关灯
extern void timetoclose(void* curr,void* closetime,void* opentime);
extern void numberctrl(unsigned char num);//根据人数开关灯
extern char timecmp(void* time1,void* time2);
extern void lightctrl(char*para,unsigned char size);

#endif