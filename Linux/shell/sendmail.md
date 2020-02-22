## 配置阿里云ECS自动化监控发送邮件

### 背景知识简介

用于收发Mail的程序一般统称为邮件用户代理MUA。将来自MUA的信件转发给指定的用户的程序一般被称之为因特网邮件传送代理MTA。

 - 邮件用户代理  MUA(Mail User Agent)
 - 邮件传送代理  MTA(Mail Transport Agent)
 - 邮件分发代理  MDA(Mail Deliver Agent)
    
`mail`,`mailx`都是收发邮件用的,类似浏览器的作用,叫做`Mail User Agent`.
`qmail`,`sendmail`,`postfix`属于邮件服务器,类似`apache`,`nginx`的角色，可以充当`Mail Transport Agent`

发送流程:

    MUA - MTA - MTA - MUA 

正常情况下,使用`mail -s "title" xxxx@qq.com`会调用本地的 MUA 然后将邮件发送到本地的 MTA(也就是邮件服务器软件 sendmail 、postfix)
然后邮件由MTA发送到目的地的MTA,因为使用的是本地的MTA,可能你自己的邮件域名知名度不高,会经常会被对方打入垃圾箱,而且维护邮件服务器也是一笔开销
所以,有时候可以选择以通过修改配置文件使用外部的MTA收发邮件(当然,选择第三方服务多少会有一些发送频率限制)。
            
#### 问题 

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
    
#### 注意事项

#### 参考资料

感谢 https://blog.csdn.net/yiluohan0307/article/details/80514319        