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
	uiupdater();
	getcutrrenttime();
	lightctrl(paralist,3);
	timectrl();//����ʱ��ص�
	
} 
void sch01s()
{	
	cashcard(getuartbuf());
	keyhandler();
}
void sch03s()
{
	beehandler();
}