# linux中ab命令安装

    yum -y install httpd-tools 
    ab -v 查看ab版本 
    ab –help

    ab -n1000 -c 10 http://www.91cnm.com/
    

    [sujianhui@localhost interviews]$>ab -c 10 -n100 https://www.baidu.com
    ab: invalid URL

需在你压测的域回名后面加上path部分
    
    [sujianhui@localhost interviews]$>ab -c 10 -n100 https://www.baidu.com/
    success