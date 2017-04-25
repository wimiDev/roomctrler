#include"schduler.h"

void update()
{
	char i=0;
	NRFSetRXMode();//设置为接收模式
	GetDate();//开始接收数据 	
	parafilter(RevTempDate0,RX_DATA_WITDH);
}

void sch1s()
{
	uiupdater();
	getcutrrenttime();
	lightctrl(paralist,3);
	timectrl();//根据时间关灯
	
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