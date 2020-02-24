## 配置阿里云ECS自动化监控发送邮件

### 背景知识简介

用于收发Mail的程序一般统称为邮件用户代理MUA。将来自MUA的信件转发给指定的用户的程序一般被称之为因特网邮件传送代理MTA。

 - 邮件用户代理  MUA(Mail User Agent)
 - 邮件传送代理  MTA(Mail Transport Agent)
 - 邮件分发代理  MDA(Mail Deliver Agent)
    
`mail`,`mailx`都是接收,编写,发送邮件用的,类似浏览器的作用,叫做`Mail User Agent`.
`qmail`,`sendmail`,`postfix`属于邮件服务器,类似`apache`,`nginx`的角色，可以充当`Mail Transport Agent`
`pop3` 邮件接收协议
`smtp` 简单邮件发送协议,使用smtp协议不能发送附件,对于一个ie邮件服务器来讲：必须既可以发送邮件同时也可以接收邮件

发送流程:
    
1 使用mail编写邮件.默认情况下发件人为系统当前登陆用户
2 将mail编写好的邮件发送到MTA,这个MTA可以是本地服务,也可以是远程服务.例如：在你同一机器中存在sendmail进程,那么你可以将通过mail编写好的邮件维托给sendmail(本地MTA)服务进行传送.
3 本地MTA根据邮件中收件人的地址,将邮件内容发送到收件人的MTA服务商.
4 收件人的MTA服务商分发邮件到真正的收件人(实质为收件人使用MTA服务上提供的客户端定期收取).
    
    local_app(mail) -> local_app(sendmail) - remote_app(sendmail/postfix/qmail) - remote_receiver
    MUA             ->  MTA                ->  MTA                              -> MUA
    
第2步中同样可以使用远程MTA,比如qq邮箱.我们将步骤1中编写完成的邮件转发到qq而不是本地的sendmail进程。因为很多时候本地MTA并不被别人认可,
经常会被收件人打入垃圾信箱中,所以我们经常委托一些知名的MTA服务商发送邮件。此时,我们的发件人帐号也需要进行变更,使用提前在qq注册好的邮箱帐号,
然后将该帐号密码(一般为授权码)等信息配置在本地(相当于在本地host模拟登陆qq邮箱帐号),然后使用mail编写邮件时,就是以qq帐号作为发件人了.
所以可以这样理解:mail+sendmail的帐号通常是相关联的.另外,并不是说选择第三方MTA就比本地好,选择第三方服务多少都会有一些发送频率限制.有时候还得冲钱(-0-.-0-)
            
#### 阿里云ecs配置smtp代理 

测试环境正常的邮件发送功能,上了阿里云就无法发送。查资料发现：阿里云的《25端口使用服务协议》：

    我/我公司承诺并保证TCP 25端口仅用来连接第三方的SMTP服务器，从第三方的SMTP服务器外发邮件。
    如发现您使用本机IP直接SMTP发送邮件，有权永久性封禁TCP 25端口，并不再提供相关服务。
    
阿里云、腾讯云都封了25端口的出口方向,可以提工单找官方解封,不过很麻烦,可以使用smtp服务商代理收发 

    host : Linux xxxx 3.10.0-693.2.2.el7.x86_64 ... x86_64 x86_64 x86_64 GNU/Linux
    MUA  : mail 
    
`vim /etc/mail.rc`.在配置文件最后添加如下配置信息：
    
    set from=xxxxxx@qq.com
    set smtp=smtps://smtp.qq.com:465
    set smtp-auth-user=xxxxxx@qq.com
    set smtp-auth-password=你的QQ邮箱授权码
    set smtp-auth=login
    #set smtp-use-starttls 这里是不需要配置的，很多地方没说明，配置了反而会验证失败，所以我注释掉；
    set ssl-verify=ignore
    set nss-config-dir=/root/.certs
    
这边的邮箱授权码需要先去QQ邮箱中开启smtp获取
因为需要QQ邮箱的SSL证书，所以还需要手动的获取QQ 邮箱的证书保存到本地指定的目录里以备调用和验证，具体命令如下：

    mkdir -p /root/.certs/
    echo -n | openssl s_client -connect smtp.qq.com:465 | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > ~/.certs/qq.crt
    certutil -A -n "GeoTrust SSL CA" -t "C,," -d ~/.certs -i ~/.certs/qq.crt
    certutil -A -n "GeoTrust Global CA" -t "C,," -d ~/.certs -i ~/.certs/qq.crt
    certutil -L -d /root/.certs
    
为了防止出现前文所说的发送邮件警告提示，还需要进入邮箱 SSL 证书存放目录 /root/.certs 里执行如下命令：

    cd /root/.certs
    certutil -A -n "GeoTrust SSL CA - G3" -t "Pu,Pu,Pu" -d ./ -i qq.crt

返回如下提示即可：

    **Notice: Trust flag u is set automatically if the private key is present.**

可以发送了

    echo "message" | mail -s "title" xxxx@qq.com 或 mail -s title xxxx@qq.com < ~/.bashrc
    
#### 测试环境配置踩坑

centos7默认只安装了mail而没有安装sendmail
    
    rpm -qa | grep sendmail  
    yum -y install sendmail
    systemctl start sendmail

准备工作完成,开始发送
    
    
    [prod70_root@ mail]$>echo "test" | mail -s "hello" root  // success 
    [prod70_root@ mail]$>echo "test" | mail -s "hello" guangsu@xxxx.com  // failed
    
