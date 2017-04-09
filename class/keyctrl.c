#include"keyctrl.h"

 unsigned char getkeyval()
 {
 	unsigned char keyval = 0;
	unsigned char value = 0;
	value = K0;
	value<<=7;
	keyval|=value;
	value = 0;
	 
	value = K1;
	value<<=6;
	keyval |=value; 
	value = 0;

	value = K2;
	value<<=5;
	keyval |=value;
	value = 0;

	value = K3;
	value<<=4;
	keyval |=value;
	value = 0;

	value = K4;
	value<<=3;
	keyval |=value;
	value = 0;

	value = K5;
	value<<=2;
	keyval |=value;
	value = 0;

	value = K6;
	value<<=1;
	keyval |=value;
	value = 0;

	value = K7;
	value<<=0;
	keyval |=value; 
	value = 0;

   	return  keyval;
 }
char getkeypree()
{
	char keypree = -1;
	unsigned char cowval = 0;
	unsigned char rowval = 0;
	unsigned char cow = 0;//被按下的列
	unsigned char row = 0;//被按下的行
	unsigned char scanrule1[] =
	{0x70,0xb0,0xd0,0xe0};
	unsigned char scanrule2[] =
	{0x07,0x0b,0x0d,0x0e};

	K0=1;K1=1;K2=1;K3=1;
	K4=0;K5=0;K6=0;K7=0;
	//读取那一列被按下
	cowval = getkeyval();
	if (cowval == 0xf0) return -1;
   	K0=0;K1=0;K2=0;K3=0;
	K4=1;K5=1;K6=1;K7=1;
	//读取哪一行被按下
	rowval = getkeyval();
	if (rowval != 0x0f)
	{
		for(cow = 0;cow<4;cow++)
		{
		   if(cowval == scanrule1[cow])break;
		}
		for(row = 0;row<4;row++)
		{
			if(rowval == scanrule2[row])break;
		} 
		keypree = row * 4 + cow;
		return keypree;
	}  	
	return -1;
}