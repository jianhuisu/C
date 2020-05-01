#### 创建线程 

    pthread_create
    e.g. pthread_create(&thrd1, NULL, (void *)&thread_function, (void *) &some_argument);
    
线程创建函数包含四个变量，分别为： 
   
1. 一个线程变量名，被创建线程的标识 
2. 线程的属性指针，缺省为NULL即可 
3. 被创建线程的程序代码 
4. 程序代码的参数 

pthread_create调用成功以后，众多子线程谁先执行,谁后执行是不确定的,这取决与操作系统对线程的调度算法与实际情况
如果我们需要等待指定线程结束，需要使用pthread_join函数，这个函数实际上类似与多进程编程中的waitpid().   

#### 结束线程

    pthread_exit(void *retval); // retval用于存放线程结束的退出状态

#### 线程等待 

    pthread_join(trd1,NULL);

代码中如果没有pthread_join主线程会很快结束从而使整个进程结束，从而使创建的子线程没有机会开始执行就结束了。
加入pthread_join后，主线程会一直等待直到等待的线程结束自己才结束，使创建的线程有机会执行。

#### 线程让出CPU

    pthread_yield()
    
causes the calling thread to relinquish the CPU. The thread is moved to the end of the queue for its static priority and a new thread gets to run.
主动让出CPU从而让另外一个线程运行,函数可以使用另一个级别等于或高于当前线程的线程先运行。如果没有符合条件的线程，那么这个函数将会立刻返回然后继续执行当前线程的程序。

#### prio

 - 静态优先级 static_prio：不随时间改变,内核不会主动修改它,只能通过系统调用nice去修改
 - 动态优先级 prio： 调度程序通过或减少进程静态优先级来奖励IO消耗型进程或惩罚CPU消耗进程,调整后的优先级为动态优先级
 - 实时优先级 rt_priority：实时优先级只对实时进程有效

### 互斥量和信号量的区别 

 - 1. 互斥量用于线程的互斥，信号量用于线程的同步。这是互斥量和信号量的根本区别，也就是互斥和同步之间的区别。
 - 2. 互斥量值只能为0/1，信号量值可以为非负整数。
 - 3. 互斥量的加锁和解锁必须由同一线程分别对应使用，信号量可以由一个线程释放，另一个线程得到。

## 事件驱动


## 线程同步

 - 互斥量
 - 信号量
 - 临界区
 - 事件驱动

###  

  






















