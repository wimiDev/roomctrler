#include"iddatabase.h"

unsigned char iddb[MAXIDSESION][MAXATTRIBUTE];
//记录是否有效，0 无效，1 有效 
//最大254条记录，255为查找失败标志 
char  dbindex[MAXIDSESION];
void dbinit()
{
	unsigned char i;
	for(i=0;i<MAXIDSESION;i++)
	{
		dbindex[i] = 0;//初始化为无效 
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
		//查找成功
		if(su == 0) return idindex;	
	}
	//查找失败	
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