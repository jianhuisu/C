netstat命令监测tcp链接数量

    [guangsujiqiang@su-ct7 ~]$>netstat -ant
    Active Internet connections (servers and established)
    Proto Recv-Q Send-Q Local Address           Foreign Address         State
    tcp        0      0 0.0.0.0:80              0.0.0.0:*               LISTEN
    tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN
    ...
    tcp        0      1 172.16.125.203:50150    61.135.169.125:443      FIN_WAIT1
    tcp        0      1 172.16.125.203:41982    123.58.182.252:443      LAST_ACK
    tcp        0      0 172.16.125.203:42000    123.58.182.252:443      CLOSE_WAIT
    tcp        0      0 172.16.125.203:50306    58.251.111.105:80       ESTABLISHED
    ...

### man netstat 查看参数

- -a : 显示所有链接,对于TCP链接来说，使用本参数会将处于LISTEN状态的TCP链接显示
- -t : 协议类型为TCP
- -n : 以数字而不是助记符形式显示

### 输出字段简介

- Proto：协议,[TCP|UDP|unix]
- Recv-Q：链接的网络接收队列
- Send-Q：该链接的网络发送队列
- Local Address ： SOCKET链接之本地端
- Foreign Address ： SOCKET链接之远端
- State ： 链接状态

### 输出字段详细介绍

#### Proto

    [guangsujiqiang@su-ct7 ~]$>netstat -n | egrep -v 'Active|Proto' | awk '{print $1}' | uniq
    tcp
    udp
    unix

#### recv-Q

    表示收到的数据已经在本地接收缓冲，但是还有多少没有被进程取走，recv()如果接收队列Recv-Q一直处于阻塞状态，可能是遭受了拒绝服务 denial-of-service 攻击。

#### send-Q

    对方没有收到的数据或者说没有Ack的,还是本地缓冲区.如果发送队列Send-Q不能很快的清零，可能是有应用向外发送数据包过快，或者是对方接收数据包不够快。
    recv-Q/send-Q两个值通常应该为0，如果不为0可能是有问题的。packets在两个队列里都不应该有堆积状态。可接受短暂的非0情况。

#### State

各状态对应三次握手与四次挥手

    LISTEN       ： 侦听来自远方的TCP端口的连接请求 服务器在等待进入呼叫
    SYN-SENT     ： 发送连接请求，等待确认
    SYN-RECEIVED ： 发送(连接请求已收到,同意连接)的请求,等待确认
    ESTABLISHED  ： 已成功建立的链接
    FIN-WAIT-1   ： todo
    FIN-WAIT-2   ： todo
    CLOSE-WAIT   ： todo
    CLOSING      ： todo
    LAST-ACK     ： todo
    TIME-WAIT    ： todo
    CLOSED       ： todo

### 实际应用场景

#### nginx最大链接数问题

   网站在线人数增多，访问时很慢。初步认为是服务器资源不足了，但经反复测试，一旦连接上，不断点击同一个页面上不同的链接，都能迅速打开，这种现象就是说明Nginx最大连接数已经满了，
新的访客只能排队等待有空闲的链接，而如果一旦连接上，在keep-alive 的存活时间内不用重新打开连接，因此解决的方法可以加大Nginx的最大连接数。

    [root@web01 conf]# cat /usr/local/nginx/conf/nginx.conf

    # worker_processes 指明了nginx要开启的进程数 ,
    # 一般使用默认值即可[或者auto] 如果要修改必须要和CPU的内核数匹配
    # 用例 ： value 为 2时, nginx 服务会开2个worker进程 1 个master进程
    worker_processes  2;
    ...
    user www www;

    # 为nginx工作进程改变打开最多文件描述符数目的限制
    # 用来在不重启主进程的情况下增加限制 nginx -s reload 不会重启master
    # 但是会重启所有worker
    # 这个也与 ulimit -n 有关
    # ulimit -n 通过修改 /etc/security/limits.conf 修改，重启服务器生效
    # (limit -n 对于 root 用户没有限制，没有限制 ，仅适合一些骚操作)
    worker_rlimit_nofile 65535;

    events {

        # 每一个worker进程能同时维持的最大连接数（包含所有连接数）。
        # 不能超过最大文件打开数,使用 ulimit -n 进行查看
        worker_connections  20480;
    }

    http {
        include       mime.types;
        default_type  application/octet-stream;
        sendfile        on;

        # 单位 秒,Nginx 在处理完一个请求后保持这个 TCP 连接的打开状态。
        # 若接收到来自同一客户端的其它请求，利用这个未被关闭的连接，而不需要再建立一个连接。
        # Nginx 的默认值是 75 秒，有些浏览器最多只保持 60 秒，所以可以设定为 60 秒。
        # 若将它设置为 0，就禁止了 keepalive 连接。
        # 其它超时参数可参考 https://blog.csdn.net/weixin_42350212/article/details/81123932
        keepalive_timeout  65;
        server_tokens on;
        ....
    }

链接数应该设为多少呢?连接数理论上当然是支持越大越好，但要在服务器的能力范围内，
这跟服务器的CPU、内存、带宽等都有关系。 终极的解决办法是进行负载均衡

##### 监控当其主机维持多少个TCP链接

查看活跃的TCP链接

    netstat -nt | grep ESTABLISHED

查看80或443端口的TCP链接(也可以理解为Nginx的并发访问数)

    [root@ ~]$>netstat -nt | grep ESTABLISHED | egrep ':80|:443'
    tcp        0      0 172.17.51.219:46696     100.100.30.25:80        ESTABLISHED
    tcp        0      0 172.17.51.219:443       111.198.190.132:21238   ESTABLISHED
    tcp        0      0 172.17.51.219:443       111.198.190.132:21237   ESTABLISHED

查看Nginx的并发请求数及其TCP连接状态：
    
    netstat -n | awk '/^tcp/ {++S[$NF]} END {for(a in S) print a, S[a]}'  

这个命令统计结果与实际值稍有出入,待我后续补充

// todo watch 命令使用指南