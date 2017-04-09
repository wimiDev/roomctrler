
#ifndef _REAL_TIMER_DS1302_
#define _REAL_TIMER_DS1302_

#include"global.h"

sbit  DS1302_CLK = P0^5;              //ʵʱʱ��ʱ�������� 
sbit  DS1302_IO  = P0^6;              //ʵʱʱ������������ 
sbit  DS1302_RST = P0^7;              //ʵʱʱ�Ӹ�λ������  
sbit  ACC0 = ACC^0;
sbit  ACC7 = ACC^7;


#define AM(X)	X
#define PM(X)	(X+12)            	  // ת��24Сʱ��
#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84 
#define DS1302_WEEK		0x8A
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_YEAR		0x8C
#define DS1302_RAM(X)	(0xC0+(X)*2)   	//���ڼ��� DS1302_RAM ��ַ�ĺ� 

typedef struct __SYSTEMTIME__
{
	unsigned char Second;
	unsigned char Minute;
	unsigned char Hour;
	unsigned char Week;
	unsigned char Day;
	unsigned char Month;
	unsigned char  Year;
	unsigned char DateString[9];
	unsigned char TimeString[9];
}SYSTEMTIME;	//�����ʱ������


extern void DS1302InputByte(unsigned char d); 	//ʵʱʱ��д��һ�ֽ�(�ڲ�����)
extern unsigned char DS1302OutputByte(void); 	//ʵʱʱ�Ӷ�ȡһ�ֽ�(�ڲ�����)

extern void Write1302(unsigned char ucAddr, unsigned char ucDa);	//ucAddr: DS1302��ַ, ucData: Ҫд������ 
extern unsigned char Read1302(unsigned char ucAddr);	//��ȡDS1302ĳ��ַ������
extern void DS1302_SetProtect(bit flag);        //�Ƿ�д����
extern void DS1302_SetTime(unsigned char Address, unsigned char Value);        // ����ʱ�亯��
extern void DS1302_GetTime(SYSTEMTIME *Time);
extern void DateToStr(SYSTEMTIME *Time);	 //
extern void TimeToStr(SYSTEMTIME *Time);
extern void Initial_DS1302(void);

#endif