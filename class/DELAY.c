#include"delay.h"
//#include"reg52.h"
//#include"global.h"
/***************************��ʱ����*********************/
//void LCDDelay(unchar t)
//{
//  unchar x,y;
//  for(x=t;x>0;x--)
//    for(y=110;y>0;y--);
//}
/**********************��ʱ����**************************/
void NRFDelay(unsigned int t)
{
   unsigned int x,y;
   for(x=t;x>0;x--)
    for(y=110;y>0;y--);
}