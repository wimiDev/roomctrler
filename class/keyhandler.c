#include"keyhandler.h"
 char _keyval = -1;
 char _keyvalbuf = -1;
void keyhandler()
{
	char keyval = 0 ;
	//char str[11];
	keyval = getkeypree();
	if(keyval != -1) 
	{
		_keyval = keyval;
		return;
	}	
	if(_keyval!=-1)	_keyvalbuf = _keyval;
//	switch(_keyval)
//	{
//		case 15:
//		{
//			//�Ϸ�ҳ
//			_page++;
//			if (_page > MAXPAGE) _page = 0;
//		}break;
//		case 11:
//		{
//			//�·�ҳ
//			--_page;
//			if (_page>MAXPAGE-1)	_page = MAXPAGE-1;
//		}break;
//		case 7:
//		{
//			//ȡ��
//		}break;
//		case 3:
//		{
//		  //ȷ��
//		}break;
//		default:{
//		   _page = _keyval >= 0?_keyval:_page;
//
//		}break;
//	}
	_keyval=-1;
}
char getkey(bit _swallow)
{
	char keyval = _keyvalbuf;
	//���ɰ���ֵ�������Ľ���ȡ��������ֵ
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