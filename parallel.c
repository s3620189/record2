#include "main.h"
#include "parallel.h"

#include <stdlib.h>


static void* thread_routine(void* rank){
    long my_rank = (long)rank;
    long start_x;
    long stop_x;
    start_x=(matrix_size/num_threads)*my_rank;
    stop_x=start_x+matrix_size/num_threads;
    if(my_rank==num_threads-1)
    {
        stop_x=matrix_size;
    }
    int my_x;
    int y;
    long local_sum=0;
    //printf("start_x = %ld,  I am Thread %ld\n", start_x,my_rank);
    for (my_x=start_x; my_x<stop_x; my_x++)
    {
        for (y=0; y<matrix_size; y++)
        {
        	
            local_sum += matrix_x[my_x][y] * matrix_y[y][my_x];
            
            
        }
    }
    pthread_mutex_lock(&mutex);
    sum+=local_sum; 
    pthread_mutex_unlock(&mutex);       
    //printf("sum = %ld,  I am Thread %ld\n", sum,my_rank);



    // *** YOUR CODE FOR THE THREAD ROUTINE GOES HERE ***

    return NULL;
}

void parallel()
{
	pthread_t* thread_handles; 
    pthread_mutex_init(&mutex, 0);
	thread_handles = malloc (num_threads*sizeof(pthread_t));
	for(thread=0;thread<num_threads;thread++)
	{
		pthread_create(&thread_handles[thread],NULL,thread_routine,(void*) thread);
	}

    for (thread = 0; thread < num_threads; thread++)
        pthread_join(thread_handles[thread], NULL);

    free(thread_handles);
    pthread_mutex_destroy(&mutex);
    // *** YOUR CODE FOR THE THREAD GENERATION GOES HERE ***
    
}
