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

void insert_sort(int arr[],int length)
{
    // 目的：将元素序列按照正序排序
    // 将长度为N的原始序列划分两个左右两个序列,left序列含有一个元素,right序列含有 n - 1 个元素,
    // 逐次把right序列头部第一个元素x 与 left序列中的每个元素两个比较,因为left序列是我们从1生成的有序序列,所以只要x在left中从右向左比较过程中(顺便移动) 遇到第一个小于它的元素,那么x就应该在此插入.
    // 直接插入排序 与 冒泡排序 相比，复杂度基本相同,但是当原始序列部分有序时 ，插入排序要优于 冒泡排序.
    int j;
    int i;
    int temp;

    // i 指针定义 左右序列的分界点
    for(i = 1 ;i < length;i++){

        // j 定义left序列的末尾指针，并从后向前进行比较 ，插入
        // ！！这里可以用 while 来代替
        for(j = i; j > 0;j--){

            // 如果前一个元素 大于待插入元素 ,则需要继续向前比较 ，直至遇到第一个不大于x的元素.
            if( arr[j - 1] > arr[j] ){
                temp = arr[j - 1];
                arr[j-1] = arr[j];
                arr[j]  = temp;
            }
        }
    }

}

int main(void)
{
    show(wait_sort,MAX_SIZE);
    insert_sort(wait_sort,MAX_SIZE);
    show(wait_sort,MAX_SIZE);
    return 0;
}

// 直接插入排序的 时间复杂度 最优 O(n) 最坏 O(n^2) 平均 O(n^2) ，辅助空间O(1) 是稳定排序 适用场景： 当基础序列大部分有序时 选择此种排序方式