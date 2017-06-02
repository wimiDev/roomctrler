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
    SCON = 0x50;                //8λ�ɱ䲨����
#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
    SCON = 0xda;                //9λ�ɱ䲨����,У��λ��ʼΪ1
#elif (PARITYBIT == SPACE_PARITY)
    SCON = 0xd2;                //9λ�ɱ䲨����,У��λ��ʼΪ0
#endif

    T2L = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
    AUXR |= 0x01;               //ѡ��ʱ��2Ϊ����1�Ĳ����ʷ�����
    ES = 1;                     //ʹ�ܴ���1�ж�
    EA = 1;
}
/*----------------------------
UART �жϷ������
-----------------------------*/
void Uart() interrupt 4 using 1
{
    if (RI)
    {
        RI = 0;                 //���RIλ
				_handlercash();
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
        busy = 0;               //��æ��־
    }
}
/*----------------------------
���ʹ�������
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);               //�ȴ�ǰ������ݷ������
    ACC = dat;                  //��ȡУ��λP (PSW.0)
    if (P)                      //����P������У��λ
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;                //����У��λΪ0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;                //����У��λΪ1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;                //����У��λΪ1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;                //����У��λΪ0
#endif
    }
    busy = 1;
    SBUF = ACC;                 //д���ݵ�UART���ݼĴ���
}

/*----------------------------
�����ַ���
----------------------------*/
void SendString(char *s)
{  	
	unsigned char i=0;
    while (*(s+i))                  //����ַ���������־
    {
        SendData(*(s+i));         //���͵�ǰ�ַ�
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
*ͨ������ʽ��
*  7F 		0E 			00 		A0 	 00 ��n�� 90 00  63
*����ͷ ����� ��ַ ������ 		���� 			У��
*/
void _handlercash()
{
		char _recvbuf = 0;
		if(getreaded() != 1) 
		{
			return;//������δ����
		}
		_recvbuf = SBUF;��
		if(_uartrecvindex < 5 && (_recvbuf != _starttag[_uartrecvindex]))
		{
			_uartrecvindex = 0;
			setread(-1);//�Ƿ�����
			return;
		}
		if(_uartrecvindex >= 5)uartrecv[_uartrecvindex - 5] = _recvbuf;
		_uartrecvindex++;
		//if(_uartrecvindex == 5) _uartrecvindex = 0;
		if (_uartrecvindex > 15)
		{
			_uartrecvindex -= 5;
			//�����������
			setread(0);
		}
		
}
