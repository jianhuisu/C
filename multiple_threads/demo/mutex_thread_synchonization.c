//
// 使用Mutex实现线程间同步
//
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_LOOP 100000
int counter = 0;
pthread_mutex_t t_mutex = PTHREAD_MUTEX_INITIALIZER;

void * thd(void)
{
    int i;
    int tmp;
    for(i=0;i<MAX_LOOP;i++){

        // 一个线程可以调用pthread_mutex_lock获得Mutex，
        // 如果这时另一个线程已经调用pthread_mutex_lock获得了该Mutex，
        // 则当前线程需要挂起等待，直到另一个线程调用pthread_mutex_unlock释放Mutex，
        // 当前线程被唤醒，才能获得该Mutex并继续执行。
        //
        //如果一个线程既想获得锁，又不想挂起等待，可以调用pthread_mutex_trylock，
        // 如果Mutex已经被另一个线程获得，这个函数会失败返回EBUSY，而不会使线程挂起等待。
        pthread_mutex_lock(&t_mutex);
        tmp = counter;
        printf("call one system call %d %d \n",(int)pthread_self(),counter);
        counter = tmp + 1;
        pthread_mutex_unlock(&t_mutex);
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