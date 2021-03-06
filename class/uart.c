#include"uart.h"
 bit busy=0;
 unsigned char uartrecv[16];
 unsigned char _uartrecvindex = 0;
 char _readed = 1;
 unsigned char _starttag[5] = {0x7F,0x0E,0x00,0xA0,0x00};

void uartinit()
{
    ACC = P_SW1;
    ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
    P_SW1 = ACC;                //(P3.0/RxD, P3.1/TxD)
    
//  ACC = P_SW1;
//  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=1 S1_S1=0
//  ACC |= S1_S0;               //(P3.6/RxD_2, P3.7/TxD_2)
//  P_SW1 = ACC;  
//  
//  ACC = P_SW1;
//  ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=1
//  ACC |= S1_S1;               //(P1.6/RxD_3, P1.7/TxD_3)
//  P_SW1 = ACC;  
// 	_cashcallback = &cashcard;
#if (PARITYBIT == NONE_PARITY)
    SCON = 0x50;                //8位可变波特率
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9位可变波特率,校验位初始为1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9位可变波特率,校验位初始为0
#endif

    T2L = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2为1T模式, 并启动定时器2
    AUXR |= 0x01;               //选择定时器2为串口1的波特率发生器
    ES = 1;                     //使能串口1中断
    EA = 1;
}
/*----------------------------
UART 中断服务程序
-----------------------------*/
void Uart() interrupt 4 using 1
{
    if (RI)
    {
        RI = 0;                 //清除RI位
				_handlercash();
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        busy = 0;               //清忙标志
    }
}
/*----------------------------
发送串口数据
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);               //等待前面的数据发送完成
    ACC = dat;                  //获取校验位P (PSW.0)
    if (P)                      //根据P来设置校验位
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;                //设置校验位为0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;                //设置校验位为1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;                //设置校验位为1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;                //设置校验位为0
#endif
    }
    busy = 1;
    SBUF = ACC;                 //写数据到UART数据寄存器
}

/*----------------------------
发送字符串
----------------------------*/
void SendString(char *s)
{  	
	unsigned char i=0;
    while (*(s+i))                  //检测字符串结束标志
    {
        SendData(*(s+i));         //发送当前字符
		i++;
    }
}
unsigned char* getuartbuf()
{
	return 	uartrecv;
}
unsigned char getuartbuflen()
{
	return _uartrecvindex;
}
char getreaded()
{
	return _readed;
}
void setread(char read)
{
	if(read==1) _uartrecvindex = 0;
   _readed = read;
}
/*
*通信帖格式：
*  7F 		0E 			00 		A0 	 00 …n… 90 00  63
*命令头 命令长度 地址 命令字 		数据 			校验
*/
void _handlercash()
{
		char _recvbuf = 0;
		if(getreaded() != 1) 
		{
			return;//数据尚未处理
		}
		_recvbuf = SBUF;，
		if(_uartrecvindex < 5 && (_recvbuf != _starttag[_uartrecvindex]))
		{
			_uartrecvindex = 0;
			setread(-1);//非法数据
			return;
		}
		if(_uartrecvindex >= 5)uartrecv[_uartrecvindex - 5] = _recvbuf;
		_uartrecvindex++;
		//if(_uartrecvindex == 5) _uartrecvindex = 0;
		if (_uartrecvindex > 15)
		{
			_uartrecvindex -= 5;
			//接收数据完毕
			setread(0);
		}
		
}
