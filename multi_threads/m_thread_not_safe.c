//
// Created by guangsujiqiang on 11/13/19.
//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int increment();

void m_thread_not_safe(void){

    int shareI = 0;
    int * p = &shareI;

    // thread identify
    pthread_t thread1,thread2,thread3;

    // thread create return
    int thread_ret1,thread_ret2,thread_ret3;
    char message1[] = "thread1";
    char message2[] = "thread2";
    char message3[] = "thread3";

    thread_ret1 = pthread_create(&thread1,NULL,(void *)&increment,message1);
    thread_ret2 = pthread_create(&thread2,NULL,(void *)&increment,message2);
    thread_ret3 = pthread_create(&thread3,NULL,(void *)&increment,message3);

    if(thread_ret1 != 0){
        printf("create 1 fail");
        exit(1);
    }

    if(thread_ret2 != 0){
        printf("create 2 fail");
        exit(1);
    }

    if(thread_ret3 != 0){
        printf("create 3 fail");
        exit(1);
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("finished \n");

}

int increment(char * ptr){

    int t;
    for(t = 0;t<100000;t++){
        printf("thread prefix is %s --- %d \n", ptr,t);
    }

}