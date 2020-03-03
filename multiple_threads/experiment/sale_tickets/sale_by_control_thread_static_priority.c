//
// Created by guangsujiqiang on 2/28/20.
//

/*
    [guangsujiqiang@su-ct7 sale_tickets]$>gcc -o sale -lpthread sale_by_control_thread_static_priority.c && ./sale
    init tickets number：100000
    expect values is 91000 ,final surplus tickets number ： 98688
    [guangsujiqiang@su-ct7 sale_tickets]$>gcc -o sale -lpthread sale_by_control_thread_static_priority.c && ./sale
    init tickets number：100000
    expect values is 91000 ,final surplus tickets number ： 101000

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

void * back();
void * sell();

sem_t* Sem = NULL;
int ticketCount=100000;
const int cycle_sell = 10000;
const int cycle_back = 1000;

void * back()
{
    int temp;
    int i;
    for(i=0; i < cycle_back;i++)
    {
        int temp = ticketCount;
        temp = temp + 1;

        // 回写前强制 出让本线程的CPU使用权,主动触发线程切换 延长读写操作之间的时间间隔 放大回写覆盖的问题
        // tmp 覆写 售票后数据
        //  1000 覆盖 998 ，售票线程 从1000 卖了两张票,理论上应该剩余998张,但实际剩余1000
        pthread_yield();
        ticketCount = temp;

    }
}

void * sell()
{
    int temp;
    int i;
    for(i = 0; i < cycle_sell; i++)
    {
        int temp = ticketCount;
        temp = temp - 1;
        ticketCount = temp ;
    }

}

int main(int argc,char *argv[]){

    pthread_t p1,p2;
    int c_ret_1,c_ret_2;
    int tmp =  ticketCount;
    printf("init tickets number：%d \n",ticketCount);

    c_ret_1 = pthread_create(&p1,NULL,sell,"sell tickets");
    c_ret_2 = pthread_create(&p2,NULL,back,"back tickets");

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    printf("expect values is %d ,final surplus tickets number ： %d \n",tmp - cycle_sell + cycle_back,ticketCount);
    return 0;
}
