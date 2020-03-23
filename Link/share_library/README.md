### 动态库的制作(别名共享库)

动态库文件以`.so`结尾

制作共享库的目标文件与一般的目标文件不同

    gcc -c -fPIC stack/stack.c stack/push.c stack/pop.c stack/is_empty.c
    
-f后面跟一些编译选项，PIC是其中一种，表示生成位置无关代码（Position Independent Code）
共享库各段的加载地址并没有定死，可以加载到任意位置，因为指令中没有使用绝对地址，(相对应的 静态库中各段的加载地址是绝对地址)
因此称为位置无关代码。top和stack的绝对地址保存在一个地址表中，而指令通过**地址表做间接寻址，因此避免了将绝对地址写死在指令中**，
这也是一种避免硬编码的策略。   

### 共享库的查找顺序

当我们制作完一个动态库文件后,想要测试使用一下该动态库,
    
    // gcc -shared -o lib库文件名.so 目标文件列表,例如:stack.o pop.o push.o is_empty.o 
    [root@ share_library]$>gcc -shared -o libstack.so stack.o pop.o push.o is_empty.o 
    [root@ share_library]$>gcc main.c -L. -lstack -Istack.h -o main.o
    /usr/bin/ld: cannot find -lstack
    collect2: error: ld returned 1 exit status
    
动态库文件就在当前目录啊,为什么找不到呢？

共享库的搜索路径由动态链接器决定，从ld.so(8)的Man Page可以查到共享库路径的搜索顺序：

 - 1. LD_LIBRARY_PATH shell变量所指定的路径
 - 2. 从缓存文件/etc/ld.so.cache中查找,该文件内容由`ldconfig`读取`/etc/ld.so.conf`内容后生成
 - 3. 如果上述步骤都找不到，则到默认的系统路径中查找，依次是`/usr/lib`,`/lib`(centos7中安装软件时,库文件not found很多情况都是因为没有将/usr/lib64添加到为库路径)

响应的就有三种解决办法

#### 修改shell变量 LD_LIBRARY_PATH (适合在开发中临时使用)

    [root@ share_library]$>export LD_LIBRARY_PATH=.
    [root@ share_library]$>./main 
    或者 
    LD_LIBRARY_PATH=. ./main  
    
第二种方式是两条指令放到一起执行,注意理解,书中说 这种方式只适合在开发中临时使用,治标不治本

####  修改  /etc/ld.so.conf (最常用) 

把`libstack.so`所在目录的绝对路径添加到`/etc/ld.so.conf`中（该文件中每个路径占一行），然后运行`ldconfig`

    echo pwd >> /etc/ld.so.conf && ldconfig

