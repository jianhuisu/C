## 解决php.ini not load 问题
    
    [sujianhui@dev529 ~]$>php --ini
    Configuration File (php.ini) Path: /usr/local/php
    Loaded Configuration File:         (none)
    Scan for additional .ini files in: (none)
    Additional .ini files parsed:      (none)

`Loaded Configuration File` 一项显示的是加载的 `php.ini` 文件，如果值为 `none` 证明根本没加载任何 `php.ini` 文件.
(或者可以使用`php -i`获取更为详细的信息,类似于打印`phpinfo()`).


#### 解决方案 

使用`strace`去追踪一下：

    strace /usr/local/php/bin/php -i 2> ~/1.log
    grep 'php.ini' ~/1.log 显示如下信息：
    [sujianhui@dev529 ~]$>grep 'php.ini' 1.log 
    open("/usr/local/php/bin/php.ini", O_RDONLY) = -1 ENOENT (No such file or directory)
    open("/usr/local/php/php.ini", O_RDONLY) = -1 ENOENT (No such file or directory)
    write(1, "Configuration File (php.ini) Pat"..., 33) = 33

将源码包中的`php.ini`复制一份到`php`的安装目录.

    [sujianhui@dev529 php]$>cp /usr/local/php-7.3.0/etc/php.ini /usr/local/php/
    [sujianhui@dev529 php]$>cat php.ini | egrep -v ";|^$"
    
注：如果编译时指定配置文件路径（`--with-config-file-path=/usr/local/php/etc`），PHP会先去加载指定的配置文件，如果未找到会去找默认配置文件存放路径。


