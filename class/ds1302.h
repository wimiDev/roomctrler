
#ifndef _REAL_TIMER_DS1302_
#define _REAL_TIMER_DS1302_

#include"global.h"

sbit  DS1302_CLK = P0^5;              //实时时钟时钟线引脚 
sbit  DS1302_IO  = P0^6;              //实时时钟数据线引脚 
sbit  DS1302_RST = P0^7;              //实时时钟复位线引脚  
sbit  ACC0 = ACC^0;
sbit  ACC7 = ACC^7;


#define AM(X)	X
#define PM(X)	(X+12)            	  // 转成24小时制
#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84 
#define DS1302_WEEK		0x8A
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_YEAR		0x8C
#define DS1302_RAM(X)	(0xC0+(X)*2)   	//用于计算 DS1302_RAM 地址的宏 

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
}SYSTEMTIME;	//定义的时间类型


extern void DS1302InputByte(unsigned char d); 	//实时时钟写入一字节(内部函数)
extern unsigned char DS1302OutputByte(void); 	//实时时钟读取一字节(内部函数)

extern void Write1302(unsigned char ucAddr, unsigned char ucDa);	//ucAddr: DS1302地址, ucData: 要写的数据 
extern unsigned char Read1302(unsigned char ucAddr);	//读取DS1302某地址的数据
extern void DS1302_SetProtect(bit flag);        //是否写保护
extern void DS1302_SetTime(unsigned char Address, unsigned char Value);        // 设置时间函数
extern void DS1302_GetTime(SYSTEMTIME *Time);
extern void DateToStr(SYSTEMTIME *Time);	 //
extern void TimeToStr(SYSTEMTIME *Time);
extern void Initial_DS1302(void);

#endif