#### 创建线程 

    pthread_create
    e.g. pthread_create(&thrd1, NULL, (void *)&thread_function, (void *) &some_argument);
    
线程创建函数包含四个变量，分别为： 
   
1. 一个线程变量名，被创建线程的标识 
2. 线程的属性指针，缺省为NULL即可 
3. 被创建线程的程序代码 
4. 程序代码的参数 
   

#### 结束线程

    pthread_exit(void *retval); // retval用于存放线程结束的退出状态

#### 线程等待 

    pthread_join(trd1,NULL);

代码中如果没有pthread_join主线程会很快结束从而使整个进程结束，从而使创建的线程没有机会开始执行就结束了。
加入pthread_join后，主线程会一直等待直到等待的线程结束自己才结束，使创建的线程有机会执行。

pthread_create调用成功以后，新线程和老线程谁先执行，谁后执行用户是不知道的,这一块取决与操作系统对线程的调度,
如果我们需要等待指定线程结束，需要使用pthread_join函数，这个函数实际上类似与多进程编程中的waitpid, 
举个例子，以下假设A线程调用pthread_join试图去操作B线程，该函数将A线程阻塞，直到B线程退出，当B线程退出以后，A线程会收集B线程的返回码


#### 线程让出CPU

    pthread_yield()

causes the calling thread to relinquish the CPU. The thread is moved to the end of the queue for its static priority and a new thread gets to run.

todo 线程里调用 printf进行打印,输出顺序并不一定等同于执行顺序


静态优先级：（定义在进程描述符中的:static_prio)

动态优先级:（定义在进程描述符中的:prio)

实时优先级:（定义在进程描述符中的:rt_priority)

 

 - 静态优先级：定义:他不随时间改变,内核不会主动修改它,只能通过系统调用nice去修改static_prio
 - 动态优先级：定义:调度程序通过或减少进程静态优先级来奖励IO消耗型进程或惩罚CPU消耗进程,调整后的优先级为动态优先级(prio)
 - 实时优先级：实时优先级只对实时进程有效

































