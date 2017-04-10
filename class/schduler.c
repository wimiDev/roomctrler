#include"schduler.h"

void update()
{
	//char sendstr[20];
	char i=0;
	NRFSetRXMode();//设置为接收模式
	GetDate();//开始接受数	 	
	parafilter(RevTempDate0,RX_DATA_WITDH);
}

void sch1s()
{
	uiupdater();
	getcutrrenttime();
	timectrl();//根据时间关灯
} 
void sch02s()
{	
	cashcard(getuartbuf());
	keyhandler();
}