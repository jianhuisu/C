## mysql8.0

### install 

    wget https://dev.mysql.com/get/mysql80-community-release-el7-1.noarch.rpm
    yum localinstall mysql80-community-release-el7-1.noarch.rpm
    yum repolist enabled | grep "mysql.*-community.*"
    vim /etc/yum.repos.d/mysql-community.repo   // set default version
    yum install mysql-community-server
    systemctl start mysqld
    systemctl enable mysqld
    systemctl daemon-reload
    
### user set 

#### find root temporary password

    [guangsu@xuwei bin]$ sudo grep 'temporary password' /var/log/mysqld.log
    [guangsu@xuwei bin]$ mysql -uroot -p
    Enter password: 

    Welcome to the MySQL monitor.  Commands end with ; or \g.
    Your MySQL connection id is 8
    Server version: 8.0.19
    ...
    
change root password , actually `'root'@'localhost'` and `'root'@'%'` is two user 
 
    mysql> ALTER USER 'root'@'localhost' IDENTIFIED BY 'Debugger123@xuwei';
    Query OK, 0 rows affected (0.01 sec)
    // or : set password for 'root'@'localhost'=password('TestBicon@123');     but not recommand

grant root can login from every where 

    mysql> GRANT ALL ON *.* TO 'root'@'%';

add another mysql user  
        
    mysql> use mysql;
    Reading table information for completion of table and column names
    You can turn off this feature to get a quicker startup with -A
    
    Database changed
    mysql> create user 'guangsu'@'%' identified by '4466xdebug_User';
    Query OK, 0 rows affected (0.02 sec)
    
    mysql> grant all privileges on *.* to guangsu;
    Query OK, 0 rows affected (0.02 sec)
    
    mysql> show grants for guangsu\G
    *************************** 1. row ***************************
    Grants for guangsu@%: GRANT SELECT, INSERT, UPDATE, DELETE, CREATE, DROP,  ON *.* TO `guangsu`@`%`
    *************************** 2. row ***************************
    Grants for guangsu@%: GRANT ...,XA_RECOVER_ADMIN ON *.* TO `guangsu`@`%`
    2 rows in set (0.00 sec)
    
    mysql> flush privileges;
    Query OK, 0 rows affected (0.01 sec)

#### use utf8mb4

    mysql> SHOW VARIABLES WHERE Variable_name LIKE 'character_set_%' OR Variable_name LIKE 'collation%';
    +--------------------------+--------------------------------+
    | Variable_name            | Value                          |
    +--------------------------+--------------------------------+
    | character_set_client     | utf8mb4                        |
    | character_set_connection | utf8mb4                        |
    | character_set_database   | utf8mb4                        |
    | character_set_filesystem | binary                         |
    | character_set_results    | utf8mb4                        |
    | character_set_server     | utf8mb4                        |
    | character_set_system     | utf8                           |
    | character_sets_dir       | /usr/share/mysql-8.0/charsets/ |
    | collation_connection     | utf8mb4_0900_ai_ci             |
    | collation_database       | utf8mb4_0900_ai_ci             |
    | collation_server         | utf8mb4_0900_ai_ci             |
    +--------------------------+--------------------------------+
    11 rows in set (0.00 sec)

not need modify

#### uninstall 

    yum remove mysql-community-server
    
find use cmd like `rpm -qa | grep mysql` and use `yum remove name` to remove , until all remove (`rpm -qa | grep -i mysql` => `rpm -e name`) 

delete data files 

    rm -rf /var/lib/mysql
    rm /etc/my.cnf
    rm -rf /usr/share/mysql-8.0 

#### copy from 

https://blog.csdn.net/qq_38591756/article/details/82958333