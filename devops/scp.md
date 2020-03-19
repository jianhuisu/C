## scp真的是超好用

利用scp传输文件,命令模式：`scp A move 到 B`

###从服务器下载文件
 
    A = root@host_ip:/home/www/index.php
    B = /home/www/index.php
    scp A B
    scp root@192.168.0.101:/home/www/index.php /home/www/index.php 

将`192.168.0.101`主机上/home/www/index.php文件下载到本地`/home/www/index.php`(**it will be overwrited when specify file exists**)

针对于目录需要使用`-r`选项
    
    scp -r root@39.106.58.35:/home/www/jianhuisu.github.io/source/_posts /home/guangsujiqiang/www/

把`source/_posts`目录的内容下载到`/home/guangsujiqiang/www/`目录下,在该目录下生成一个`_posts`文件夹

    [guangsujiqiang@su-ct7 www]$>scp -r root@39.106.58.35:/home/www/jianhuisu.github.io/source/_posts /home/guangsujiqiang/www/aaa
    // !!! 目标地址中文件夹后是否跟随 / ,将影响download内容的存储位置 ,如果跟随 / ,则代表将_posts文件夹copy到 aaa目录下,否则就是将_posts文件夹重命名为aaa
    [guangsujiqiang@su-ct7 www]$>tree aaa        
    aaa
    ├── 2017-07-12.md
    ...

把`source/_posts`目录中内容下载到`/home/guangsujiqiang/www/aaa`目录下,如果`aaa`目录不存在，自动创建

    scp -r root@39.106.58.35:/home/www/jianhuisu.github.io/source/_posts /home/guangsujiqiang/www/bbb/
    <=> scp -r root@39.106.58.35:/home/www/jianhuisu.github.io/source/_posts/ /home/guangsujiqiang/www/bbb/
    // _posts 后是否跟随 / 都表示同样的意思 表示_posts文件夹
    [guangsujiqiang@su-ct7 www]$>tree bbb
        bbb
        └── _posts
            ├── 2017-07-12.md
            ...
    
把`source/_posts`目录本地`copy`到`/home/guangsujiqiang/www/bbb`目录下

###将文件上传到服务器 

    A = /home/www/index.php
    B = root@host_ip:/home/www/index.php
    scp A B
    scp /home/www/index.php root@host_ip:/home/www/index.php 
     

将本地`/home/www/index.php`文件上传到`192.168.0.101`主机上`/home/www/index.php`(**it will be overwrited when specify file exists**)

文件夹同理
    
    scp -P 22 -r /home/www/ root@host_ip:/home/www
 
###参考资料

http://blog.csdn.net/ssihc0/article/details/7544573 