#!/bin/bash
PORT_C=$(ss -anu |grep -c 123)
PS_C=$(ps -ef |grep ntpd |grep -vc grep)
if [ $PORT_C -eq 0 -o $PS_C -eq 0 ]; then
    echo "内容" | mail -s "主题" dst@example.com
fi


SSL：（Secure Socket Layer，安全套接字层），位于可靠的面向连接的网络层协议和应用层协议之间的一种协议层。SSL通过互相认证、使用数字签名确保完整性、使用加密确保私密性，以实现客户端和服务器之间的安全通讯。该协议由两层组成：SSL记录协议和SSL握手协议。

TLS：(Transport LayerSecurity，传输层安全协议)，用于两个应用程序之间提供保密性和数据完整性。该协议由两层组成：TLS记录协议和TLS握手协议。

SSL是Netscape开发的专门用户保护Web通讯的，目前版本为3.0。最新版本的TLS 1.0是IETF(工程任务组)制定的一种新的协议，它建立在SSL 3.0协议规范之上，是SSL 3.0的后续版本。两者差别极小，可以理解为SSL 3.1，它是写入了RFC的。



    
    


修改/etc/mail.rc
set from=1051034413@qq.com
set smtp=smtp.qq.com
set smtp-auth-user=1051034413@qq.com
set smtp-auth-password=wfdkqttfdquibfcc
set smtp-auth=login
