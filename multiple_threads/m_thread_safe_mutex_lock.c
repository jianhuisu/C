//
// Created by guangsujiqiang on 11/13/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * safe_print(void * pt);

int sharedi = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void m_thread_safe_lock(void){

    pthread_t trd1,trd2;

    int c_ret_1,c_ret_2;

    c_ret_1 = pthread_create(&trd1,NULL,(void *)&safe_print,"trd1");
    c_ret_2 = pthread_create(&trd2,NULL,(void *)&safe_print,"trd2");

    // todo ? 如果trd2 先于 trd1 结束怎么办？
    // 一般情况下，线程终止后，其终止状态一直保留到其它线程调用pthread_join获取它的状态为止。但是线程也可以被置为detach状态，这样的线程一旦终止就立刻回收它占用的所有资源，而不保留终止状态。不能对一个已经处于detach状态的线程调用pthread_join，这样的调用将返回EINVAL。对一个尚未detach的线程调用pthread_join或pthread_detach都可以把该线程置为detach状态，也就是说，不能对同一线程调用两次pthread_join，或者如果已经对一个线程调用了pthread_detach就不能再调用pthread_join了。
    pthread_join(trd1,NULL);
    pthread_join(trd2,NULL);

    printf("shared i value is %d \n",sharedi);
}

void * safe_print(void * pt){

    int i,tmp;

    for(i =0;i<10000;i++){

        // 对临界资源使用前 上锁


        if (pthread_mutex_lock(&mutex) != 0) {
                perror("pthread_mutex_lock");
                exit(EXIT_FAILURE);
        }

        tmp = sharedi;
        tmp++;
        sharedi = tmp;

        // 对临界资源使用结束 解锁
        if (pthread_mutex_unlock(&mutex) != 0) {
               perror("pthread_mutex_unlock");
               exit(EXIT_FAILURE);
        }
    }

}