`guangsu@xxxx.com`是一个外网邮箱地址,不用说第一次没由发成功,等了半天收件箱没有/垃圾箱也没有.查看发送队列
    
    [prod70_root@ mail]$>sendmail -bp 
    empty
    
这也没有待发送邮件, 忽然想起mail由发送日志`/var/log/maillog`,去查日志找找思路吧
    
    Connection refused by [127.0.0.1]    

第一想法是25端口被禁止了,无法进行发送。(到后边发现第一反应是错的),所以查看了一下端口监听

    [prod70_root@ mail]$>netstat -ano | head
    Active Internet connections (servers and established)
    Proto Recv-Q Send-Q Local Address           Foreign Address         State       Timer
    tcp        0      0 127.0.0.1:25            0.0.0.0:*               LISTEN      off (0.00/0/0)
    tcp        0      0 0.0.0.0:80              0.0.0.0:*               LISTEN      off (0.00/0/0)
    
25端口处于监听状态,为什么本地可以,其它主机不行呢?用另外一个host连一下这个端口
    
    [guangsujiqiang@su-ct7 C]yum -y install telnet
    [guangsujiqiang@su-ct7 C]telnet 172.16.225.xxx 25   // telnet 采用tcp协议  ping 采用icmp协议
     
请求失败,为什么... 仔细比对后发现`127.0.0.1:25`跟`0.0.0.0:80`这两个源端套接字有点不一样,马不停蹄的bing一下

127.0.0.1 环回测试地址，目的地址为127.0.0.1的包不会被路由器转发.
0.0.0.0 网络地址,0.0.0.0:80表示本机IP地址(比如你的局域网IP为192.168.1.32 那么这个0.0.0.0:80代表同一局域网的主机可以访问192.168.1.32的80端口)，相当于允许其它网络主机访问.

这两种表示法用以对计算机端口进行权限设置

 - listen(0.0.0.0:XX)   这个端口可以被外部网络访问
 - listen(127.0.0.1:XX) 这个端口允许被本机访问

解决方案：
    
/etc/mail/sendmail.cf,文件中默认只开通127.0.0.1的25端口。意思就是你不能通过更改配置文件更改sendmail监听的端口
 
    vim  O DaemonPortOptions=Port=smtp,Addr=127.0.0.1, Name=MTA  修改为 O DaemonPortOptions=Port=smtp,Addr=0.0.0.0, Name=MTA
    systemctl restart sendmail    

这次从外网telnet测试可以通过.OK 再次尝试

    [prod70_root@ mail]$>echo "test" | mail -s "hello" guangsu@xxxx.com  // failed
    
失败

继续看日志

    My unqualified host name (sdev70). unable to qualify my own domain name (sdev70) -- using short name
    
网上说DNS无法找到这个域名,手动在`/etc/hosts`指定一下 `127.0.0.1 sdev70 sdev70.com`,重启sendmail.
再试,仍就无法发送,继续查log
            
    dsn=5.0.0, stat=Service unavailable

无法发送邮件的日志如下(这段贴的别人的 有些敏感信息不方便贴)：

    Jun 26 07:24:23 MyVPS1976 sendmail[31760]: q5PNOMeP031760: from=<www@MyVPS1976>, size=1393, class=0, nrcpts=1, msgid=<101f67a320c3f53ec88cb43d5c74631f@www.centos.bz>, proto=SMTP, daemon=MTA, relay=MyVPS [127.0.0.1]
    Jun 26 07:24:25 MyVPS1976 sendmail[31762]: q5PNOMeP031760: to=<admin@centos.bz>, ctladdr=<www@MyVPS1976> (501/501), delay=00:00:02, xdelay=00:00:02, mailer=esmtp, pri=121393, relay=mxdomain.qq.com. [64.71.138.90], dsn=5.0.0,stat=Service unavailable
    Jun 26 07:24:25 MyVPS1976 sendmail[31762]: q5PNOMeP031760: q5PNOPeP031762: DSN: Service unavailable
    Jun 26 07:24:25 MyVPS1976 sendmail[31762]: q5PNOPeP031762: to=root, delay=00:00:00, xdelay=00:00:00, mailer=local, pri=32578, dsn=2.0.0, stat=Sent
    
根据relay=mxdomain.qq.com. [64.71.138.90], dsn=5.0.0,stat=Service unavailable这一段，我们知道邮件已经发送出去，但由于某种原因邮件被拒绝，于是更换hostname，重启sendmail，解决问题。

更换hostname方法：

    1、编辑/etc/sysconfig/network，更换文件中的hostnmae。
    2、把hostname写入/etc/hosts
    3、执行hostname www.centos.bz立即生效

hostname是Linux系统下的一个内核参数，它保存在/proc/sys/kernel/hostname下，但是它的值是Linux启动时从rc.sysinit读取的。
而/etc/rc.d/rc.sysinit中HOSTNAME的取值来自与/etc/sysconfig/network下的HOSTNAME.

这线上hostname俺也不敢随便改,在本地验证了一下,确实可以。原来没接触过邮件这一块,今天是连蒙带猜整磕磕绊绊.
    
#### 注意事项

    帐号： xxx@exampke.com
    收件服务器 pop3.example.com  port : 995
    发件服务器 smtp.example.com  prot : 25

#### 参考资料

感谢
 
 - https://blog.csdn.net/yiluohan0307/article/details/80514319      
 - https://www.centos.bz/2012/06/dsn-service-unavailable/  