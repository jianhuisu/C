## STL strand template library 或者也可以称为容器. 

一般来说，STL容器分两种，

 - 序列式容器 `vector`,`list`,`deque`,`stack`,`queue`,`heap`
 - 关联式容器 `set(集合)`,`map(映射表)`|`hash_set(集合)`,`hash_map(映射表)`
 
关联式容器主要分为`set`(集合)和`map`(映射表)两大类.以及这两大类的衍生体`multiset`(多键集合)和`multimap`(多键映射表).
根据上述容器的底层实现数据结的不同.又可以细分为以下两种具体实现.

底层数据结构使用`RB-tree`实现.

 - `set`(散列集合)
 - `map`(散列映射表)
 - `multiset`(散列多键集合)
 - `multimap`(散列多键映射表)

底层数据结构使用`hashtable`(散列表)实现

 - `hash_set`(散列集合)
 - `hash_map`(散列映射表)
 - `hash_multiset`(散列多键集合)
 - `hash_multimap`(散列多键映射表)

敲黑板,画重点:
 
 - `set`,`map`,`multiset`,`multimap`的底层实现为`RB-tree`.
 - `hash_set`,`hash_map`,`hash_multiset`,`hash_multimap`底层实现为`hashtable`.

就像子类继承父类一样,`set/map`容器具有自动排序特性.而`hash_set/hash_map`没有自动排序特性.

所谓关联式容器，类似关联式数据库，每笔数据或每个元素都有一个`键值(key)`和一个`实值(value)`，即所谓的`Key-Value`(`键-值对`).
当元素被插入到关联式容器中时，容器内部结构(`RB-tree`|`hashtable)便依照其键值大小，依据某种特定规则将这个元素存储于合适的位置.

#### `set/map` 与 `hash_set/hash_map` 的区别 

##### `set`,`map`,`multiset`,`multimap` 之间的细小区别

`set`同`map`一样，所有元素都会根据元素的键值自动被排序，因为`set/map`两者的所有各种操作，都会转化为底层中`RB-tree`的相关操作行为.
`set`的元素不像`map`那样可以同时拥有`实值(value)`和`键值(key)`，`set`元素的键值就是实值，实值就是键值.
而map的所有元素都是pair，同时拥有`实值(value)`和`键值(key)`，`pair`的第一个元素被视为`键值`，第二个元素被视为`实值`。
值得注意的是，两者都不允许两个元素有相同的键值。至于`multiset/multimap`，他们的特性及用法和`set/map`完全相同，唯一的差别就在于它们允许键值重复.
即所有的插入操作基于`RB-tree`的`insert_equal()`而非`insert_unique()`.

##### `hash_set`,`hash_map`,`hash_multiset`,`hash_multimap`之间的细小区别

`hash_set/hash_map`，两者的一切操作都是基于`hashtable`之上.
`hash_set`同`set`一样，尽管它也拥有实值,键值，但它的实值就是键值，键值就是实值.
而`hash_map`同`map`一样，每一个元素同时拥有一个`实值(value)`和一个`键值(key)`，所以其使用方式，和上面的map基本相同。
但由于`hash_set/hash_map`都是基于`hashtable`之上，所以不具备自动排序功能。(为什么?因为hashtable没有自动排序功能.heihei)
至于`hash_multiset/hash_multimap`的特性与上面的`multiset/multimap`完全相同，加个前缀multi_无非就是允许键值重复而已

题外话：`hash_set`就像PHP中的索引数组,我们可以根据下标`0,1,2,3...`去获取元素的值.而`hash_map`就像PHP中的关联数组.
我们需要根据键名去获取元素的值.

    ```php
    echo $article_list[0];
    echo $user['name'];
    
我看网上有很多人在比较`hashmap` 跟`hashtable`.不是一个`level`的东西,没什么可比性.要比也是`hashmap` 跟`hashset`.
    
#### RB-tree与Hashtable的区别与选择

 - hashtable hash这是一种压缩映射的函数,根据hash(key)函数计算即可以得出key在`顺序表`中的存储位置.这个顺序表就是`hashtable`,`hashtable`的查找操作复杂度为`O(1)`.
 - 红黑树的查找、插入、删除的时间复杂度最坏为`O(logn)` 

`hashtable`查找速度会比`RB-tree`快，而且查找速度基本和数据量大小无关，属于常数级别,`RB-tree`的查找速度是`log(n)`级别.
注意:虽然`hashtable`的复杂度为`O(1)`,但这并不意味着绝对比`O(log(n))`小，`hashtable`还有`hash`函数,构建,冲突的耗时.

如果只需要判断Map中某个值是否存在某个值之类的操作，当然是`hashtable`实现的要更加高效.
如果是需要将两个Map求并集交集差集等大量比较操作，就是`RB-tree`实现的Map更加高效.
    
#### 参考资料

(我重新排版 摘录了以下,保存到本地是预防哪天作者不高兴删除了,而我又没记住)

版权声明：本文为CSDN博主「v_JULY_v」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/v_july_v/article/details/7382693