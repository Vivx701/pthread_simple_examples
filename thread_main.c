#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void *print_string()
{
    char str[10];
    time_t t;
    srand((unsigned) time(&t));
    for (;;)
    {
        for (int i=0; i<10; i++)
        {
            char ch = 65+rand()%24;
            str[i] = ch;
        }
        printf("Random String: %s", str);
        sleep(1);
    }
}

void sighandler(int signum) {
   printf("Caught signal %d\n", signum);
   exit(1);
}
int main()
{
    signal(SIGINT, sighandler);
    pthread_t thread;
    pthread_create(&thread, NULL, &print_string, NULL);
    for(;;)
    {
        printf("Random Number:  %d\n ", rand());
        sleep(1);
    }
    pthread_join(thread, NULL);                                                                                                                        
    return 0;
}