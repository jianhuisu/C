## mysql删除数据后释放磁盘空间

    drop table table_name 

立刻释放磁盘空间 ，不管是 Innodb和MyISAM

    truncate table table_name
    
立刻释放磁盘空间 ，不管是 Innodb和MyISAM

    delete from table_name

删除表的全部数据，对于MyISAM 会立刻释放磁盘空间,而InnoDB不会释放磁盘空间; 

    delete from table_name where xx 

带条件的删除, 不管是innodb还是MyISAM都不会释放磁盘空间

delete操作后使用`optimize table table_name`释放磁盘空间，优化表期间会锁定表，所以要在空闲时段执行.
有人说:测试十几个G数据的表执行optimize大概20多分钟

注：delete删除数据的时候，mysql并没有把数据文件删除，而是将数据文件的标识位删除，没有整理文件，因此不会彻底释放空间。
被删除的数据将会被保存在一个链接清单中，当有新数据写入的时候，mysql会利用这些已删除的空间再写入。

`OPTIMIZE TABLE tableName`命令优化表，该命令会重新利用未使用的空间，并整理数据文件的碎片；
该命令将会整理表数据和相关的索引数据的物理存储空间，用来减少占用的磁盘空间，并提高访问表时候的IO性能；
但是具体对表产生的影响是依赖于表使用的存储引擎的。该命令对视图无效。

使用`optimize table table_name`出现`Table does not support optimize, doing recreate + analyze instead`的解决办法：

innodb的数据库不支持optimize，可以用 ALTER TABLE table.name ENGINE='InnoDB';
对旧表以复制的方式新建一个新表，然后删除旧表。操作前最好备份表。
重新启动mysql ，在启动的时候指定–skip-new或者–safe-mode选项来支持optimize功能 再执行`optimize table table_name`
(自己实测了一下,如果一个表的engine是innodb,使用`delete where`删除数据后可以使用`optimize`优化,上面说的应该是指数据库的引擎为innodb,这里没有测试)

另外可以通过对一些表进行压缩的方式来释放空间

#### 参考资料

原文链接：https://blog.csdn.net/hyfstyle/article/details/89141208