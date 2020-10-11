## 如何使用Clion调试使用make工具构建的项目

### 背景介绍 

CLion只支持使用Cmake工具构建项目,但是有很多项目是使用make进行构建的(比如php核心源码/redis源码),那么如何将一个make项目导入到CLion中,转化为CMake构建方式呢,
这样我们就能使用CLion阅读一些开源软件,使用我们熟悉的小瓢虫进行断点调试了

首先回顾一下CMake与make的关系

make是帮助构建(构建就是编译生成可执行程序一系列操作过程的统称)C/C++项目的工具,它可以解析makefile中的内容，根据makefile中的rule决定编译的先后顺序，依赖关系,
同一套源码在不同平台上的makefile内容是不一样的，所以在Centos上的makefile可能需要进行很大的改动才可以在Ubuntu上使用.CMake则负责生成针对于不同平台的makefile，
CMake生成makefile依赖于一个叫做CMakeLists.txt的文件,该文件的内容也是一些控制编译顺序/依赖关系的rule.CMakeLists.txt可以跨平台使用,而makefile不可以跨平台使用.

### 开发环境

	[sujianhui@nlp ~]$ cat /etc/centos-release
	CentOS Linux release 7.7.1908 (Core)
	[sujianhui@nlp ~]$ gcc -v
	gcc version 4.8.5 20150623 (Red Hat 4.8.5-39) (GCC)
	[sujianhui@nlp ~]$ gdb -v
	GNU gdb (GDB) Red Hat Enterprise Linux 7.6.1-115.el7
	[sujianhui@nlp ~]$ make -v
	GNU Make 3.82

	cmake 用的是CLion套件里自带的
	CLion的版本是 clion2020.1
	

### 解决思路分析(以php源码为例)

在未使用CLion之前,我们是这样编译的

	wget https://www.php.net/distributions/php-7.1.0.tar.gz
	tar -zxvf php-7.1.0.tar.gz
	cd php-7.1.0.tar.gz
	# 使用官方提供的侦测shell脚本生成makefile
	./configure --prefix=/home/sujianhui/php_debug/ --enable-fpm --enable-debug  
	make 
	make install 
	# 终端中使用gdb 进行源码调试
	gdb /home/sujianhui/php_debug/bin/php 

我的目的很简单,就是想使用CLion断点调试php内核源码,方便阅读,有了目的才能有解决思路,解决思路大概有两种

1 对照./configure命令生成的makefile,逆推生成CMakeLists.txt
2 使用./configure 生成的makefile,不需要使用CMake生成新的makefile

 - 第一种思路,很快就会被pass掉，这样搞不但耗时长,而且很容易出问题，得不偿失
 - 第二种思路,需要将CMakeLists.txt中生成makefile这一环节的rule替换为使用php源码自带的configure侦测脚本生成即可,原理上是可行的


### 实操

1 `CLion -> File -> New CMake Project From Source` 打开你解压完毕的源码目录,这一步CLion会在新项目根目录中创建一个CMakeLists.txt文件,cmake-build-debug文件夹,
当从 Source 导入生成CMake Project时,CLion会扫描 Source中所有含有`main`函数的.c文件，作为参数添加到`add_executable`命令中,如下

    add_executable(< name> [WIN32] [MACOSX_BUNDLE]
    [EXCLUDE_FROM_ALL]
    source1 source2 … sourceN)

    add_executable(C
        algorithm/sort/bubble_sort.c
        algorithm/sort/insert_sort.c
        algorithm/sort/merge_sort.c
        algorithm/sort/quick_sort.c
        algorithm/stack/maze/error_maze.c
        algorithm/stack/maze/example_maze.c
        algorithm/stack/maze/maze.c
        array/const_arr.c
        ...
        tool_makefile/main.h
        virtual_memory_manage/par1.c
        virtual_memory_manage/par2.c)

按照如上顺序对源文件进行Build,最终输出一个名为`C`的可执行文件

