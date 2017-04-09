#ifndef __IDDATABASE_H_
#define __IDDATABASE_H_
#include"global.h"

#define MAXIDSESION 100
#define MAXATTRIBUTE 10
#define UNKNOWERROR 255

extern unsigned char iddb[MAXIDSESION][MAXATTRIBUTE];
//��¼�Ƿ���Ч��0 ��Ч��1 ��Ч 
//���254����¼��255Ϊ����ʧ�ܱ�־ 
extern char  dbindex[MAXIDSESION];

//����в���һ��id,���ж��Ƿ�����ͬ��id
//����0�ɹ�������-1ʧ��
extern unsigned char insertid(char* id);
//�ӿ��в���һ��Ԫ��
//�ɹ�0��ʧ��-1
extern unsigned char selectid(char* id);
extern void dbinit();
extern unsigned char getfreeindex();
extern void setfreeindex(unsigned char index);
extern void setbusyindex(unsigned char index);
extern unsigned char delectid(unsigned char* id);
extern unsigned char delectidbyindex(unsigned char index);
#endif