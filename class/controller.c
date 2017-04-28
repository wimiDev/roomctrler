#include"controller.h"
unsigned char paralist[4];
unsigned char number = 0;
DATE currenttime;
DATE closetime;//关灯时间
DATE opentime;//开灯时间

void controllerinit()
{	 
	_BEEBEE = 0;
	Initial_DS1302();
//	DS1302_SetTime(DS1302_HOUR,10);	//??????????10??54??30
//	DS1302_SetTime(DS1302_MINUTE,54);
//	DS1302_SetTime(DS1302_SECOND,30); 
	dbinit();
  LCD_init();  //初始化LCD模块 
	LCDcls(); //清屏幕	
	closetime.hour = 0;
	closetime.min = 0;
	closetime.sec = 0;  

	opentime.hour = 0;
	opentime.min = 0;
	opentime.sec = 0; 
	beebee(3);
}

void parafilter(unsigned char* list,char size)
{
	char i=0;
	unsigned char val = 0;
	char id =  list[0]-'0';
	if (RevTempDate0[0]==0)
	{
		return;
	}
	for(i=1;i<size;i++)
	{
		val = (val*10)+(list[i]-'0');		
	}
	if(id==1)
	{
		paralist[0] = val;	
	}
	else if(id==2)
	{
		paralist[1] = val;	
	} 
	else if(id==3)
	{
		paralist[2] = val;	
	}
	else if(id==4)
	{
		paralist[3] = val;
	}
	else
	{
		for(i=0;i<5;++i)
		{
			RevTempDate0[i] = 0;	
		}
		return;
	}	
	//置空接收区
	for(i=0;i<5;++i)
	{
		RevTempDate0[i] = 0;	
	}
}
void getcutrrenttime()
{  
	SYSTEMTIME CurrentTime;
	DS1302_GetTime(&CurrentTime);
	TimeToStr(&CurrentTime);
	currenttime.hour=CurrentTime.Hour;
	currenttime.min=CurrentTime.Minute;
	currenttime.sec=CurrentTime.Second;
}

void cashcard(unsigned char *resdata)
{
	unsigned char index = 0; 
	unsigned char len = getuartbuflen();
	unsigned char idsta[10]; 
	unsigned char insertindex = 0;
	unsigned char selectindex = 0;
	char str[30] = "cashcard"; 
	if(getreaded()== 1 ) return;//没有数据更新
	LCDcls();
	if(getreaded() == -1)
	{
		beebee(5);
		showmsg("SUPPORT-ID-CARD-ONLY!",3);
		setread(1);
		return;
	}
	beebee(2);
	for(index=0;index< len;index++)
	{	
		if(index<len)//index>4&&
		{ 
			idsta[index] = *(resdata+index);//-5	
		}
		*(resdata+index) = 0;//清空数据
	}
	selectindex =  selectid(idsta);
	if(selectindex != UNKNOWERROR)
	{
		//查找到了
		number--;
		delectidbyindex(selectindex);
		sprintf(str,"NO.%d-OUT-;number-is.%d.",(int)selectindex,(int)number);
	}
	else
	{
		//没有找到
		insertindex = insertid(idsta);
		if(insertindex == UNKNOWERROR) 
		{
			LCDprintf("--FULL--",0);
			LCDprintf("--callme--13077661594",-1);
			return;
		} 
		number++;
		sprintf(str,"NO.%d-IN-;number-is-%d.",(int)insertindex,(int)number);
	}
	showmsg(str,3);
	setread(1);
}
