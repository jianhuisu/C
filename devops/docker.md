## docker

### mysql

docker pull mysql:8.0
docker run --name mysql8.0 -e MYSQL_ROOT_PASSWORD=123456 -p 3306:3306 -d mysql:8.0
docker exec -it mysql8.x bash

    root@74f6b6a3fb98:/# mysql -uroot -p
    ...
    mysql> CREATE USER 'sujianhui'@'%' IDENTIFIED BY 'xdebug_XDEBUG_5566';
    Query OK, 0 rows affected (0.01 sec)
    
    mysql> GRANT ALL ON *.* TO 'sujianhui'@'%';
    Query OK, 0 rows affected (0.01 sec)
    
    mysql> ALTER USER 'sujianhui'@'%' IDENTIFIED WITH mysql_native_password BY 'xdebug_XDEBUG_5566';
    Query OK, 0 rows affected (0.01 sec)
    
    mysql> flush privileges;
    Query OK, 0 rows affected (0.01 sec)
    
    
    
### redis

docker run --name redis -p 6379:6379 -d redis:latest

### docker-machine

    base=https://github.com/docker/machine/releases/download/v0.16.0 &&
      curl -L $base/docker-machine-$(uname -s)-$(uname -m) >/tmp/docker-machine &&
      sudo mv /tmp/docker-machine /usr/local/bin/docker-machine &&
      chmod +x /usr/local/bin/docker-machine    