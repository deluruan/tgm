#include <stdio.h>
#include <string.h>


#include "lstruan.h"

int func01(int i,int j)
{
	printf("func01\n");
	lstruan lst;
	memset(&lst,0x00,sizeof(lstruan));
	//lst.len=LST_POINTS_LEN;
	lst.flag=FALSE;
	pthread_mutex_init( &(lst.mutex_rw),NULL );
	return TRUE;
}

int push_point_to_list(int pt,lstruan lst)
{
	pthread_mutex_lock(&lst.mutex_rw);
	if((lst.flag==FALSE)||(lst.head!=lst.tail))
	{
		lst.flag=TRUE;  
		lst.item[lst.tail]=pt;
		lst.tail+=1;
		if(lst.tail==LST_POINTS_LEN) lst.tail=0;
	}
	pthread_mutex_unlock(&lst.mutex_rw);
	return TRUE;
}

int com_one_rece_slave(int* pt,lstruan lst)
{
	int blret=FALSE;
	pthread_mutex_lock(&lst.mutex_rw);
	if(lst.flag==TRUE)
	{
		*pt=lst.item[lst.head];
		lst.head+=1;
		if(lst.head==LST_POINTS_LEN)   lst.head=0;
		if(lst.head==lst.tail)  lst.flag=FALSE;
		blret=TRUE;
	}
	pthread_mutex_unlock(&lst.mutex_rw);
	return blret;
} 

