#include"schduler.h"

void update()
{
	char i=0;
	NRFSetRXMode();//����Ϊ����ģʽ
	GetDate();//��ʼ�������� 	
	parafilter(RevTempDate0,RX_DATA_WITDH);
}

void sch1s()
{
	getcutrrenttime();
	lightctrl(paralist,3,number);
	timectrl();//����ʱ��ص�
	
} 
void sch005s()
{
	
	keyhandler();
}
void sch01s()
{	
		cashcard(getuartbuf());
}
void sch03s()
{
	beehandler();
}
void sch05s()
{
	uiupdater();
}