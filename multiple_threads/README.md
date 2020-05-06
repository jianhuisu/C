#### 创建线程 

    pthread_create
    e.g. pthread_create(&thrd1, NULL, (void *)&thread_function, (void *) &some_argument);
    
线程创建函数包含四个变量，分别为： 
   
1. 一个线程变量名，被创建线程的标识 
2. 线程的属性指针，缺省为NULL即可 
3. 被创建线程的程序代码 
4. 程序代码的参数 

`pthread_create`调用成功以后，众多子线程谁先执行,谁后执行是不确定的,这取决与操作系统对线程的调度算法与实际情况
如果我们需要等待指定线程结束，需要使用`pthread_join`函数，这个函数实际上类似与多进程编程中的`waitpid()`.   

#### 结束线程

如果需要只终止某个线程而不终止整个进程，可以有三种方法：

 - 从线程函数return。这种方法对主线程不适用，从main函数return相当于调用exit。
 - 一个线程可以调用`pthread_cancel`终止同一进程中的另一个线程。
 - 线程可以调用pthread_exit终止自己。  pthread_exit(void *retval); // retval用于存放线程结束的退出状态
   
#### 线程等待 

    pthread_join(trd1,NULL);

代码中如果没有`pthread_join`主线程会很快结束从而使整个进程结束，从而使创建的子线程没有机会开始执行就结束了。
加入`pthread_join`后，主线程会一直等待直到等待的线程结束自己才结束，使创建的线程有机会执行。

调用该函数的线程将挂起等待，直到id为thread的线程终止。thread线程以不同的方法终止，通过pthread_join得到的终止状态是不同的，总结如下：

 - 如果thread线程通过return返回，value_ptr所指向的单元里存放的是thread线程函数的返回值。
 - 如果thread线程被别的线程调用pthread_cancel异常终止掉，value_ptr所指向的单元里存放的是常数PTHREAD_CANCELED。
 - 如果thread线程是自己调用pthread_exit终止的，value_ptr所指向的单元存放的是传给pthread_exit的参数。
 
现在有一个问题
    
    int main(void)
    ...
    pthread_t trd1,trd2;
    int c_ret_1,c_ret_2;

    c_ret_1 = pthread_create(&trd1,NULL,(void *)&safe_print,"trd1");
    c_ret_2 = pthread_create(&trd2,NULL,(void *)&safe_print,"trd2");

    pthread_join(trd1,NULL);
    pthread_join(trd2,NULL);

    printf("shared i value is %d \n",sharedi);
    
    ...
    
 如果`trd2`先于`trd1`结束怎么办？如果线程`trd1`一直不结束,`trd2`就一直不能回收吗?
 
    #include <stdio.h>
    #include <unistd.h>
    #include <pthread.h>
    
    void * thd1(void)
    {
        pthread_t cur_thd = pthread_self();
        printf("cur pthread id is %d 0x%x \n",cur_thd,cur_thd);
        sleep(10);
        return NULL;
    }
    
    void * thd2(void)
    {
        pthread_t cur_thd = pthread_self();
        printf("cur pthread id is %d 0x%x \n",cur_thd,cur_thd);
        sleep(3);
        return NULL;
    }
    
    int main(void)
    {
        pthread_t th_id1,th_id2;
        int err1,err2;
    
        err1 = pthread_create(&th_id1,NULL,(void *)&thd1,"new thread");
        err2 = pthread_create(&th_id2,NULL,(void *)&thd2,"new thread");
    
        if(pthread_join(th_id1,NULL) == 0){
            printf("pthread 1 success exit \n ");
        }
    
        if(pthread_join(th_id2,NULL) == 0){
            printf("pthread 2 success exit \n ");
        }
        
        // this is main pthread
        printf("this is main pthread \n");
        return 0;
    }
    
输出结果为:
    
    [sujianhui@dev529 a_test]$>gcc test.c -lpthread && ./a.out
    cur pthread id is -2142578944 0x804ad700 
    cur pthread id is 2143995648 0x7fcac700 
    pthread 1 success exit 
    pthread 2 success exit 
    this is main pthread 

结果分析,主线程会阻塞等待线程1执行结束,10秒后,线程1执行结束,进程被唤醒回收线程1的技术状态.
然后代码继续执行,此时`pthread_join(th_id2,NULL)`不会阻塞了,因为`th_id2`早以执行完成,等待主线程进行回收.        
  
小结: 一般情况下，线程终止后，其终止状态一直保留到其它线程调用`pthread_join`获取它的状态为止。
但是线程也可以被置为`detach`状态，这样的线程一旦终止就立刻回收它占用的所有资源，而不保留终止状态。
不能对一个已经处于`detach`状态的线程调用`pthread_join`，这样的调用将返回EINVAL。
对一个尚未`detach`的线程调用`pthread_join`或`pthread_detach`都可以把该线程置为`detach`状态，
也就是说，**不能对同一线程调用两次`pthread_join`，或者如果已经对一个线程调用了`pthread_detach`就不能再调用`pthread_join`了。**


### 参考资料

https://docs.huihoo.com/c/linux-c-programming/ch35s02.html  

  






















