#ifndef __LCD5110_H__
#define __LCD5110_H__

#include "global.h"

#define uchar unsigned char
#define uint unsigned int
#define _MAX_X = 10
#define _MAX_Y = 4

sbit LCD_LIGHT = P2^3; //����
sbit    sce = P4^4;  //Ƭѡ
sbit    res = P4^3;  //��λ,0��λ
sbit    dc  = P2^0;  //1д���ݣ�0дָ��
sbit    sdin = P2^1;  //����
sbit    sclk = P2^2;  //ʱ��
typedef struct __POINT 
{
	unsigned char x;
	unsigned char y;
}POINT;

extern POINT slipos;
extern unsigned char drawindex;
extern char drawbuf[30];
extern char drawnowbuf[30];

extern void delay_1ms(void);//1ms��ʱ����
extern void LCD_write_byte(unsigned char dt, unsigned char command);
/*---------------------------------------
LCD_init: 3310LCD��ʼ��
��д���ڣ�20080918 
-----------------------------------------  */
extern void LCD_init(void);
/*-------------------------------------------
LCD_set_XY: ����LCD���꺯��
���������X��0��83  Y��0��5
��д���ڣ�20080918 
---------------------------------------------*/
void LCD_set_XY(unsigned char X, unsigned char Y);
/*------------------------------------------
LCD_clear: LCD��������
��д���ڣ�20080918 
--------------------------------------------*/
void LCD_clear(void);
/*---------------------------------------------
LCD_write_shu: ��ʾ8����*16���ߣ�������������ĸ���ŵȰ����
���������c����ʾ���ַ���
��д���ڣ�20080918 
-----------------------------------------------*/
void LCDwritechar(unsigned char row, unsigned char page,unsigned char c); //row:�� page:ҳ dd:�ַ�
void LCDcls();
void LCDprintf(char*str,char pos);
void cleandrawbuf();
void LCDdraw(char* drawbuf,char* drawnow);
void LCDclearpos(unsigned char row, unsigned char page);

#endif