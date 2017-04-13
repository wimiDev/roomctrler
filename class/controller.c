#include"controller.h"
unsigned char paralist[4];
unsigned char _page = 0;
unsigned char lvsecond = 0;
 unsigned char number = 0;
DATE currenttime;
DATE closetime;//关灯时间
DATE opentime;//开灯时间

void controllerinit()
{	 	
	Initial_DS1302();
	DS1302_SetTime(DS1302_HOUR,10);	//??????????10??54??30
	DS1302_SetTime(DS1302_MINUTE,54);
	DS1302_SetTime(DS1302_SECOND,30); 
	dbinit();

	closetime.hour = 0;
	closetime.min = 0;
	closetime.sec = 0;  

	opentime.hour = 0;
	opentime.min = 0;
	opentime.sec = 0; 

  	LCD_init();  //初始化LCD模块 
	LCDcls(); //清屏幕	
}
//void setparas(char*list)
//{
//
//}
void parafilter(unsigned char* list,char size)
{
	char i=0;
	//char sendstr[30];
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
//	char str[20];
	SYSTEMTIME CurrentTime;
	DS1302_GetTime(&CurrentTime);
	//DateToStr(&CurrentTime);
	TimeToStr(&CurrentTime);
	currenttime.hour=CurrentTime.Hour;
	currenttime.min=CurrentTime.Minute;
	currenttime.sec=CurrentTime.Second;
//	sprintf(str,"[%d:%d:%d]",(int)currenttime.hour,(int)currenttime.min,(int)currenttime.sec);
//	//SendString(str);
//	LCDcls();
//	LCDprintf("-TIME-NOW-");
//	LCDprintf(str);
}
void showtimeval(DATE* time,char*name)
{
	 char str[20];
	 sprintf(str,"[%d:%d:%d]",(int)time->hour,(int)time->min,(int)time->sec);
	//SendString(str);
	LCDcls();
	LCDprintf(name);
	LCDprintf(str);
}
void trunpage()
{
	if(lvsecond==0)
	{
		if(getkey(0)==15)
		{
		//上翻页
			_page++;
			if (_page >= MAXPAGE) _page = 0;
		}
		if(getkey(0)==11)
		{
		//下翻页
			--_page;
			if (_page>MAXPAGE-1)	_page = MAXPAGE-1;
		}
	}
}
void uiupdater()
{
	char sendstr[30];
	trunpage();
	if (_page == 0)
	{ 
		LCDcls();
		LCDprintf("--wellcom-----use----WIMI-DEV-");	
	}
	else if (_page==1)
	{
		sprintf(sendstr,"a%d,b%d,c%d,d%d",(int)paralist[0],
			   (int)paralist[1],(int)paralist[2],(int)paralist[3]);
		//SendString(sendstr);
		LCDcls();
		LCDprintf(sendstr);	
	}
	else if (_page==2)
	{
		
		if(lvsecond==0) showtimeval(&currenttime,"-TIME-NOW-");
		setcurrenttime();
	}
	else if(_page == 3)
	{
		setclosetime(&opentime);
		if(lvsecond==0)	showtimeval(&opentime,"OPEN-TIME-");
		//if(timecmp(opentime,))	
	}
	else if(_page == 4)
	{
		setclosetime(&closetime);
		if(lvsecond==0)	showtimeval(&closetime,"-OFF-TIME-");
	}	
	getkey(1);
}
void cashcard(unsigned char *resdata)
{
	unsigned char index = 0; 
	unsigned char len = getuartbuflen();
	unsigned char idsta[10]; 
	unsigned char insertindex = 0;
	unsigned char selectindex = 0;
	char str[20]="cashcard"; 
	if(getreaded()) return;//没有数据更新
	LCDcls();
	for(index=0;index< len;index++)
	{	
		if(index>4&&index<len)
		{ 
			idsta[index-5] = *(resdata+index);	
		}
		setread(1);
		*(resdata+index) = 0;//清空数据
	}
	selectindex =  selectid(idsta);
	if(selectindex != UNKNOWERROR)
	{
		//查找到了
		number--;
		delectidbyindex(selectindex);
		sprintf(str,"NO.%d-OUT-;number is.%d.",(int)selectindex,(int)number);
	}
	else
	{
		//没有找到
		insertindex = insertid(idsta);
		if(insertindex == UNKNOWERROR) 
		{
			LCDprintf("--FULL--");
			LCDprintf("--callme--13077661594");
			return;
		} 
		number++;
		sprintf(str,"NO.%d-IN-;number is。%d。",(int)insertindex,(int)number);
	}
	LCDprintf(str);	
}
