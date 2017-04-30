#include"ligthcontroller.h"

char lightvalue = 0;
bit timeout = 1;
char lightopen[4];
char lightstate[4];//��ǰ�Ƶ�״̬
char lvtoopen = 5;//�ڵ�ǰ���ȿ��Կ���
char lvtooff = 0;//�ڵ�ǰ���ȿɹص�

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
	unsigned char lightpoint = 0;//�м������������㹻��
//	char str[30];
	lightvalue = 0;//��Ҫ�������ٸ���
	
	for(index=0;index<_size;index++)
	{
		if(lightstate[index]) 
		{
			lightvalue= ++lightvalue % 4;
		}else if(para[index] > lvtoopen)
		{
			lightopen[index]=1;
			lightvalue= ++lightvalue % 4;
		}
		
		if(para[index] <= lvtooff )
		{
//			sprintf(str,"CLOSE ID: %d",(int)index);
//			LCDprintf(str,0);
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
			//δ������ʱ��
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

