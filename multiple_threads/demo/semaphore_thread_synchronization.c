// 注意：下面的信号量用法 只能限制 生产者生产一个资源 ，消费者消费一个资源 ，但是并不能保证 最终的输出 stack 为 0 ,因为临界资源 stack 的操作并没有加锁
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define MAX_PRODUCE_NUM 10000

sem_t sem;

int stack = 0;

void produce(void);
void consume(void);

int main(void)
{
    sem_init(&sem, 0, 0);
    pthread_t tid_1,tid_2;

    int err_1,err_2;
    err_1 = pthread_create(&tid_1,NULL,(void *)&produce,NULL);
    err_2 = pthread_create(&tid_2,NULL,(void *)&consume,NULL);

    pthread_join(tid_1,NULL);
    pthread_join(tid_2,NULL);

    sem_destroy(&sem);
    printf("最终库存为 %d , 期望库存为 0 \n",stack);
    printf("finished \n");
    return 0;
}

void produce(void)
{
    int i;
    for(i=0;i < MAX_PRODUCE_NUM;i++){
        stack++;
        //sleep(1);
        sem_post(&sem);
    }

    pthread_exit(NULL);
}

void consume(void)
{
    int i = 0;  // 消耗指定数量资源后 就结束消费线程
    while(i < MAX_PRODUCE_NUM){
        sem_wait(&sem);
        printf("get one value %d\n ",i);
        i++; // i++ 不是原子性操作
        stack--;
    }

    pthread_exit(NULL);
}