`ldconfig`命令除了扫描`/etc/ld.so.conf`中配置的目录之外，同时会扫描一些默认目录，如`/lib`、`/usr/lib`等，
处理之后生成`/etc/ld.so.cache`缓存文件，动态链接器就从这个缓存中搜索共享库.
查看一下每个路径下都有哪些动态库

    [root@ share_library]$>ldconfig -v
    ldconfig: Path `/usr/lib' given more than once
    ldconfig: Path `/usr/local/lib' given more than once
    ldconfig: Path `/lib' given more than once
    ldconfig: Path `/lib64' given more than once
    ldconfig: Can't stat /libx32: No such file or directory
    ldconfig: Path `/usr/lib' given more than once
    ldconfig: Path `/usr/lib64' given more than once
    ldconfig: Can't stat /usr/libx32: No such file or directory
    
    /usr/local/freetype/lib:
        libfreetype.so.6 -> libfreetype.so.6.12.6
    /usr/lib64/mysql:
        libmysqlclient.so.18 -> libmysqlclient.so.18.0.0
    /usr/local/mysql/lib:
        libmysqlharness.so.1 -> libmysqlharness.so.1
        libmysqlclient.so.21 -> libmysqlclient.so.21.0.13
        libmysqlrouter.so.1 -> libmysqlrouter.so.1
    /usr/local/lib:
        libx264.so.157 -> libx264.so.157
        libcharset.so.1 -> libcharset.so.1.0.0
        libmcrypt.so.4 -> libmcrypt.so.4.4.8
        libmhash.so.2 -> libmhash.so.2.0.1
        libmp3lame.so.0 -> libmp3lame.so.0.0.0
        libiconv.so.2 -> libiconv.so.2.6.0
    /lib:
        libpng15.so.15 -> libpng.so
        libjpeg.so.62 -> libjpeg.so.62.1.0
        libmcrypt.so.4 -> libmcrypt.so.4.4.8
        libmhash.so.2 -> libmhash.so.2.0.1
    /usr/lib64:
        liblua-5.1.so -> liblua-5.1.so
        liblvm2app.so.2.2 -> liblvm2app.so.2.2
        ...
        libverto.so.1 -> libverto.so.1.0.0
        libkrb5support.so.0 -> libkrb5support.so.0.1
    /usr/local/lib64:
    /lib/sse2: (hwcap: 0x0000000004000000)
    /usr/lib64/tls: (hwcap: 0x8000000000000000)
    /usr/lib64/sse2: (hwcap: 0x0000000004000000)

`hwcap`是x86平台的Linux特有的一种机制，系统检测到当前平台是i686而不是i586或i486，所以在运行程序时使用i686的库，
这样可以更好地发挥平台的性能，也可以利用一些新的指令。

#### 将库文件copy到系统已经配置的lib_path下

这个没什么好说的创建的软链就可以

    ln -s libstack.so /usr/lib/libstack.so

### 共享库的命名规则

按照共享库的命名惯例，每个共享库有三个文件名

 - real name : 真正的库文件（而不是符号链接）的名字是real name，包含完整的共享库版本号.
 - soname : soname是一个符号链接的名字，只包含共享库的主版本号，主版本号一致即可保证库函数的接口一致. 
 - linker name : 只在链接的时候使用
 
#### real name

真正的库文件（不是符号链接）的名字是real name，包含完整的共享库版本号.

    [root@ share_library]$>ls -l /usr/lib64/
    ...
    lrwxrwxrwx   1 root root       19 Jul  8  2019 libX11-xcb.so -> libX11-xcb.so.1.0.0
    lrwxrwxrwx   1 root root       19 Jul  8  2019 libX11-xcb.so.1 -> libX11-xcb.so.1.0.0
    -rwxr-xr-x   1 root root     6848 Oct 31  2018 libX11-xcb.so.1.0.0
    lrwxrwxrwx   1 root root       15 Jul  8  2019 libXau.so -> libXau.so.6.0.0
    lrwxrwxrwx   1 root root       15 Jul  8  2019 libXau.so.6 -> libXau.so.6.0.0
    -rwxr-xr-x   1 root root    15512 Jun 10  2014 libXau.so.6.0.0
    lrwxrwxrwx   1 root root       25 Jul  8  2019 libxcb-composite.so -> libxcb-composite.so.0.0.0
    lrwxrwxrwx   1 root root       25 Jul  8  2019 libxcb-composite.so.0 -> libxcb-composite.so.0.0.0
    ...
    
`libxcb-composite.so.0.0.0`等价于`libxcb-composite.so.主版本号.次版本号.修改版本号`.对于使用者讲,`libxcb-composite.so.0.0.0`与
`libxcb-composite.so.0.1.0`没有区别 

real name 是我们制作共享库时指定的(尽量不要使用生成后手动改名的骚操作 听话)

    gcc -shared -o libstack.so.1.0.0 stack.o pop.o push.o is_empty.o     
    
#### soname

