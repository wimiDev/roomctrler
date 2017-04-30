
#include"global.h"

long int osclock = 0;
void C51Timer0Init();
void schdulerswitch();

/************************������********************/
void main()
{
   uartinit();
   NRF24L01Int();
   C51Timer0Init();
   controllerinit();
   SendString("init\r\n");
   while(1) schdulerswitch();
}
void schdulerswitch()
{
	 update();
	 if(osclock%1000 ==0 )sch1s();

	 if(osclock%50 == 0)sch005s();
	
	 if(osclock%100 == 0)sch01s();
	
	 if(osclock%300 == 0) sch03s();
	
	 if(osclock%500 == 0) sch05s();
}
void C51Timer0Init()
{  	
	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x88;		//���ö�ʱ��ֵ
	TH0 = 0x96;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	ET0 = 1; //ʹ�ܶ�ʱ��0�ж�
    EA = 1;

}
void Timer0Interrupt() interrupt 1 using 2
{
	   osclock = (osclock+1)%3000;
	   if(osclock%1000 == 0)
	   {
	   	 P55 = ~P55;
	   }
}
