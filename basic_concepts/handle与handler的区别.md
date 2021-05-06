# handle 与 handler的区别

### 什么是handle

"勺子把儿"说的就是handle。而将handle译成"句柄"绝对是一个相当文雅相当阳春白雪的翻译，多文化底蕴不够的码农就看不大懂了或者望而生畏。
例如： 在Unix/Linux系统中

 - 进程号pid就是一个handle,
 - 文件描述符(fd)也是一个handle,  
 - 系统调用号(syscall num)仍然是一个handle

>一个unsigned int占4个字节，可以表征的通信密码总数为2^32(=4G, 约40亿)

### 什么是handler

hanlder就是一个回调函数(callback)。当某个事件到达时，事先注册的handler会被接收到事件的主体所调用。

	static void foo_handler(int signum)

### 巨人肩膀

https://www.cnblogs.com/idorax/p/6414007.html