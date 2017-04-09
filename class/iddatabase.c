#include"iddatabase.h"

unsigned char iddb[MAXIDSESION][MAXATTRIBUTE];
//��¼�Ƿ���Ч��0 ��Ч��1 ��Ч 
//���254����¼��255Ϊ����ʧ�ܱ�־ 
char  dbindex[MAXIDSESION];
void dbinit()
{
	unsigned char i;
	for(i=0;i<MAXIDSESION;i++)
	{
		dbindex[i] = 0;//��ʼ��Ϊ��Ч 
	}
}
unsigned char getfreeindex()
{
	unsigned char i;
	for(i=0;i<MAXIDSESION;i++)
	{
		if(dbindex[i] == 0) return i;
	}
	return UNKNOWERROR;
} 
void setfreeindex(unsigned char index)
{
	dbindex[index] = 0;	
} 
void setbusyindex(unsigned char index)
{
	dbindex[index] = 1;	
} 
unsigned char insertid(unsigned char* id)
{
	unsigned char index=0;
	unsigned char freedindex = getfreeindex();
	
	if(freedindex == UNKNOWERROR) return UNKNOWERROR;
	 for(index=0;index<MAXATTRIBUTE;index++)
	 {
	 	 iddb[freedindex][index] = id[index];
	 }
	 setbusyindex(freedindex);
	 return freedindex;
}

unsigned char selectid(unsigned char* id)
{
	char su = 0;
	unsigned char idindex=0;
	unsigned char valindex=0;
	for(idindex=0;idindex<MAXIDSESION;idindex++)
	{	
		if(dbindex[idindex]==0) continue;
		su = 0;
		for(valindex=0;valindex<MAXATTRIBUTE;valindex++)
		{
			if (id[valindex] != iddb[idindex][valindex])
			{
				su = UNKNOWERROR;
				break;
			}
		}  
		//���ҳɹ�
		if(su == 0) return idindex;	
	}
	//����ʧ��	
	return UNKNOWERROR;
}
unsigned char delectid(unsigned char* id)
{
	 unsigned char index = selectid(id);
	 if(index == UNKNOWERROR) return UNKNOWERROR;
	 setfreeindex(index);
	 return 0;
}
unsigned char delectidbyindex(unsigned char index)
{
	setfreeindex(index);
	return 0;	
}