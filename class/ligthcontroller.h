#ifndef __LIGTHCONTROLLER_H_
#define __LIGTHCONTROLLER_H_
#include"global.h"
sbit _LIGHT_1 = P4^6; //一号灯
sbit _LIGHT_2 = P4^5; //二号灯
sbit _LIGHT_3 = P2^7; //三号灯


extern char lightvalue;//开几盏灯
extern char lightopen[4];//亮度不足为1
extern char lightstate[4];//当前灯的状态
extern bit timeout; 
extern char lvtoopen;
extern char lvtooff;

extern void setlight(char para);//设置开几盏灯++
extern void timectrl();
//根据时间关灯
extern void timetoclose(void* curr,void* closetime,void* opentime);
extern void numberctrl(unsigned char num);//根据人数开关灯
extern char timecmp(void* time1,void* time2);
extern void lightctrl(char*para,unsigned char size,unsigned char num);


#endif