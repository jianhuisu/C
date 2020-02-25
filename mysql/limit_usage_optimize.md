## 覆盖索引

在mysql中limit可以实现快速分页，但是如果数据到了几百万时我们的limit必须优化才能有效的合理的实现分页了，否则可能卡死你的服务器.
当一个表数据有几百万的数据的时候成了问题！

    select * from table order by id asc limit 0,10       快速
    select * from table order by id asc limit 200000,10  较慢

limit10000,20的意思扫描满足条件的10020行，扔掉前面的10000行，返回最后的20行。
如果limit 430000,1 那不得扫描4w多.

两个点：

- limit语句的查询时间与起始记录的位置成正比
- mysql的limit语句对记录不适合直接使用

### 对limit分页问题的性能优化方法

覆盖索引是select的数据列只用从索引中就能够取得,不必读取数据行，换句话说就是select的对象可以被创建了索引的列覆盖.
注意与使用索引区别开,使用索引是指where字句中的字段被创建了索引,但是获取数据的时候要根据索引去数据区域获取select的字段

利用表的覆盖索引来加速分页查询
一般来讲id字段是主键，自然就包含了默认的主键索引。现在让我们看看利用覆盖索引的查询效果如何：

这次我们之间查询最后一页的数据（利用覆盖索引，只包含id列），如下：

    select id from product limit 866613,20  => 0.2秒

相对于查询了所有列的37.44秒，提升了大概100多倍的速度

下面查询所有列,有两种方法:

 - id>= : SELECT * FROM product WHERE ID > =(select id from product order by id asc limit 866613, 1) limit 20  => 0.2s
 - join : SELECT * FROM product a JOIN (select id from product order by id asc  limit 866613, 20) b ON a.ID = b.id  => 0.2s

 使用explain可以监测到,虽然扫描rows增加了,但是整体耗时下降很多

### 联合索引

如果表存在多个单列索引,那么delete,update,insert操作时需要花费大量的时间删除索引和重建索引.
通过把多个单列索引合并成一个多列索引后,delete,update,insert操作时需要花费的时间大大缩短。
如果使用了联合索引,查询时如果使用了联合索引并且可以覆盖查询的字段,那么对查询的性能也会有很大的提升