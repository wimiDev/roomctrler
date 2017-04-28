#include"ligthcontroller.h"

char lightvalue = 0;
bit timeout = 1;
char lightopen[4];
char lightstate[4];//当前灯的状态
char lvtono = 5;//在当前亮度可以开灯
char lvtooff = 4;//在当前亮度可关灯

void setlight(char para)
{  	
	 _LIGHT_1 = 1;
	 _LIGHT_2 =	1;
	 _LIGHT_3 =	1;
		lightstate[0]=0;
		lightstate[1]=0;
		lightstate[2]=0;
		lightstate[3]=0;
	if(para > 0 && lightopen[0])
		{
			_LIGHT_1 = 0;
			lightstate[0]=1;
			para--;
		}
	if(para > 0 && lightopen[1])
		{
			_LIGHT_2 = 0;
			lightstate[1]=1;
			para--;
		}
	if(para > 0 && lightopen[2])
		{
			_LIGHT_3 = 0;
			lightstate[2]=1;
			para--;
		}
}
void timectrl()
{	
	timetoclose(&currenttime,&closetime,&opentime);
	//numberctrl(number);
	setlight(lightvalue);		
}
void lightctrl(char*para,unsigned char _size,unsigned char number)
{
	unsigned char index = 0;
	unsigned char lightpoint = 0;//有几个点亮度是足够的。
	lightvalue = 0;
	for(index=0;index<_size;index++)
	{
		if(para[index] > lvtono)
		{
			lightopen[index]=1;
			lightvalue++;
		}
		if(para[index] <= lvtooff)
		{
			lightopen[index] = 0;
		}
	}
	lightpoint = _size - lightvalue;
	if(number > lightpoint) 
	{
		lightvalue = number - lightpoint;
	}
	else
	{
		lightvalue = 0;
	}
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
void timetoclose(DATE* curr,DATE* closetime,DATE* opentime)
{
	if(timecmp(closetime,opentime) > 0)
	{
		if(timecmp(curr,opentime) >0&&
		timecmp(curr,closetime) <0 )
		{
			timeout = 0;
			return;		
		}
		timeout=1;
		lightvalue=0;		
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
	 if(num <= lightvalue)
	 {
	 	lightvalue = num;
	 }
}

