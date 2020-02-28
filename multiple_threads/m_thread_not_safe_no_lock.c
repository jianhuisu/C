//
// Created by guangsujiqiang on 11/13/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * no_lock_increse(void * pt);
int sharedi = 0;

void m_thread_not_safe_no_lock(void){

    pthread_t trd1,trd2;

    int c_ret_1,c_ret_2;

    c_ret_1 = pthread_create(&trd1,NULL,(void *)&no_lock_increse,"trd1");
    c_ret_2 = pthread_create(&trd2,NULL,(void *)&no_lock_increse,"trd2");

    pthread_join(trd1,NULL);
    pthread_join(trd2,NULL);

    printf("shared i value is %d \n",sharedi);
}

void * no_lock_increse(void * pt){

    int i,tmp;
    // 2个线程竞争访问全局变量sharedi，并且都没有进行相应的同步  两个线程在更新 sharedi值时  for 都执行了 10000 次
    // 但是有时候两者的 累加操作会重合(幻读)  所以 两个线程最终执行完成时 sharedi 的值会 < 19999
    for(i =0;i<10000;i++){
        tmp = sharedi;
        tmp++;
        sharedi = tmp;
    }

}

