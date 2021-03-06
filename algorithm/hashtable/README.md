## 哈希表

#### 哈希表的定义

根据设定的哈希函数`H(key)`和设定的处理冲突方法将一组关键字`映像`到一个有限的连续的地址区间上,并以关键字在地址区间中的像作为
记录在表中的存储位置,这种表称为哈希表,这一过程称为哈希造表或者散列,所得的存储位置称为哈希地址或散列地址.

理想情况下.hash表可以使我们不用经过比较,一次存取便能查到所查记录.即hash表操作的时间复杂度是`O(1)`.

`skiplist`和各种平衡树（如AVL、红黑树等）的元素都是有序排列的，而哈希表不是有序的。
**所以，在哈希表上只能做单个key的查找，不适宜做范围查找**.而`skiplist`和`平衡树`可以进行范围查找.

#### 哈希函数的构造方法

 - 直接定址法  `H(key) = a * key + b` . `h(key)`是关于`key`的一次线性函数. 
 - 数字分析法     
 - 平方取中法  取关键字平方后的中间几位为hash地址.
 - 折叠法     切割,求叠加和
 - 除模取余法  `x/9`,取余数
 - 随机数法

#### 哈希冲突

对不同的key进行hash计算可能得到同一个hash地址，即`key1 != key2`但是`f(key1) == f(key2)`.这种现象称为冲突.
**我们要知道,冲突只能尽量减少,而不能完全避免.**

 - 开放定址法  线性探测再散列/二次探测再散列/随机探测再散列
 - 再哈希法
 - 拉链法 (线性链表/红黑树)  拉链法不容易产生二次聚集,在实际中最常用.
 - 公共溢出区

#### 常见面试题

7、HashMap的底层实现的数据结构是什么？（没有答很多，等他来问。哈哈）
答：Java7中的HashMap(数组+链表)，Java8中的HashMap(数组+链表+红黑树).php7中是数组是hashtable(C数组+线性链表)

8、什么时候转化成红黑树？为什么要这样做？（答的比较完整）
答：当链表的元素大于等于8时就会转换为红黑树。当链表的元素大于等于8时，查询效率降低了，这个时候就要变成红黑树了
（但也不一定就要转化成红黑树，在源码中其实是可以看到的，还有一个判断的条件就是数组的容量小于默认值64，这时就会扩容）。
当红黑树只有六个节点了，查询的效率还算可以，但是插入效率提高了，这时就要变成链表了。

9、HashMap什么时候进行扩容？
答：当hashmap中的元素个数超过数组大小*loadFactor时，就会进行数组扩容，
（开始答的是，当数组的元素超过了初始值的时候就会扩容，面试官提醒了负载因子，就改成以下的答案了）

10、HashCode有什么作用（只想到了在HashMap中是作为数组的下标。）
答：（其他方面没思路）

**为什么提倡数组大小是2的幂次方**？
答： 因为只有大小是 2 的幂次方时，才能使`hash 值 % n(数组大小) == (n-1) & hash `公式成立,使Hash值散列、均匀分布呢。如果不是2的次幂.
那么HaspTable数组的利用率会降低,碰撞概率上升导致链表过深.

#### 哈希表的扩容




1、按照传统先自我介绍一下吧。

答：您好，我是。。。。。。（声音完全没有第一次参加面试的颤抖与紧张）

2、说一下你的项目吧。（卧槽，上来就聊项目）

答：我校第一款校园门户微信小程序《指尖移通》。涵盖了全校师生的基本需求，例如查课表、查成绩、告白墙、电表查询等。。。（吹了一下，哈哈）

3、在开发中你所扮演的角色？以及项目是怎么设计的？（最喜欢这样的主观题了）

答：后端开发人员，编写接口。项目采用前后端完全分离、分模块开发的形式，每个功能对应一个模块。整个项目由设计、前端、后端 三部分完成。

4、接口有没有做什么验证？（没想起来其他的验证。。。。我的）

答：根据学生的学号或老师的工号生成对应的sfm和jym，在请求接口时通过sfm和jym来获取身份标识。

5、gc算法了解吗 ？有哪些？（答得比较完整，毕竟准备了很多次了，感觉背都背会了）
答：
标记-清除算法：该算法分为标记和清除两个阶段。标记就是把所有活动对象都做上标记的阶段；清除就是将没有做上标记的对象进行回收的阶段。

复制算法：就是将内存空间按容量分成两块。当这一块内存用完的时候，就将还存活着的对象复制到另外一块上面，然后把已经使用过的这一块一次清理掉。这样使得每次都是对半块内存进行内存回收。内存分配时就不用考虑内存碎片等复杂情况，只要移动堆顶的指针，按顺序分配内存即可，实现简单，运行高效。

标记-整理算法：标记-压缩算法适合用于存活对象较多的场合，如老年代。它在标记-清除算法的基础上做了一些优化。和标记-清除算法一样，标记-压缩算法也首先需要从根节点开始，对所有可达对象做一次标记；但之后，它并不简单的清理未标记的对象，而是将所有的存活对象压缩到内存的一端；之后，清理边界外所有的空间。

分代收集算法：这种算法，根据对象的存活周期的不同将内存划分成几块，新生代和老年代，这样就可以根据各个年代的特点采用最适当的收集算法。可以用抓重点的思路来理解这个算法。新生代对象朝生夕死,对象数量多，只要重点扫描这个区域，那么就可以大大提高垃圾收集的效率。另外老年代对象存储久，无需经常扫描老年代，避免扫描导致的开销。

6、说一下永久代是什么？(卧槽，我之前研究过的，全忘了。。。。。。只记得好像是被取消了)

答：hotspot的方法区存放在永久代中，因此方法区被人们称为永久代。永久代的垃圾回收主要包括类型的卸载和废弃常量池的回收。当没有对象引用一个常量的时候，该常量即可以被回收。而类型的卸载更加复杂。必须满足一下三点，该类型的所有实例都被回收了，该类型的ClassLoader被回收了，该类型对应的java.lang.Class没有在任何地方被引用，在任何地方都无法通过反射来实例化一个对象


————————————————
版权声明：本文为CSDN博主「我_是_太_阳」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_43229543/article/details/105770725
 