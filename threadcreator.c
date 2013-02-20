#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_PATH "/proc/lfprng"

pthread_mutex_t mute;
pthread_cond_t cond;
long ret[10];

void *thread_test(void *pointer)
{
	char *buffer = (char *)malloc(32);
	return buffer;
}

main()
{
	pthread_t threads[10];
  	int i, index, in;
	char *threadresult;
	void *exitstatus;
	
	for(in = 0; in<10;in++)
	{
		for(i = 0; i<10; i++)
		{
			pthread_create(&threads[i], NULL, thread_test, NULL );
		}//end for loop
		
		for(index = 0; index<9;index++)
		{		
			pthread_join(threads[index], &exitstatus);		
			threadresult = (char *) exitstatus;
			free (exitstatus);
		}//end for loop
	}//end for loop
	pthread_exit(NULL);

}//end main function