2 vim CMakeLists.txt,修改为如下格式

	cmake_minimum_required(VERSION 3.16)
	project(php_7_1_0)

	set(CMAKE_CXX_STANDARD 14)

	#定义php源码路径，这里根据自己的真实路径来更改
	set(PHP_SOURCE /home/sujianhui/CLionProjects/php-7.1.0)
	set(PHP_BIN_OUTPUT /home/sujianhui/CLionProjects/output/php7_1/)

	#引入php需要的扩展源码，这里也是根据自己需要的来更改
	include_directories(${PHP_SOURCE}/main)
	include_directories(${PHP_SOURCE}/Zend)
	include_directories(${PHP_SOURCE}/sapi)
	include_directories(${PHP_SOURCE}/pear)
	include_directories(${PHP_SOURCE}/TSRM)
	include_directories(${PHP_SOURCE}/ext)
	include_directories(${PHP_SOURCE})
	
	# 注意 --enable-debug 必须得加上，否则断点调试会缺少调试符号信息
	add_custom_target(makefile COMMAND ./configure --prefix=${PHP_BIN_OUTPUT} --enable-fpm --enable-debug && make 
        	WORKING_DIRECTORY ${PHP_SOURCE})

	add_custom_target(learn_extend COMMAND sudo ${PHP_BIN_OUTPUT}bin/phpize && ./configure --with-php-config=${PHP_BIN_OUTPUT}/bin/php-config &&  make
        	WORKING_DIRECTORY ${PHP_SOURCE})

上面内容中的

	add_custom_target(makefile COMMAND ./configure --prefix=${PHP_BIN_OUTPUT} --enable-fpm --enable-debug && make
                 WORKING_DIRECTORY ${PHP_SOURCE})

命令实现的就是执行 ./configure 脚本生成makefile,替换原本应该出现的复杂的cmake rule，配置完这一步之后，你会发现小瓢虫已经亮起来了

3 点击CLion上方导航栏小瓢虫左侧的Edit Configurations,弹出框中选择CMake Applications 下的 makefile target 进行配置
	
	# 该参数指定当点击导航栏 run（小三角icon） 按钮时,执行哪一个可执行文件, 这里我选择了build后生成的php，相当于 gdb $(PHP_BIN_OUTPUT)/bin/php
	Executable : 选择$(PHP_BIN_OUTPUT)/bin/php                       
	
	# 该参数制定的是当点击导航兰 run 按钮时,传入到可执行程序的参数,相当于在gdb bash 中执行 : r /home/sujianhui/php/1.php (1.php 是随便写的一个php文件)
	Programs Arguments : -f /home/sujianhui/php/1.php 

	# 该列中指定的是在点击run按钮后，在真正的可执行程序被执行之前，需要执行的操作,默认添加了build操作,即每次run/debug之前，都会强制重新Build一下 ,这个配置看个人需要吧
	Before Launch : 去掉 Build 

4 CLion中打开 sapi/cli/php_cli.c ，在main函数的起始处(我这里是 1192行)设置断点,点击小瓢虫，如果正常的话,断点已经会生效了


### 小结

在配置过程中遇到各种问题很正常，如果你需要这个东西，你先得了解解决方案的思路，然后按照这个思路去解决配置过程中出现的各种问题.
比如你可能会遇到Build时多核编译warning 的问题..

CLion导航栏目中的Build run Debug的区别

 - Build  : ./configure 生成makefile ，make 工具解析makefile 进行编译,安装,直至生成二进制可执行文件这一过程的统称
 - run    : 执行一下Build 生成的二进制文件,比如我们编译安装完php源码后，通常会看一下开启了哪些模块,这时我们会在shell中执行`php -m `,这就是run
 - Debug  : 以调试模式运行一个进行,debug实质为父进程检测子进程（日如gdb为父进程，gdb调试的进程为子进程）

Debug 的Setting Path为: File -> Setting -> Build,Execution,Deployment -> CMake 弹窗中,这里你可以设置一些Debug时的参数

### 参考资料

他这个里面有图片，我本地环境有点问题，就没有截图，参考一下吧
https://blog.csdn.net/weixin_44056915/article/details/102859556



