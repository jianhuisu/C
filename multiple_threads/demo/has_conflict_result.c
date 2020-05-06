//
// 累加结果小于期望结果 未进行线程间同步
//
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_LOOP 100000
int counter = 0;

void * thd(void)
{
    int i;
    int tmp;
    for(i=0;i<MAX_LOOP;i++){
        tmp = counter;
        printf("call one system call %d %d \n",(int)pthread_self(),counter);
        counter = tmp + 1;
    }

    return NULL;
}

int main(void)
{
    pthread_t th_id1,th_id2;
    int err1,err2;

    err1 = pthread_create(&th_id1,NULL,(void *)&thd,"new thread");
    err2 = pthread_create(&th_id2,NULL,(void *)&thd,"new thread");

    if(pthread_join(th_id1,NULL) == 0){
        printf("pthread 1 success exit \n ");
    }

    if(pthread_join(th_id2,NULL) == 0){
        printf("pthread 2 success exit \n ");
    }

    // this is main pthread
    printf("this is main pthread %d \n",counter);
    return 0;
}