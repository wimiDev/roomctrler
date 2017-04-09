#include"ds1302.h"

void DS1302InputByte(unsigned char d) 	//实时时钟写入一字节(内部函数)
{ 
    unsigned char i;
    ACC = d;
    for(i=8; i>0; i--)
    {
        DS1302_IO = ACC0;           	//相当于汇编中的 RRC
        DS1302_CLK = 1;
        DS1302_CLK = 0;
        ACC = ACC >> 1; 
    } 
}

unsigned char DS1302OutputByte(void) 	//实时时钟读取一字节(内部函数)
{ 
    unsigned char i;
    for(i=8; i>0; i--)
    {
        ACC = ACC >>1;         			//相当于汇编中的 RRC 
        ACC7 = DS1302_IO;
        DS1302_CLK = 1;
        DS1302_CLK = 0;
    } 
    return(ACC); 
}

void Write1302(unsigned char ucAddr, unsigned char ucDa)	//ucAddr: DS1302地址, ucData: 要写的数据
{
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr);       	// 地址，命令 
    DS1302InputByte(ucDa);       	// 写1Byte数据
//    DS1302_CLK = 1;
    DS1302_RST = 0;
} 

unsigned char Read1302(unsigned char ucAddr)	//读取DS1302某地址的数据
{
    unsigned char ucData;
    DS1302_RST = 0;
    DS1302_CLK = 0;
    DS1302_RST = 1;
    DS1302InputByte(ucAddr|0x01);        // 地址，命令 
    ucData = DS1302OutputByte();         // 读1Byte数据
//    DS1302_CLK = 1;
    DS1302_RST = 0;
    return(ucData);
}

void DS1302_SetProtect(bit flag)        //是否写保护
{
	if(flag)
		Write1302(0x8E,0x10);
	else
		Write1302(0x8E,0x00);
}

void DS1302_SetTime(unsigned char Address, unsigned char Value)        // 设置时间函数
{
	DS1302_SetProtect(0);
	Write1302(Address, ((Value/10)<<4 | (Value%10))); 
}

void DS1302_GetTime(SYSTEMTIME *Time)
{
	unsigned char ReadValue;
	ReadValue = Read1302(DS1302_SECOND);
	Time->Second = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	//八进制转换成十进制
	ReadValue = Read1302(DS1302_MINUTE);
	Time->Minute = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_HOUR);
	Time->Hour = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_DAY);
	Time->Day = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	
	ReadValue = Read1302(DS1302_WEEK);
	Time->Week = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_MONTH);
	Time->Month = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);
	ReadValue = Read1302(DS1302_YEAR);
	Time->Year = ((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	
}

void DateToStr(SYSTEMTIME *Time)	 //
{
	Time->DateString[0] = Time->Year/10 ;	 //分离出个位和十位
	Time->DateString[1] = Time->Year%10 ;
	Time->DateString[2] = '-';
	Time->DateString[3] = Time->Month/10;
	Time->DateString[4] = Time->Month%10 ;
	Time->DateString[5] = '-';
	Time->DateString[6] = Time->Day/10 ;
	Time->DateString[7] = Time->Day%10 ;
	Time->DateString[8] = '\0';
}

void TimeToStr(SYSTEMTIME *Time)
{
	Time->TimeString[0] = Time->Hour/10 ;
	Time->TimeString[1] = Time->Hour%10 ;
	Time->TimeString[2] = ':';
	Time->TimeString[3] = Time->Minute/10 ;
	Time->TimeString[4] = Time->Minute%10 ;
	Time->TimeString[5] = ':';
	Time->TimeString[6] = Time->Second/10;
	Time->TimeString[7] = Time->Second%10 ;
	Time->DateString[8] = '\0';
}

void Initial_DS1302(void)
{
	unsigned char Second=Read1302(DS1302_SECOND);
	if(Second&0x80)		  
		DS1302_SetTime(DS1302_SECOND,0);
}
