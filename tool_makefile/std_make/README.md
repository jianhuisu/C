## 自动处理头文件的依赖关系

人工数里依赖关系很容易出现错误,gcc套件提供了工具动态解析依赖关系

 - gcc -M main.c  输出以main.c源文件的依赖,`包括` 系统头文件的依赖关系 例如 stdio.h的依赖关系
 - gcc -MM main.c 输出以main.c源文件的依赖,`不包括`对操作系统的依赖项
 
### GNU官方建议Makefile写法

    all: main
    main: main.o stack.o maze.o
        gcc $^ -o $@
    clean:
        -rm main *.o
    .PHONY: clean
    sources = main.c stack.c maze.c
    include $(sources:.c=.d)
    %.d: %.c
        set -e; rm -f $@; \
        $(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
        sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
        rm -f $@.$$$$
        
注意，虽然在Makefile中这个命令写了四行，但其实是一条命令，make只创建一个Shell进程执行这条命令，**这条命令分为5个子命令，用;号隔开**，并且为了美观，用续行符\拆成四行来写。执行步骤为：

 - set -e命令设置当前Shell进程为这样的状态：如果它执行的任何一条命令的退出状态非零则立刻终止，不再执行后续命令。
 - 把原来的maze.d删掉。
 - 重新生成maze.c的依赖关系，保存成文件maze.d.1234（假设当前Shell进程的id是1234）。注意，在Makefile中$有特殊含义，如果要表示它的字面意思则需要写两个$，所以Makefile中的四个$传给Shell变成两个$，两个$在Shell中表示当前进程的id，一般用它给临时文件起名，以保证文件名唯一。
 - 经过sed处理之后存为maze.d，其内容是maze.o maze.d: maze.c maze.h main.h。
 - 最后把临时文件maze.d.1234删掉。
 
特殊变量(下面的规则指紧紧相临的规则)
 
 - $@，表示规则中的目标
 - $<，表示规则中的第一个条件
 - $?，表示规则中所有比目标新的条件，组成一个列表，以空格分隔
 - $^，表示规则中的所有条件，组成一个列表，以空格分隔
 
 
    main: main.o stack.o maze.o
        gcc main.o stack.o maze.o -o main
        
    =>
    
    main: main.o stack.o maze.o
    	gcc $^ -o $@
    	
### 子模块的Makefile

进入到子目录`testmake`,编译下面的Makefile

    make -C testmake

-C选项可以切换到另一个目录执行那个目录下的Makefile，比如先退到上一级目录再执行我们的Makefile（假设我们的源代码都放在testmake目录下）：
一些规模较大的项目会把不同的模块或子系统的源代码放在不同的子目录中，然后在每个子目录下都写一个该目录的Makefile，
然后在一个总的Makefile中用make -C命令执行每个子目录下的Makefile。
例如Linux内核源代码根目录下有Makefile，子目录fs、net等也有各自的Makefile，二级子目录fs/ramfs、net/ipv4等也有各自的Makefile。

思考：为什么需要模块这一个概念呢? heihei

### debug

在make命令行也可以用`=`或`:=`定义变量，如果这次编译我想加调试选项`-g`，但我不想每次编译都加-g选项，
可以在命令行定义CFLAGS变量，而不必修改Makefile编译完了再改回来：(这个超实用且很常见)

    $ make CFLAGS=-g
    cc -g   -c -o main.o main.c
    cc -g   -c -o stack.o stack.c
    cc -g   -c -o maze.o maze.c
    gcc main.o stack.o maze.o -o main
    
如果在Makefile中也定义了CFLAGS变量，则命令行的值覆盖Makefile中的值。

-n选项只打印要执行的命令，而不会真的执行命令，这个选项有助于我们检查Makefile写得是否正确，由于Makefile不是顺序执行的，
用这个选项可以先看看命令的执行顺序，确认无误了再真正执行命令。


### 应该把哪些内容放置在头文件中 哪些内容放置在源文件中

我看了一下redis的源码,例如 src/cluster.h src/cluster.c

其中 cluster.h中主要包括以下内容

    #ifndef __CLUSTER_H
    #define __CLUSTER_H
    
    /*-----------------------------------------------------------------------------
    * Redis cluster data structures, defines, exported API.
    *----------------------------------------------------------------------------*/
    
    #define CLUSTER_SLOTS 16384
    ...
    #define CLUSTER_REDIR_DOWN_UNBOUND 6  /* -CLUSTERDOWN, unbound slot. */
    
    struct clusterNode;
    
    /* clusterLink encapsulates everything needed to talk with a remote node. */
    typedef struct clusterLink {
        mstime_t ctime;             /* Link creation time */
        connection *conn;           /* Connection to remote node */
        sds sndbuf;                 /* Packet send buffer */
        sds rcvbuf;                 /* Packet reception buffer */
        struct clusterNode *node;   /* Node related to this link if any, or NULL */
    } clusterLink;
    
    typedef struct clusterNode {
        ...
        int port;                   /* Latest known clients port of this node */
        int cport;                  /* Latest known cluster port of this node. */
        clusterLink *link;          /* TCP/IP link with this node */
        list *fail_reports;         /* List of nodes signaling this as failing */
    } clusterNode;
    
    union clusterMsgData {
        /* PING, MEET and PONG */
        struct {
        /* Array of N clusterMsgDataGossip structures */
        clusterMsgDataGossip gossip[1];
    } ping;
    
    #define CLUSTERMSG_MIN_LEN (sizeof(clusterMsg)-sizeof(union clusterMsgData))
    
    clusterNode *getNodeByQuery(client *c, struct redisCommand *cmd, robj **argv, int argc, int *hashslot, int *ask);
    int clusterRedirectBlockedClientIfNeeded(client *c);
    void clusterRedirectClient(client *c, clusterNode *n, int hashslot, int error_code);
    
    #endif /* __CLUSTER_H */
 
而在源码文件cluster.c中

    #include "server.h"
    #include "cluster.h"
    #include "endianconv.h"
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/file.h>
    #include <math.h>
    函数定义...

总结来说 头文件中主要包括

 - 宏
 - 结构/变量的声明 或 定义
 - 函数原型声明
 - 少量的include语句
 
 源码文件中主要包括
 
 - 大量的include语句
 - 函数原型的定义
 - 业务逻辑的实现
 