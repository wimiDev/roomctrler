#include"ligthcontroller.h"

char lightvalue = 0;
bit timeout = 1;

void setlight(char para)
{  	
	 _LIGHT_1 = 0;
	 _LIGHT_2 =	0;
	 _LIGHT_3 =	0;
	if(para>=1) _LIGHT_1 = 1;
	if(para>=2) _LIGHT_2 = 1;
	if(para>=3) _LIGHT_3 = 1;
}
void timectrl()
{	
	timetoclose(&currenttime,&closetime,&opentime);
	numberctrl(number);
	setlight(lightvalue);		
}
char timecmp(DATE* time1,DATE* time2)
{
	if(time1->hour > time2->hour) 
	{
		return 1;
	}

	if(time1->hour == time2->hour&&
	   time1->min > time2->min )
	{
		return 1;
	}
	if(time1->hour == time2->hour&&
	   time1->min == time2->min&&
	   time1->sec > time2->sec) 
	{
		return 1;
	}
	return -1;
}
void timeadd(DATE* sum,DATE* add1)
{
	sum->sec += add1->sec;
	sum->min += sum->sec / 60;
	sum->sec = sum->sec % 60;
	
	sum->min += add1->min;
	sum->hour +=  sum->min / 60;
	sum->min = sum->min % 60;

	sum->hour += add1->hour;
}
void timetoclose(DATE* curr,DATE* closetime,DATE* opentime)
{
	if(timecmp(closetime,opentime) > 0)
	{
		if(timecmp(curr,opentime) >0)
		{
			timeout = 0;	
		}
		if(timecmp(curr,closetime))
		{
			timeout=1;
			lightvalue=0;
			return;		
		}		
	}
	else
	{
		if(timecmp(curr,opentime) < 0 && 
			timecmp(curr,closetime) > 0)
		{
			//未到开灯时间
			timeout=1;
			lightvalue=0;
			return;
		}
		timeout = 0;	
	}		
}

void numberctrl(unsigned char num)
{
	 if(timeout)return;
	 lightvalue = num;
}

