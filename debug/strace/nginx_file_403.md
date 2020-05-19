## use strace reslove 403

find nginx worker pid 

    [sujianhui@dev529 bin]$>ps aux | grep nginx
    root      4458  0.0  0.0  46468  1196 ?        Ss   09:41   0:00 nginx: master process /usr/sbin/nginx -c /etc/nginx/nginx.conf
    sujianh+  4459  0.0  0.0  49092  2540 ?        S    09:41   0:00 nginx: worker process
    sujianh+  8431  0.0  0.0 112820   976 pts/0    S+   10:15   0:00 grep --color=auto nginx
    
attach strace listen list this nginx work process
    
    [sujianhui@dev529 bin]$>strace -p 4459
    strace: Process 4459 attached
    epoll_wait(8, [{EPOLLIN, {u32=3349491632, u64=93985823862704}}], 512, -1) = 1
    ...
    ...
    ...
    !!!(when request in browser , follow message will display)
    accept4(6, {sa_family=AF_INET, sin_port=htons(39846), sin_addr=inet_addr("127.0.0.1")}, [16], SOCK_NONBLOCK) = 5
    epoll_ctl(8, EPOLL_CTL_ADD, 5, {EPOLLIN|EPOLLRDHUP|EPOLLET, {u32=3349492560, u64=93985823863632}}) = 0
    epoll_wait(8, [{EPOLLIN, {u32=3349492560, u64=93985823863632}}], 512, 60000) = 1
    recvfrom(5, "GET /index.html HTTP/1.1\r\nHost: "..., 1024, 0, NULL, NULL) = 447
    open("/home/sujianhui/PhpstormProjects/pfd/index.html", O_RDONLY|O_NONBLOCK) = -1 ENOENT (No such file or directory)
    gettid()                                = 4459
    write(3, "2020/05/18 10:15:53 [error] 4459"..., 239) = 239
    open("/home/sujianhui/PhpstormProjects/pfd/404.html", O_RDONLY|O_NONBLOCK) = -1 ENOENT (No such file or directory)
    gettid()                                = 4459
    write(3, "2020/05/18 10:15:53 [error] 4459"..., 237) = 237
    writev(5, [{"HTTP/1.1 404 Not Found\r\nServer: "..., 155}, {"<html>\r\n<head><title>404 Not Fou"..., 100}, {"<hr><center>nginx/1.18.0</center"..., 53}, {"<!-- a padding to disable MSIE a"..., 402}], 4) = 710
    write(4, "127.0.0.1 - - [18/May/2020:10:15"..., 194) = 194
    setsockopt(5, SOL_TCP, TCP_NODELAY, [1], 4) = 0
    epoll_wait(8, [{EPOLLIN, {u32=3349491632, u64=93985823862704}}], 512, 65000) = 1
    accept4(6, {sa_family=AF_INET, sin_port=htons(39848), sin_addr=inet_addr("127.0.0.1")}, [16], SOCK_NONBLOCK) = 11
    epoll_ctl(8, EPOLL_CTL_ADD, 11, {EPOLLIN|EPOLLRDHUP|EPOLLET, {u32=3349492097, u64=93985823863169}}) = 0
    epoll_wait(8, 


引起`nginx 403 forbidden`通常是三种情况：

 - 一是缺少索引文件，
 - 二是权限问题，
 - 三是SELinux状态。


    [sujianhui@dev529 pfd]$>sudo /usr/sbin/sestatus
    [sudo] password for sujianhui: 
    SELinux status:                 enabled
    SELinuxfs mount:                /sys/fs/selinux
    SELinux root directory:         /etc/selinux
    Loaded policy name:             targeted
    Current mode:                   enforcing
    Mode from config file:          enforcing
    Policy MLS status:              enabled
    Policy deny_unknown status:     allowed
    Max kernel policy version:      31
    
resolve 
   
永久关闭
     
    vi  /etc/sysconfig/selinux
    SELINUX=enforcing   => SELINUX=disabled
    shutdown -r now
    
临时关闭，重启机器后恢复原状态：

    sudo setenforce 0             
 
