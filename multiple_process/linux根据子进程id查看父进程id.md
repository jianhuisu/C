# linux根据子进程id查看父进程id

在Linux下，可以有两种比较方便的方法：

## 1. `pstree`

通过查看系统的进程树来查看某个进程的父进程.例如查看docker的进程组关系.
	
	[sujianhui@dev529 C]$>pstree
	systemd─┬─ModemManager───2*[{ModemManager}]
		├─NetworkManager─┬─dhclient
		│                └─2*[{NetworkManager}]
		├─2*[abrt-watch-log]
		├─abrtd
		├─accounts-daemon───2*[{accounts-daemon}]
		├─alsactl
		├─at-spi-bus-laun─┬─dbus-daemon
		│                 └─3*[{at-spi-bus-laun}]
		├─at-spi2-registr───2*[{at-spi2-registr}]
		├─atd
		├─auditd─┬─audispd─┬─sedispatch
		│        │         └─{audispd}
		│        └─{auditd}
		├─avahi-daemon───avahi-daemon
		├─boltd───2*[{boltd}]
		├─chronyd
		├─colord───2*[{colord}]
		├─crond
		├─cupsd
		├─2*[dbus-daemon]
		├─dbus-launch
		├─dconf-service───2*[{dconf-service}]
		├─dnsmasq───dnsmasq
		├─dockerd-current─┬─docker-containe───12*[{docker-containe}]  // -----> 在这里
		│                 └─13*[{dockerd-current}]
		├─evolution-addre─┬─evolution-addre───5*[{evolution-addre}]
		│                 └─4*[{evolution-addre}]
		├─evolution-calen─┬─evolution-calen───8*[{evolution-calen}]
		│                 └─4*[{evolution-calen}]
		├─evolution-sourc───3*[{evolution-sourc}]
		├─firewalld───{firewalld}
		├─fwupd───4*[{fwupd}]

	...

## `ps -ef | grep <进程名>`

使用

	ps -ef | grep <子进程名>

在显示的输出中，第三列就是该进程的父进程PID，然后可以再使用`ps -p`命令来查看父进程的名称.

	ps -ef |grep <父进程PID>

以查看docker进程关系为例子

	[sujianhui@dev529 C]$>ps -ef | grep docker
	root      6319     1  0 22:35 ?        00:00:01 /usr/bin/dockerd-current ...
	root      6327  6319  0 22:35 ?        00:00:00 /usr/bin/docker-containerd-current -l unix:///var/run/docker/libcontainerd/docker-containerd.sock ...
	sujianhui  7249  4627  0 22:48 pts/0    00:00:00 grep --color=auto docker

所以:

	[sujianhui@dev529 C]$>pstree -p 6319
	dockerd-current(6319)─┬─docker-containe(6327)─┬─{docker-containe}(6328)
		              │                       ├─{docker-containe}(6329)
		              │                       ├─{docker-containe}(6330)
		              │                       ├─{docker-containe}(6331)
		              │                       ├─{docker-containe}(6332)
		              │                       ├─{docker-containe}(6333)
		              │                       ├─{docker-containe}(6334)
		              │                       ├─{docker-containe}(6335)
		              │                       ├─{docker-containe}(6336)
		              │                       ├─{docker-containe}(6341)
		              │                       ├─{docker-containe}(6342)
		              │                       └─{docker-containe}(6773)
		              ├─{dockerd-current}(6320)
		              ├─{dockerd-current}(6321)
		              ├─{dockerd-current}(6322)
		              ├─{dockerd-current}(6323)
		              ├─{dockerd-current}(6324)
		              ├─{dockerd-current}(6325)
		              ├─{dockerd-current}(6326)
		              ├─{dockerd-current}(6337)
		              ├─{dockerd-current}(6338)
		              ├─{dockerd-current}(6339)
		              ├─{dockerd-current}(6340)
		              ├─{dockerd-current}(6370)
		              └─{dockerd-current}(6371)



子集为线程.

	[sujianhui@dev529 C]$>ps -T -p 6319
	  PID  SPID TTY          TIME CMD
	 6319  6319 ?        00:00:00 dockerd-current
	 6319  6320 ?        00:00:00 dockerd-current
	 6319  6321 ?        00:00:00 dockerd-current
	 6319  6322 ?        00:00:00 dockerd-current
	 6319  6323 ?        00:00:00 dockerd-current
	 6319  6324 ?        00:00:00 dockerd-current
	 6319  6325 ?        00:00:00 dockerd-current
	 6319  6326 ?        00:00:00 dockerd-current
	 6319  6337 ?        00:00:00 dockerd-current
	 6319  6338 ?        00:00:00 dockerd-current
	 6319  6339 ?        00:00:00 dockerd-current
	 6319  6340 ?        00:00:00 dockerd-current
	 6319  6370 ?        00:00:00 dockerd-current
	 6319  6371 ?        00:00:00 dockerd-current

`SPID`列值为线程ID.


## 总结 

Linux操作系统下,所有进程的父进程为`systemd`，`pid`为`1`.
