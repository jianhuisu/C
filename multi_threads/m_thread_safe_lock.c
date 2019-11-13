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

