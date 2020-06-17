## lsof

Linux 平台提供了 lsof 工具可以查看某个进程打开的文件句柄。可以用于跟踪 swoole 的工作进程所有打开的 socket、file、资源。 

    lsof -p 26821
    lsof: WARNING: can't stat() tracefs file system /sys/kernel/debug/tracing
          Output information may be incomplete.
    COMMAND   PID USER   FD      TYPE             DEVICE SIZE/OFF    NODE NAME
    php     26821  htf  cwd       DIR                8,4     4096 5375979 /home/htf/workspace/swoole/examples
    php     26821  htf  rtd       DIR                8,4     4096       2 /
    php     26821  htf  txt       REG                8,4 24192400 6160666 /opt/php/php-5.6/bin/php
    php     26821  htf  DEL       REG                0,5          7204965 /dev/zero
    php     26821  htf  DEL       REG                0,5          7204960 /dev/zero
    php     26821  htf  DEL       REG                0,5          7204958 /dev/zero
    php     26821  htf  DEL       REG                0,5          7204957 /dev/zero
    php     26821  htf  DEL       REG                0,5          7204945 /dev/zero
    php     26821  htf  mem       REG                8,4   761912 6160770 /opt/php/php-5.6/lib/php/extensions/debug-zts-20131226/gd.so
    php     26821  htf  mem       REG                8,4  2769230 2757968 /usr/local/lib/libcrypto.so.1.1
    php     26821  htf  mem       REG                8,4   162632 6322346 /lib/x86_64-linux-gnu/ld-2.23.so
    php     26821  htf  DEL       REG                0,5          7204959 /dev/zero
    php     26821  htf    0u      CHR             136,20      0t0      23 /dev/pts/20
    php     26821  htf    1u      CHR             136,20      0t0      23 /dev/pts/20
    php     26821  htf    2u      CHR             136,20      0t0      23 /dev/pts/20
    php     26821  htf    3r      CHR                1,9      0t0      11 /dev/urandom
    php     26821  htf    4u     IPv4            7204948      0t0     TCP *:9501 (LISTEN)
    php     26821  htf    5u     IPv4            7204949      0t0     UDP *:9502 
    php     26821  htf    6u     IPv6            7204950      0t0     TCP *:9503 (LISTEN)
    php     26821  htf    7u     IPv6            7204951      0t0     UDP *:9504 
    php     26821  htf    8u     IPv4            7204952      0t0     TCP localhost:8000 (LISTEN)
    php     26821  htf    9u     unix 0x0000000000000000      0t0 7204953 type=DGRAM
    php     26821  htf   10u     unix 0x0000000000000000      0t0 7204954 type=DGRAM
    php     26821  htf   11u     unix 0x0000000000000000      0t0 7204955 type=DGRAM
    php     26821  htf   12u     unix 0x0000000000000000      0t0 7204956 type=DGRAM
    php     26821  htf   13u  a_inode               0,11        0    9043 [eventfd]
    php     26821  htf   14u     unix 0x0000000000000000      0t0 7204961 type=DGRAM
    php     26821  htf   15u     unix 0x0000000000000000      0t0 7204962 type=DGRAM
    php     26821  htf   16u     unix 0x0000000000000000      0t0 7204963 type=DGRAM
    php     26821  htf   17u     unix 0x0000000000000000      0t0 7204964 type=DGRAM
    php     26821  htf   18u  a_inode               0,11        0    9043 [eventpoll]
    php     26821  htf   19u  a_inode               0,11        0    9043 [signalfd]
    php     26821  htf   20u  a_inode               0,11        0    9043 [eventpoll]
    php     26821  htf   22u     IPv4            7452776      0t0     TCP localhost:9501->localhost:59056 (ESTABLISHED)
 
注释: 
    
 - so 文件是进程加载的动态连接库
 - IPv4/IPv6 TCP (LISTEN) 是服务器监听的端口
 - UDP 是服务器监听的 UDP 端口
 - unix type=DGRAM 时是进程创建的 unixSocket
 - IPv4 (ESTABLISHED) 表示连接到服务器的 TCP 客户端，包含了客户端的 IP 和 PORT，以及状态 (ESTABLISHED)
 - 9u / 10u 表示该文件句柄的 fd 值 (文件描述符)
 
其他更多信息可以参考 lsof 的手册