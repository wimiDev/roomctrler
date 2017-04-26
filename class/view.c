#include "view.h"

unsigned char _page = 0;
unsigned char lvsecond = 0;
char trybee = 0;
bit enablebee = 1;
char msginval = 0;

void showtimeval(DATE* time,char*name)
{
	 char str[20];
	 sprintf(str,"[%d:%d:%d]",(int)time->hour,(int)time->min,(int)time->sec);
	 LCDprintf(name,0);
	 LCDprintf(str,-1);
}
void trunpage()
{
	if(lvsecond == 0)
	{
		if(getkey(0)==15)
		{
		//ÉÏ·­Ò³
			_page++;
			if (_page >= MAXPAGE) _page = 0;
			beebee(1);
			LCDcls();
		}
		if(getkey(0)==11)
		{
		//ÏÂ·­Ò³
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
	if(msgviewhandler()) return;
	trunpage();
	if (_page == 0)
	{ 
		LCDprintf("--wellcom-----use----WIMI-DEV-",0);	
	}
	else if (_page==1)
	{
		sprintf(sendstr,"a%d,b%d,c%d,d%d",(int)paralist[0],
			   (int)paralist[1],(int)paralist[2],(int)paralist[3]);
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
void showmsg(char str[],char inval)
{
	char msg[30];
	msginval = inval;
	sprintf(msg,"%s------%d",str,(int)msginval);
	LCDprintf(msg,0);
}
char msgviewhandler()
{
	if(msginval > 0)
	{
		msginval--;
		//showmsg("",0);
		return 1;
	}
	if(msginval==0)
		{ 
			LCDcls();
			msginval = -1;
		}
		return 0;
}
