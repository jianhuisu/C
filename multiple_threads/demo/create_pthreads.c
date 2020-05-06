#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t ntd_id;

void * thd(void)
{
    pthread_t cur_thd = pthread_self();
    printf("cur pthread id is %d 0x%x \n",cur_thd,cur_thd);
    return NULL;
}

int main(void)
{
    char *argv;
    int err;
    err = pthread_create(&ntd_id,NULL,(void *)&thd,"new thread");

    pthread_join(ntd_id,NULL);

    // this is main pthread
    printf("this is main pthread \n");
    return 0;
}