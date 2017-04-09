#ifndef __KEYCTRL_H_
#define __KEYCTRL_H_
#include"global.h"

	sbit K0 = P1^5;
	sbit K1 = P1^6;
	sbit K2 = P1^7;
	sbit K3 = P5^4;
	sbit K4 = P3^4;
	sbit K5 = P3^3;
	sbit K6 = P3^2;
	sbit K7 = P4^0;

extern 	unsigned char getkeyval();
extern char getkeypree();

#endif   