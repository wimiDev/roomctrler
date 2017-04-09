#include"ligthcontroller.h"

void setlight(char para)
{  	
	 _LIGHT_1 = 0;
	 _LIGHT_2 =	0;
	 _LIGHT_3 =	0;
	if(para>=1) _LIGHT_1 = 1;
	if(para>=2) _LIGHT_2 = 1;
	if(para>=3) _LIGHT_3 = 1;
}
void timectrl(DATE*curr,DATE*closetime)
{	
	setlight(3);
	if(curr->hour>closetime->hour) 
	{
		setlight(0);
		return;
	}

	if(curr->hour==closetime->hour&&
	curr->min>closetime->min)
	{
		setlight(0);
		return;
	}

	if(curr->hour==closetime->hour&&
	curr->min==closetime->min&&
	curr->sec>closetime->sec)setlight(0);			
}
void numberctrl(unsigned char num)
{
	
}

