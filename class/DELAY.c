#include"delay.h"
//#include"reg52.h"
//#include"global.h"
/***************************延时函数*********************/
//void LCDDelay(unchar t)
//{
//  unchar x,y;
//  for(x=t;x>0;x--)
//    for(y=110;y>0;y--);
//}
/**********************延时函数**************************/
void NRFDelay(unsigned int t)
{
   unsigned int x,y;
   for(x=t;x>0;x--)
    for(y=110;y>0;y--);
}