#include"schduler.h"

void update()
{
	//char sendstr[20];
	char i=0;
	NRFSetRXMode();//����Ϊ����ģʽ
	GetDate();//��ʼ������	 	
	parafilter(RevTempDate0,RX_DATA_WITDH);
}

void sch1s()
{
	uiupdater();
	getcutrrenttime();
	timectrl();//����ʱ��ص�
} 
void sch02s()
{	
	cashcard(getuartbuf());
	keyhandler();
}