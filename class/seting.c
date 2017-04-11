#include"seting.h"
char inputval = 0;
char setclosetime(DATE* closetime)
{
	char str[30];
	//获取输入的键值
	char key = getkey(0);
	char val = -1;	
	if(lvsecond==0)
	{
		if (key==3)	 
		{
		lvsecond=1;
		key=-1;
		};
	}
	if(lvsecond==1)
	{
		LCDcls(); 	
		val = inputbox();
		sprintf(str,"inputhour:=%d",(int)val);
		LCDprintf(str);
		if(key==3) {
		lvsecond=2;
		closetime->hour = val;
		key=-1;
		};	
	} 
	if(lvsecond==2)
	{
		LCDcls(); 	
		val = inputbox();
		sprintf(str,"inputmin:=%d",(int)val);
		LCDprintf(str);
		if(key==3) {
		lvsecond=3;
		closetime->min = val;
		key=-1;
		};	
	} 
	if(lvsecond==3)
	{
		LCDcls(); 	
		val = inputbox();
		sprintf(str,"inputsec:=%d",(int)val);
		LCDprintf(str);
		if(key==3) {
		lvsecond=0;
		closetime->sec = val;
		key=-1;
		return 0;
		};	
	} 
	return -1;
}  	
void setcurrenttime(DATE* curr)
{
	DATE currtime;
	if(setclosetime(&currtime)==0)
	{
		DS1302_SetTime(DS1302_HOUR,currtime.hour);	//??????????10??54??30
		DS1302_SetTime(DS1302_MINUTE,currtime.min);
		DS1302_SetTime(DS1302_SECOND,currtime.sec);
	} 	
}
void setopentime(DATE* opentime)
{
	setclosetime(opentime);
}
char inputbox()
{
	char key = getkey(0); 
	if(key!=-1&&getnumber(key)!=-1)
	{
		inputval = (inputval*10 + getnumber(key));
	} 
//	//确定
//	if(key==3)return inputval;
	if(key==14)
	{
		//退格
		inputval = (inputval-inputval%10)/10;		
	}  	
	return inputval;
}