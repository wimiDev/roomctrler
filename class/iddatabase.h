#ifndef __IDDATABASE_H_
#define __IDDATABASE_H_
#include"global.h"

#define MAXIDSESION 100
#define MAXATTRIBUTE 10
#define UNKNOWERROR 255

extern unsigned char iddb[MAXIDSESION][MAXATTRIBUTE];
//记录是否有效，0 无效，1 有效 
//最大254条记录，255为查找失败标志 
extern char  dbindex[MAXIDSESION];

//向库中插入一个id,不判断是否有相同的id
//返回0成功，返回-1失败
extern unsigned char insertid(char* id);
//从库中查找一个元素
//成功0，失败-1
extern unsigned char selectid(char* id);
extern void dbinit();
extern unsigned char getfreeindex();
extern void setfreeindex(unsigned char index);
extern void setbusyindex(unsigned char index);
extern unsigned char delectid(unsigned char* id);
extern unsigned char delectidbyindex(unsigned char index);
#endif