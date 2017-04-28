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
	getcutrrenttime();
	lightctrl(paralist,3,number);
	timectrl();//根据时间关灯
	
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