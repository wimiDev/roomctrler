#include"keyhandler.h"
 char _keyval = -1;
 char _keyvalbuf = -1;
void keyhandler()
{
	char keyval = 0 ;
	keyval = getkeypree();
	if((keyval !=-1) &&(keyval != _keyval))
	{
		beebee(2);
	}
	if(keyval != -1) 
	{
		_keyval = keyval;
		return;
	}	
	if(_keyval!=-1)	
	{
		//按键弹起
		_keyvalbuf = _keyval;
	}
	_keyval=-1;
}
char getkey(bit _swallow)
{
	char keyval = _keyvalbuf;
	//吞噬按键值，后续的将获取不到按键值
	if(_swallow) _keyvalbuf = -1;
	return keyval;
}
char getnumber(char _code)
{
	char code keycode[] = {0,1,2,-1,3,4,5,-1,6,7,8,-1,9,-1,-1,-1,-1};
	return keycode[_code];
}
void keynumberhandler()
{
	
}