#ifndef __LIGTHCONTROLLER_H_
#define __LIGTHCONTROLLER_H_
#include"global.h"
sbit _LIGHT_1 = P4^6; //һ�ŵ�
sbit _LIGHT_2 = P4^5; //���ŵ�
sbit _LIGHT_3 = P2^7; //���ŵ�


extern char lightvalue;//����յ��
extern char lightopen[4];//���Ȳ���Ϊ1
extern char lightstate[4];//��ǰ�Ƶ�״̬
extern bit timeout; 
extern char lvtoopen;
extern char lvtooff;

extern void setlight(char para);//���ÿ���յ��++
extern void timectrl();
//����ʱ��ص�
extern void timetoclose(void* curr,void* closetime,void* opentime);
extern void numberctrl(unsigned char num);//�����������ص�
extern char timecmp(void* time1,void* time2);
extern void lightctrl(char*para,unsigned char size,unsigned char num);


#endif