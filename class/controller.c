#include"controller.h"
unsigned char paralist[4];
unsigned char _page = 0;
unsigned char lvsecond = 0;
unsigned char number = 0;
char trybee = 0;
bit enablebee = 1;
DATE currenttime;
DATE closetime;//关灯时间
DATE opentime;//开灯时间

void controllerinit()
{	 
	_BEEBEE = 0;
	Initial_DS1302();
	DS1302_SetTime(DS1302_HOUR,10);	//??????????10??54??30
	DS1302_SetTime(DS1302_MINUTE,54);
	DS1302_SetTime(DS1302_SECOND,30); 
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
void showtimeval(DATE* time,char*name)
{
	 char str[20];
	 sprintf(str,"[%d:%d:%d]",(int)time->hour,(int)time->min,(int)time->sec);
	 //LCDcls();
	 LCDprintf(name,0);
	 LCDprintf(str,-1);
}
void trunpage()
{
	if(lvsecond == 0)
	{
		if(getkey(0)==15)
		{
		//上翻页
			_page++;
			if (_page >= MAXPAGE) _page = 0;
			beebee(1);
			LCDcls();
		}
		if(getkey(0)==11)
		{
		//下翻页
			--_page;
			if (_page>MAXPAGE-1)	_page = MAXPAGE-1;
			beebee(1);
			LCDcls();
		}
	}
}
void uiupdater()
{
	char sendstr[30];
	trunpage();
	if (_page == 0)
	{ 
		//LCDcls();
		LCDprintf("--wellcom-----use----WIMI-DEV-",0);	
	}
	else if (_page==1)
	{
		sprintf(sendstr,"a%d,b%d,c%d,d%d",(int)paralist[0],
			   (int)paralist[1],(int)paralist[2],(int)paralist[3]);
		//LCDcls();
		LCDprintf(sendstr,0);	
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
	else if(_page == 5)
	{
		if(lvsecond==0)showbeeable();
		setbeeanle();
	}
	else if(_page == 6)
	{
		showlightsta();
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
	char str[20] = "cashcard"; 
	if(getreaded()== 1 ) return;//没有数据更新
	LCDcls();
	if(getreaded() == -1)
	{
		beebee(5);
		sprintf(str,"SUPPORT-ID-CARD-ONLY!");
		LCDprintf(str,0);
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
		sprintf(str,"NO.%d-OUT-;number is.%d.",(int)selectindex,(int)number);
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
		sprintf(str,"NO.%d-IN-;number is。%d。",(int)insertindex,(int)number);
	}
	LCDprintf(str,0);
	setread(1);
}
void beebee(char inval)
{
	trybee = inval;
	beehandler();
}
void beehandler()
{
		if(trybee > 0)
		{
			if(enablebee && trybee%2) _BEEBEE = 1;
			else _BEEBEE = 0;	
			trybee --;
		}
		else
		{
			_BEEBEE = 0;	
		}
}
void showbeeable()
{
		char str[30];
		if(enablebee)
		{
			sprintf(str,"BEE-ENABLE----ON----");
		}
		else
		{
			sprintf(str,"BEE-ENABLE----OFF---");
		}
		LCDprintf(str,0);
}
void showlightsta()
{
		char str[30];
		char index=0;
		sprintf(str,"---LIGHT--");
		LCDprintf(str,0);
		for(index=0;index<3;index++)
		{
			if(lightstate[index])
			{
				sprintf(str,"%d:%c--",(int)index+1,'O');
				LCDprintf(str,-1);
			}
			else
			{
				sprintf(str,"%d:%c--",(int)index+1,'X');
				LCDprintf(str,-1);
			}
		}
}
