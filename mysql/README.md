
为什么复合索引比单列索引效率更高

由于Contact表存在多个（单列）索引，造成Delete ，update ，insert操作时需要花费大量的时间删除索引和重建索引。
通过把多个（单列）索引合并成一个（多列）索引后，测试得出Delete ，update ，insert操作时需要花费的时间大大缩短。

问你会不会这个东西 ：
    回答 没接触过 ,而不是不会