## 位图法

位图法就是bitmap的缩写，所谓bitmap，就是用每一位来存放某种状态，适用于大规模数据，但数据状态又不是很多的情况。通常是用来判断某个数据存不存在的。

#### 位图法存数据

在`8K`字节的内存空间内，如何存`unsigned short`类型数据？

 - 常规做法：定义一个数组进行存储;`unsigned short`占用`2`字节,那么`8K`字节空间最多容纳`4K`个`unsigned short`数据,即`unsigned shortarrNormal[4096]`.
 - 利用位图法：定义一个数组：`unsigned chararrBit[8192]`;这样做，能存`8K * 8 = 64K`个`unsigned short`数据.
