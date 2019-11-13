//
// Created by guangsujiqiang on 11/13/19.
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAXSIZE 10

void m_thread_safe_semaphore(void);
void data_produce();
void data_consume();

int stack[MAXSIZE];
sem_t sem;

void m_thread_safe_semaphore(void){

    pthread_t trd1,trd2;
    int c_ret_1,c_ret_2;

    c_ret_1 = pthread_create(&trd1,NULL,(void *)&data_produce,"trd1");
    c_ret_2 = pthread_create(&trd2,NULL,(void *)&data_consume,"trd2");

    pthread_join(trd1,NULL);
    pthread_join(trd2,NULL);

    sem_destroy(&sem); //销毁信号量
    printf("finish success \n");

}

void data_produce(){
    // 产生一个资源 则 信号量+1
    int i;
    for(i = 0;i<MAXSIZE;i++){
        sleep(1);
        stack[i] = i;
        sem_post(&sem); // 信号量+1
    }
}

void data_consume(){

    // 消费一个资源 则信号量-1  当信号量为0时  阻塞线程执行
    int i=0;
    while(i < MAXSIZE){
        sem_wait(&sem);
        printf("value is %d \n",stack[i]);
        i++;
    }

}