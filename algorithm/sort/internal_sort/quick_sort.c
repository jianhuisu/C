// 插入排序
// 冒泡排序
// 归并排序


#include <stdio.h>
#define MAX_SIZE 10
int wait_sort[MAX_SIZE] = {11,15,20,13,17,65,27,49,99,18};

void show(int * s,int length)
{
    int i ;
    for(i=0;i<length;i++){
        printf(" %d ",s[i]);
    }

    printf("\n");
}

/*
    快排算法分析
    首先 快排的核心思想是 分治法
    一个序列划分为 两个序列 ，两个序列分为四个 ... 直到序列只含有一个元素.(即 low high 相遇)
    实现时需要借助辅助空间 不是原地排序
    然后在每个序列中 借助三个指针，同时从前向后 ，从后向前 遍历,（有点类似于土木工程中 竖井开凿法）
    每趟遍历
    一般选择 数据记录的第一个元素作为基准. 基准左边是 左序列 基准右边是右序列



    动图：看动图 明白的快 哈哈哈
    for 需要配置 break 使用时 需要用while来代替
    其余情况使用 for

 */


//快速排序
void quick_sort(int s[],int low , int high)
{
    if(low < high){

        int temp = s[low];
        int j,i;
        j = high;
        i = low;

        // 如果找到一个比基准值小的元素 那么终止循环,向下运行.否则 继续向前遍历.
        while(i < j && s[j] >= temp)
        {
            j--;
        }

        if(i < j){
            s[i] = s[j];
            i++;
        }

        // 如果找到一个比基准值大的元素 那么终止循环,向下运行.否则 继续向后遍历.
        while(i < j && s[i] < temp)
        {
            i++;
        }

        if(i < j){
            s[j] = s[i];
            j--;
        }

        //
        s[i] = temp;
        quick_sort(s,low,i - 1); // 此步骤 略过中间基准 元素
        quick_sort(s,i + 1,high);

    }
}

int main(void)
{
    quick_sort(wait_sort,0,9);
    show(wait_sort,MAX_SIZE);
    return 0;
}

// 快速排序使用的空间是O(1)的，也就是个常数级；而真正消耗空间的就是递归调用了，
//　　最优的情况下空间复杂度为:O(log2n)；每一次都平分数组的情况
//　　最差的情况下空间复杂度为：O( n )；退化为冒泡排序的情况

// 快排的时间复杂度分析
// 时间复杂度 平均 O(nlogn) 最坏 O(n^2)  初始序列 局部有序或者整体有序时 退化为冒泡排序 两两比较