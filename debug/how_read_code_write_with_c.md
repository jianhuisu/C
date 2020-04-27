## 如何阅读C项目的源码

网上很少有教人如何阅读C源码的文章,而教人阅读的文章大多根据特定软件，直接上代码，少有涉及阅读方法

### 以php源码为例子

php源码是用C写的，各种宏,加上指针调用，复杂算法的封装，精心设计的层层套叠的结构体，复杂的编译流程,光代码就将近20M 望而生畏

	[sujianhui@nlp php-7.1.0]$ ls -l | grep ^d
	drwxrwxr-x.  2 sujianhui sujianhui     222 Dec  2  2016 build
	drwxr-xr-x.  3 sujianhui sujianhui     110 Apr 26 14:13 cmake-build-debug
	drwxrwxr-x. 75 sujianhui sujianhui    4096 Dec  2  2016 ext
	drwxrwxr-x.  2 sujianhui sujianhui       6 Apr 25 13:13 include
	drwxrwxr-x.  2 sujianhui sujianhui       6 Apr 25 13:13 libs
	drwxrwxr-x.  4 sujianhui sujianhui    4096 Apr 26 14:43 main
	drwxrwxr-x.  2 sujianhui sujianhui      59 Apr 26 14:15 modules
	drwxrwxr-x.  2 sujianhui sujianhui      42 Dec  2  2016 netware
	drwxrwxr-x.  3 sujianhui sujianhui     115 Apr 25 13:14 pear
	drwxrwxr-x. 10 sujianhui sujianhui     118 Dec  2  2016 sapi
	drwxrwxr-x.  4 sujianhui sujianhui     137 Apr 26 14:43 scripts
	drwxrwxr-x. 10 sujianhui sujianhui     142 Dec  2  2016 tests
	drwxrwxr-x.  3 sujianhui sujianhui      35 Dec  2  2016 travis
	drwxrwxr-x.  4 sujianhui sujianhui    4096 Apr 25 13:16 TSRM
	drwxrwxr-x.  3 sujianhui sujianhui    4096 Dec  2  2016 win32
	drwxrwxr-x.  5 sujianhui sujianhui   12288 Apr 25 13:16 Zend

这么一堆代码编译下来，会生成好几个可执行文件，也就是说源码中 main 入口不止一处，如何在这一团乱麻中找到一个切入点呢


### 借助工具

	借助IDE，gdb来简化源码，快速的跳跃到我们感兴趣的地方
	

### 选取切入点，有舍才有得

一般人很难啃透php的源码，我们应该选取我们疑惑的地方/源码的闪光点 进行定点学习，通篇学习对于普通人来说
不论是时间，还是技术积累都有很高的门槛。

