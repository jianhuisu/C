## 数据结构中的堆

按照堆的特点可以把堆分为大顶堆和小顶堆

 - 大顶堆/小：每个结点的值都大于或等于其左右孩子结点的值
 - 小顶堆：每个结点的值都小于或等于其左右孩子结点的值

（堆的这种特性非常的有用，堆常常被当做优先队列使用，因为可以快速的访问到“最重要”的元素）

#### 堆与二叉树的区别

 - 内存：
 - 结点顺序即树的属性: heap-> 父结点大于子结点，Btree -> LDR ...
 - 适用场景：删除与查找
 
所以:堆并不能取代二叉搜索树

#### 存储结构

原始序列 `[ 10, 5, 9, 1, 2 , 7, 8]`

    堆结构
    
             10 
        5           9
    1       2    7     8
    
    in memory unit :
    index        0    1     2      3     4   
    node_v       10   5     7      1     2          
    tree_level   1    2     2      3     3
    
#### 参考资料

总结的非常好:
 
https://www.jianshu.com/p/6b526aa481b1

https://github.com/raywenderlich/swift-algorithm-club/blob/master/Heap/README.markdown