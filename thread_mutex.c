#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>


int counter = 0;
pthread_mutex_t lock; 

void *setCounter()
{
    puts("set counter ");
    for (;;)
    {
        if (counter == 0)
        {
            pthread_mutex_lock(&lock); 
            counter = 10;
            puts(" counter set 10 ");
            pthread_mutex_unlock(&lock); 
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
            pthread_mutex_lock(&lock); 
            for (;counter > 0; counter--)
            {
                printf(" Counter get %d \n", counter);
                sleep(1);
            }
            pthread_mutex_unlock(&lock); 
        }
    }
}
int main()
{
    pthread_t threadSet, threadGet;
    pthread_create(&threadSet, NULL, &setCounter, NULL);
    pthread_create(&threadGet, NULL, &getCounter, NULL); 
    pthread_join(threadGet, NULL);
    pthread_join(threadSet, NULL);
    return 0;
}