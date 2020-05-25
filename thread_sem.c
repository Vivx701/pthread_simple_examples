#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int counter = 0;
sem_t sem_count; 

void *setCounter()
{
    puts("set counter ");
    for (;;)
    {
        if (counter == 0)
        {
            sem_wait(&sem_count); 
            counter = 10;
            puts(" counter set 10 ");
            sem_post(&sem_count); 
        }
    }
}

void *getCounter()
{
    puts("Get counter ");
    while (1)
    {
        if (counter == 10)
        {
            sem_wait(&sem_count); 
            for (;counter > 0; counter--)
            {
                printf(" Counter get %d \n", counter);
                sleep(1);
            }
            sem_post(&sem_count); 
        }
    }
}
int main()
{
    pthread_t threadSet, threadGet;
    sem_init(&sem_count, 0, 1);
    pthread_create(&threadSet, NULL, &setCounter, NULL);
    pthread_create(&threadGet, NULL, &getCounter, NULL); 
    pthread_join(threadGet, NULL);
    pthread_join(threadSet, NULL);
    return 0;
}