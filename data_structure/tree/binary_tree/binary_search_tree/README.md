二叉搜索树实现思路

    二分查找 依赖于一个有序序列
    比如从小到大  1 2 3 4 5 6 ...  90 91 或者 91 90 ... 3 2 1

    如果在一个 无序的集合中查找指定值,常规思路是 遍历查找

    在一个长度为N的集合中查找指定值i

    function seqSearch ($setLength,$searchValue){

        for($i = 1;$i<= $setLength;$i++){
            if($i === $searchValue){
                break;
            }
        }
    }


    最好时间复杂度  $searchValue = $setLength     O(1)
    最坏时间复杂度  $searchValue > $setLength     O(n)
                1 < $searchValue < $setLength   O(x)  不确定
    平均情况复杂度                                O(n)

    推导过程 https://www.cnblogs.com/jonins/p/9956752.html#autoid-4-0-0

    平均情况复杂度计算公式
        所有情况下代码执行的次数累加和 / 所有情况数  =
        （大O表示法，会省略系数、低阶、常量，所以平均情况时间复杂度是O(n)。）

        n^2 + 3n
        -------------  => n
         2n + 2

    如果是在长度为N的有序序列中查找一个数值 采用二分查找 则平均时间复杂度 O(log2n)

     1 2 3 4 5
           4 5


     所以如果可以构建一个有序的序列，然后从该序列中进行查找就可以极大的提升性能

操作
ADT

-------------------

   物理存储结构
       链式存储
-------------------

    typedef struct Node{

        struct DT data_item;
        dNode * left;
        dNode * right;

    } dNode

    typedef struct DT{
        char name[50];
        float price;
    } dDT ;

    typedef struct BSTree{
        dNode * root;
    }

-------------------------------
    二叉树的初始化
    插入结点
    删除结点
    遍历结点
    清空树

