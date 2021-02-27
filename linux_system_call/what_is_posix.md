# 什么是posix标准

POSIX（Portable Operating System Interface）是由IEEE制定的标准,致力于统一各种UNIX系统的接口，促进各种UNIX系统向互相兼容的发向发展。

我们常说的CPU架构不同,其实是指CPU的指令集不同.那么相对应的汇编指令就会不同.操作系统在编写时,遵循POSIX标准.对上层提供统一标准的接口.
比如说windows开放了socket_create()系统API,那么linux也要提供相同签名的socket_create()API.我们的鲲鹏系统也要遵循契约按POSIX标准提供该接口.
将指令集的差异消灭在操作系统层面.为操作系统之上的各个应用的良好移植提供可能,降低移植成本.求同存异，欣欣向荣.