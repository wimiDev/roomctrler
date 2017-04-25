#ifndef __LCD5110_H__
#define __LCD5110_H__

#include "global.h"

#define uchar unsigned char
#define uint unsigned int
#define _MAX_X = 10
#define _MAX_Y = 4

sbit LCD_LIGHT = P2^3; //背光
sbit    sce = P4^4;  //片选
sbit    res = P4^3;  //复位,0复位
sbit    dc  = P2^0;  //1写数据，0写指令
sbit    sdin = P2^1;  //数据
sbit    sclk = P2^2;  //时钟
typedef struct __POINT 
{
	unsigned char x;
	unsigned char y;
}POINT;

extern POINT slipos;
extern unsigned char drawindex;
extern char drawbuf[30];
extern char drawnowbuf[30];

extern void delay_1ms(void);//1ms延时函数
extern void LCD_write_byte(unsigned char dt, unsigned char command);
/*---------------------------------------
LCD_init: 3310LCD初始化
编写日期：20080918 
-----------------------------------------  */
extern void LCD_init(void);
/*-------------------------------------------
LCD_set_XY: 设置LCD坐标函数
输入参数：X：0－83  Y：0－5
编写日期：20080918 
---------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y);
/*------------------------------------------
LCD_clear: LCD清屏函数
编写日期：20080918 
--------------------------------------------*/
void LCD_clear(void);
/*---------------------------------------------
LCD_write_shu: 显示8（宽）*16（高）点阵列数字字母符号等半角类
输入参数：c：显示的字符；
编写日期：20080918 
-----------------------------------------------*/
void LCDwritechar(unsigned char row, unsigned char page,unsigned char c); //row:列 page:页 dd:字符
void LCDcls();
void LCDprintf(char*str,char pos);
void cleandrawbuf();
void LCDdraw(char* drawbuf,char* drawnow);
void LCDclearpos(unsigned char row, unsigned char page);

#endif