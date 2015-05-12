#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


void call_cstatic1()
{
	int i;

	puts("call_cstatic1");
	for(i=0;i<10;i++)
	{
		printf("i=%d\n",i);
	}


}

#ifdef __cplusplus
}
#endif

