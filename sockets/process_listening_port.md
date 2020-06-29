## 端口监听相关Tips


#### 同一个进程可以监听多个端口

    [sujianhui@dev0529 php-fpm.d]$>sudo netstat -ntpl | grep php
    tcp        0      0 127.0.0.1:9000          0.0.0.0:*               LISTEN      12488/php-fpm: mast 
    tcp        0      0 127.0.0.1:9007          0.0.0.0:*               LISTEN      12488/php-fpm: mast
    
同一个php-fpm master 进程监听两个 `worker pool`的端口. 

#### 多个进程可以监听同一个端口吗

当然可以，只要你使用 SO_REUSEPORT 这个参数。

还是先来看下man文档中是怎么说的：

    SO_REUSEPORT (since Linux 3.9)
    Permits multiple AF_INET or AF_INET6 sockets to be bound to an
    identical socket address.  This option must be set on each
    socket (including the first socket) prior to calling bind(2)
    on the socket.  To prevent port hijacking, all of the pro‐
    cesses binding to the same address must have the same effec‐
    tive UID.  This option can be employed with both TCP and UDP
    sockets.
    
    For TCP sockets, this option allows accept(2) load distribu‐
    tion in a multi-threaded server to be improved by using a dis‐
    tinct listener socket for each thread.  This provides improved
    load distribution as compared to traditional techniques such
    using a single accept(2)ing thread that distributes connec‐
    tions, or having multiple threads that compete to accept(2)
    from the same socket.
    
    For UDP sockets, the use of this option can provide better
    distribution of incoming datagrams to multiple processes (or
    threads) as compared to the traditional technique of having
    multiple processes compete to receive datagrams on the same
    socket.
    
从文档中可以看到，该参数允许多个socket绑定到同一本地地址，即使socket是处于listen状态的。
当多个listen状态的socket绑定到同一地址时，各个socket的accept操作都能接受到新的tcp连接。
https://cloud.tencent.com/developer/article/1485911