soname是一个符号链接的名字，只包含共享库的主版本号，主版本号一致即可保证库函数的接口一致.soname也是在制作共享库时指定的

    gcc -shared -Wl,-soname,libstack.so.1 -o libstack.so.1.0 stack.o push.o pop.o is_empty.o

`-Wl,-soname,libstack.so.1` 指定soname,使用readelf工具查看ELF文件信息

    [root@ share_library]$>readelf -a libstack.so.1.0 
    Dynamic section at offset 0xdf8 contains 25 entries:
      Tag        Type                         Name/Value
     0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
     0x000000000000000e (SONAME)             Library soname: [libstack.so.1]

soname被写入到了ELF文件中,**所以指定soname需要在制作时进行**. (当然 手动创建软链也可以,前提是确保名称正确).
如果把`libstack.so.1.0`所在的目录加入/etc/ld.so.conf中，然后运行ldconfig命令，ldconfig会自动创建一个soname的符号链接
(在`libstack.so.1.0`所在的目录)：

    [root@ share_library]$>cat /etc/ld.so.conf
    include ld.so.conf.d/*.conf
    /lib
    /usr/lib
    /usr/lib64
    /usr/local/lib
    /usr/local/lib64
    [root@ share_library]$>cd /etc/ld.so.conf.d/

    [root@ ld.so.conf.d]$>cat mysql.conf 
        /usr/local/mysql/lib
        /usr/local/lib
    [root@ ld.so.conf.d]$>ll /home/link/share_library/
    total 60
    ...
    -rwxr-xr-x 1 root root 10192 Mar 23 15:59 libstack.so.1.0
    ...
   
    [root@ ld.so.conf.d]$>echo "/home/link/share_library/" > sujianhui.conf
   
    [root@ ld.so.conf.d]$>sudo ldconfig
    [root@ ld.so.conf.d]$>ll
    total 24
    -rw-r--r--  1 root root 24 Jul  8  2019 freetype.conf
    -r--r--r--  1 root root 63 Sep 13  2017 kernel-3.10.0-693.2.2.el7.x86_64.conf
    -r--r--r--. 1 root root 63 Aug 23  2017 kernel-3.10.0-693.el7.x86_64.conf
    -rw-r--r--  1 root root 17 Aug  8  2019 mariadb-x86_64.conf
    -rw-r--r--  1 root root 44 Jul  8  2019 mysql.conf
    -rw-r--r--  1 root root 25 Mar 23 16:10 sujianhui.conf
    
    [root@ ld.so.conf.d]$>find / -name libstack.so.1
    /home/link/share_library/libstack.so.1
    [root@ ld.so.conf.d]$>ll /home/link/share_library/
    total 60
    ... // 在real name 所在目录创建了soname链接
    lrwxrwxrwx 1 root root    15 Mar 23 16:11 libstack.so.1 -> libstack.so.1.0
    -rwxr-xr-x 1 root root 10192 Mar 23 15:59 libstack.so.1.0
    ...
    
那我们要这个soname有什么用呢?这在版本升级以及新旧版本共存场景中非常实用,比如我们修复了一些bug,但是没有更改接口,虽然real name变了,但是soname没有改变
依赖于这个库的应用依然可以继续实用该库函数.

#### linker name

链接名字就很正规了,不要后面哪些版本号

    [root@ share_library]$>gcc main.c -L. -lstack -Istack -o mian
    /usr/bin/ld: cannot find -lstack
    collect2: error: ld returned 1 exit status
    
`-lstack`提示编译链接时将main.c与libstack.so链接在一起,但是在目前已知的库函数目录里,只有`libstack.so.1.0`,`libstack.so.1`,所以我们需要手动创建一个linker name
供我们编译时使用

    [root@ share_library]$>ln -s libstack.so.1.0 libstack.so
    [root@ share_library]$>gcc main.c -L. -lstack -Istack -o mian
    
这样就不会报`cannot find error`         
    
### 动态库的优点

- 节省空间
- 软件升级方便 不必重新编译软件        