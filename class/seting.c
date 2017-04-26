#include"seting.h"
char inputval = 0;
DATE _currtime;
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
			beebee(1);
			lvsecond=1;
			key=-1;
		};
	}
	if(lvsecond==1)
	{
		LCDcls(); 	
		val = inputbox();
		sprintf(str,"inputhour:=%d",(int)val);
		LCDprintf(str,0);
		if(key==3) {
			beebee(1);
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
		LCDprintf(str,0);
		if(key==3) {
			beebee(1);
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
		LCDprintf(str,0);
		if(key==3) {
		beebee(1);
		lvsecond=0;
		closetime->sec = val;
		key=-1;
		LCDcls(); 
		LCDprintf("----------Waiting",0);
		return 0;
		};	
	} 
	return -1;
}  	
void setcurrenttime()
{	
	if(setclosetime(&_currtime)==0)
	{
		DS1302_SetTime(DS1302_HOUR,_currtime.hour);	
		DS1302_SetTime(DS1302_MINUTE,_currtime.min);
		DS1302_SetTime(DS1302_SECOND,_currtime.sec);
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
void setbeeanle()
{
		char str[30];
	//获取输入的键值
		char key = getkey(0);
		if (key == 3 && lvsecond == 0)	 
		{
			lvsecond = 4;
			LCDcls(); 
			key = -1;
		}
		if(lvsecond == 4)
		{
				if(key==15)
				{
				//上翻页
					enablebee = ~enablebee;
				}
				if(key==11)
				{
				//下翻页
					enablebee = ~enablebee;
				}
				if(enablebee)
				{
					sprintf(str,"SET--BEE----ON----");
					LCDprintf(str,0);
				}
				else
				{
					sprintf(str,"SET--BEE----OFF---");
					LCDprintf(str,0);
				}
				if (key == 3)
				{
					lvsecond=0;
					key = -1;
					beebee(3);
				}
				
		}
}