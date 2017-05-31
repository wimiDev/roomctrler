#include"ligthcontroller.h"

char lightvalue = 0;
bit timeout = 1;
char lightopen[4];
char lightstate[4];//当前灯的状态
char lvtoopen = 5;//在当前亮度可以开灯
char lvtooff = 0;//在当前亮度可关灯

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

/*
*BUG01:由于数据更新速率的问题，可能会带来采集点亮度数据不是实时
*同步的问题，会引发全部灯光熄灭再恢复正常。暂时解决办法是增加灯
*光处理方法的刷新时间间隔，确保数据能全部同步。
*/

void lightctrl(char*para,unsigned char _size,unsigned char number)
{
	unsigned char index = 0;
	unsigned char lightpoint = 0;//有几个点亮度是足够的
	lightvalue = 0;//需要点亮多少个灯
	
	for(index = 0;index < _size;index++)
	{
		lightopen[index] = 0;
		//如果这盏灯已经开了，就默认这个点的亮度是足够的
		if(lightstate[index]) 
		{
			lightopen[index] = 1;
			++lightvalue;
		}
		//如果这个采集点的亮度不足标记这盏灯可以开
		else if(para[index] > lvtoopen)
		{
			lightopen[index] = 1;
			++lightvalue ;
		}
		//如果这个采集点的亮度过高标记这盏灯可以关
		if(para[index] <= lvtooff )
		{
			lightopen[index] = 0;
		}
	}
	if(lightvalue>4) lightvalue = 4;
	//计算有几个不需要开的灯
	lightpoint = _size - lightvalue;
	//根据现在有多少人来计算需要开多少盏灯
	lightvalue = number - lightpoint;
	if(lightvalue < 0) lightvalue = 0;
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

