
#include <stdio.h>
#include <pthread.h>

#define TRUE          0x01
#define FALSE         0x00
#define LST_POINTS_LEN    200

typedef int bool;
typedef struct __lstruan
{
	// value
	int len;
	int head;
	int tail;
	bool flag;
	pthread_mutex_t mutex_rw;

	int item[LST_POINTS_LEN];
	//mutex_t
	//struct mutex        io_mutex;
}lstruan;

int func01(int i,int j);



