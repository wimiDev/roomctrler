#ifndef __KEYHANDLER_H_
#define __KEYHANDLER_H_

#include"global.h"
extern char _keyval;

extern char _keyvalbuf;//可读取的按键值

extern void keyhandler();
extern void keynumberhandler();
extern char getkey(bit _swallow);
extern char getnumber(char _code);

#endif