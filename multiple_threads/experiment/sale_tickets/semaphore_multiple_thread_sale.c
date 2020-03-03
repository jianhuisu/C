//
// Created by guangsujiqiang on 2/28/20.
// gcc semaphore_sale.c -o sale -lpthread
// right sample
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

void * back();
void * sell();

sem_t* sem_count_tickets = NULL;
int ticketCount=1000000;
const int cycle_sell = 100000;
const int cycle_back = 10000;

void * back()
{
    int temp;
    int i;
    for(i=0; i < cycle_back;i++)
    {
        sem_wait(sem_count_tickets); // wait
        int temp = ticketCount;
        temp = temp + 1;
        ticketCount = temp;
        sem_post(sem_count_tickets); // release
    }
}

void * sell()
{
    int temp;
    int i;
    for(i = 0; i < cycle_sell; i++)
    {
        sem_wait(sem_count_tickets); // wait
        int temp = ticketCount;
        temp = temp - 1;
        ticketCount = temp ;
        sem_post(sem_count_tickets); // release 信号量+1
    }

}

int main(int argc,char *argv[]){

    pthread_t p1,p2;
    int c_ret_1,c_ret_2;
    int tmp =  ticketCount;
    printf("init tickets number：%d \n",ticketCount);

    // ------------------------------
    sem_count_tickets = sem_open("sem", O_CREAT, 0666, 1);

    c_ret_1 = pthread_create(&p1,NULL,sell,"sell tickets");
    c_ret_2 = pthread_create(&p2,NULL,back,"back tickets");

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    sem_close(sem_count_tickets);
    sem_unlink("sem");
    // ------------------------------

    printf("expect values is %d ,final surplus tickets number ： %d \n",tmp - cycle_sell + cycle_back,ticketCount);
    return 0;
}
