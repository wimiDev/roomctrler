#include"global.h"

#ifndef __UART_H_
#define __UART_H_

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L          //系统频率
#define BAUD 9600//115200             //串口波特率

#define NONE_PARITY     0       //无校验
#define ODD_PARITY      1       //奇校验
#define EVEN_PARITY     2       //偶校验
#define MARK_PARITY     3       //标记校验
#define SPACE_PARITY    4       //空白校验	 
#define BUFLENG 15

#define PARITYBIT NONE_PARITY   //定义校验位




sfr T2H   = 0xd6;               //定时器2高8位
sfr T2L   = 0xd7;               //定时器2低8位

#define S1_S0 0x40              //P_SW1.6
#define S1_S1 0x80              //P_SW1.7

typedef void (*CASHCALLBACK)(unsigned char *);

extern unsigned char _uartrecvindex;
extern unsigned char uartrecv[16];
extern char _readed;
extern bit busy;
//extern CASHCALLBACK _cashcallback;
void uartinit();
void SendData(BYTE dat);
void SendString(char *s);
extern unsigned char* getuartbuf();
extern unsigned char getuartbuflen();
extern char getreaded();
extern void setread(char read);

#endif