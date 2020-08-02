## pidstat

pidstat是sysstat工具的一个命令，用于监控全部或指定进程的cpu、内存、线程、设备IO等系统资源的占用情况。
pidstat首次运行时显示自系统启动开始的各项统计信息，之后运行pidstat将显示自上次运行该命令以后的统计信息。
用户可以通过指定统计的次数和时间来获得所需的统计信息。

pidstat 是sysstat软件套件的一部分，sysstat包含很多监控linux系统状态的工具，它能够从大多数linux发行版的软件源中获得。
在Debian/Ubuntu系统中可以使用下面的命令来安装:

    apt-get install sysstat
    
CentOS/Fedora/RHEL版本的linux中则使用下面的命令：

    yum install sysstat

#### 使用范例

监控所有进程的IO情况,间隔5s,打印2次.

    [sujianhui@dev0529 ~]$>pidstat -d 5 2
    Linux 3.10.0-1127.13.1.el7.x86_64 (dev0529) 	07/31/2020 	_x86_64_	(4 CPU)
    
    09:47:06 AM   UID       PID   kB_rd/s   kB_wr/s kB_ccwr/s  Command
    09:47:11 AM  1000      3307      0.00      7.98      0.00  chrome
    09:47:11 AM  1000      3351      0.00     14.37      0.00  chrome
    09:47:11 AM  1000      4256      0.00      3.99      0.00  java
    09:47:11 AM  1000      4707      0.00      3.99      0.00  java
    
    09:47:11 AM   UID       PID   kB_rd/s   kB_wr/s kB_ccwr/s  Command
    09:47:16 AM  1000      4256      0.00      4.00      0.00  java
    09:47:16 AM  1000      4707      0.00      4.00      0.00  java
    
    Average:      UID       PID   kB_rd/s   kB_wr/s kB_ccwr/s  Command
    Average:     1000      3307      0.00      4.00      0.00  chrome
    Average:     1000      3351      0.00      7.19      0.00  chrome
    Average:     1000      4256      0.00      4.00      0.00  java
    Average:     1000      4707      0.00      4.00      0.00  java


监控nginx进程的IO情况

    [sujianhui@dev0529 ~]$>systemctl start nginx
    [sujianhui@dev0529 ~]$>ps aux | grep nginx
    root      5584  0.0  0.0  46608  1072 ?        Ss   09:49   0:00 nginx: master process /usr/sbin/nginx -c /etc/nginx/nginx.conf
    sujianh+  5585  0.0  0.0  49124  2080 ?        S    09:49   0:00 nginx: worker process
    sujianh+  5614  0.0  0.0 112812   972 pts/0    S+   09:49   0:00 grep --color=auto nginx
    [sujianhui@dev0529 ~]$>pidstat -d -p 5584 2
    Linux 3.10.0-1127.13.1.el7.x86_64 (dev0529) 	07/31/2020 	_x86_64_	(4 CPU)
    
    09:51:56 AM   UID       PID   kB_rd/s   kB_wr/s kB_ccwr/s  Command
    09:51:58 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:00 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:02 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:04 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:06 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:08 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:10 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:12 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:14 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:16 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:18 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:20 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:22 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:24 AM     0      5584      0.00      0.00      0.00  nginx
    09:52:26 AM     0      5584      0.00      0.00      0.00  nginx
    ^C
    Average:        0      5584      0.00      0.00      0.00  nginx
    [sujianhui@dev0529 ~]$>pidstat -d -p 5585 2
    Linux 3.10.0-1127.13.1.el7.x86_64 (dev0529) 	07/31/2020 	_x86_64_	(4 CPU)
    
    09:52:35 AM   UID       PID   kB_rd/s   kB_wr/s kB_ccwr/s  Command
    09:52:37 AM  1000      5585      0.00      0.00      0.00  nginx
    09:52:39 AM  1000      5585      0.00      2.00      0.00  nginx
    09:52:41 AM  1000      5585      0.00      2.00      0.00  nginx
    09:52:43 AM  1000      5585      0.00      2.00      0.00  nginx
    09:52:45 AM  1000      5585      0.00      0.00      0.00  nginx
    09:52:47 AM  1000      5585      0.00      0.00      0.00  nginx
    09:52:49 AM  1000      5585      0.00      0.00      0.00  nginx
    ^C
    Average:     1000      5585      0.00      0.86      0.00  nginx

在MyISAM存储引擎上使用一个覆盖索引扫描时,我们就可以使用pidstat来监控IO,CPU，上下文,内存占用等资源使用情况.