#include"global.h"

#ifndef __UART_H_
#define __UART_H_

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 11059200L          //ϵͳƵ��
#define BAUD 9600//115200             //���ڲ�����

#define NONE_PARITY     0       //��У��
#define ODD_PARITY      1       //��У��
#define EVEN_PARITY     2       //żУ��
#define MARK_PARITY     3       //���У��
#define SPACE_PARITY    4       //�հ�У��	 
#define BUFLENG 15

#define PARITYBIT NONE_PARITY   //����У��λ




sfr T2H   = 0xd6;               //��ʱ��2��8λ
sfr T2L   = 0xd7;               //��ʱ��2��8λ

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