## netstat 输出解释

    [sujianhui@nlp ~]$ netstat -ant
    Active Internet connections (servers and established)
    Proto Recv-Q Send-Q Local Address           Foreign Address         State      
    tcp        0      0 127.0.0.1:631           0.0.0.0:*               LISTEN     
    tcp        0      0 127.0.0.1:25            0.0.0.0:*               LISTEN     
    tcp        0      0 0.0.0.0:111             0.0.0.0:*               LISTEN     
    tcp        0      0 192.168.122.1:53        0.0.0.0:*               LISTEN     
    tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN     
    tcp        0      0 192.168.1.105:32968     59.111.179.135:443      ESTABLISHED
    tcp        0      0 192.168.1.105:41800     106.12.63.108:443       ESTABLISHED
    tcp        1      1 192.168.1.105:58538     182.61.200.5:443        LAST_ACK   
    tcp        0      1 192.168.1.105:48418     104.18.56.214:443       SYN_SENT   
    tcp        0      1 192.168.1.105:55294     185.199.109.153:80      SYN_SENT   
    tcp        0      1 192.168.1.105:55298     185.199.109.153:80      SYN_SENT   
    tcp        0      1 192.168.1.105:55296     185.199.109.153:80      SYN_SENT   
    tcp        0      1 192.168.1.105:48420     104.18.56.214:443       SYN_SENT   
    tcp        0      1 192.168.1.105:55650     172.217.160.109:443     SYN_SENT   
    tcp        0      1 192.168.1.105:55648     172.217.160.109:443     SYN_SENT   
    tcp        1      1 192.168.1.105:32930     182.61.200.7:443        LAST_ACK   
    tcp        1      1 192.168.1.105:32932     182.61.200.7:443        LAST_ACK   
    tcp6       0      0 ::1:631                 :::*                    LISTEN     
    tcp6       0      0 ::1:25                  :::*                    LISTEN     
    tcp6       0      0 127.0.0.1:6942          :::*                    LISTEN     
    tcp6       0      0 127.0.0.1:63342         :::*                    LISTEN     
    tcp6       0      0 :::111                  :::*                    LISTEN     
    tcp6       0      0 :::22                   :::*                    LISTEN    
    
上边每一条代表一个socket链接,主要分为两类

 - `tcp        0      0 127.0.0.1:631           0.0.0.0:*               LISTEN` 这个是监听套接字
 - `tcp        1      1 192.168.1.105:32932     182.61.200.7:443        LAST_ACK` 这个就是普通带双端的套接字,一个客户端`Local Address`,一个服务端`Foreign Address`   