## tcp/udp 中的阻塞与非阻塞

tcp是字节流协议,只要到达一些数据,进程就会立刻被唤醒.这些数据可能是单个字节,也有可能是完整的TCP分节.
非阻塞方式调用IO函数时,如果操作不能被满足.IO函数会立刻返回`EWOULDBLOCK`.否则返回允许写入TCP缓存的字节数.