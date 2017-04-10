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
void timetoclose(DATE* curr,DATE* closetime,DATE* opentime)
{
	//setlight(3);
	if(curr->hour > closetime->hour ||
	   curr->hour < opentime->hour	) 
	{
		//setlight(0);
		lightvalue=0;
		timeout = 1;
		return;
	}

	if(curr->hour==closetime->hour&&
	   curr->hour == opentime->hour&&
	   curr->min>closetime->min ||
	   curr->min < opentime->min)
	{
		//setlight(0);
		lightvalue=0;
		timeout = 1;
		return;
	}

	if(curr->hour==closetime->hour&&
	   curr->hour == opentime->hour&&
	   curr->min==closetime->min&&
	   curr->min == opentime->min&&
	   curr->sec > closetime->sec||
	   curr->sec < opentime->sec
		) 
	{
		lightvalue=0;//setlight(0);
		timeout = 1;
		return;
	}
	timeout = 0;	
}

void numberctrl(unsigned char num)
{
	 if(timeout)return;
	 lightvalue = num;
}

