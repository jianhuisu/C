//
// 将两个(或者N个)有序数列合并成一个有序数列，我们称之为“归并”。
// 问题： 如果 两个序列中的值是相互交叉的，如何合并？ 例如 {7 11 15} {9,13,20} 二者如何合并？

//具体的实现有三个步骤：
//
//分解 -- 将当前区间一分为二，即求分裂点 mid = (low + high)/2;
//求解 -- 递归地对两个子区间a[low...mid] 和 a[mid+1...high]进行归并排序。递归的终结条件是子区间长度为1。
//合并 -- 将已排序的两个子区间a[low...mid]和 a[mid+1...high]归并为一个有序的区间a[low...high]。
//


// 采用 递归 实现归并排序
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

// 合并操作 归并排序的精髓所在
void merge(int start,int mid,int end)
{

    int n1 = mid - start + 1;
    int n2 = end - mid;
    int left[n1];
    int right[n2];
    int i,j,p;

    // 这里初始化为0即可 这个代表offset
    i = 0;
    j = 0;

    // start --- mid
    while(i < n1 ){
        left[i] = wait_sort[start + i];
        i++;
    }

    // mid + 1 --- end
    while(j < n2 ){
        right[j] = wait_sort[mid + 1 +j];
        j++;
    }

    // 设置有序序列的指针
    i = 0;
    p = start;
    j = 0;

    // 逐个比较 left 与 right 中元素, 取较小者存入缓冲序列,并将该序列指针后移一位，缓冲区序列指针后移一位. 直到其中一个序列被完全复制.
    // 最重要的部分 就是双指针 一起移动

    // 只要两个序列同时不为空，那么就需要进行比较
    while(i < n1 && j < n2){
        if(left[i] < right[j]){
            wait_sort[p] = left[i];
            i++;
            p++;
        } else {
            wait_sort[p] = right[j];
            j++;
            p++;
        }
    }

    // 如果两个序列比较完成后,left有序序列不为空,则将 剩余部分 追加到 缓冲序列尾部
    while( i< n1 ){
        wait_sort[p] = left[i];
        i++;
        p++;
    }

    while( j < n2 ){
        wait_sort[p] = right[j];
        j++;
        p++;
    }

}

void merge_sort(int start,int end)
{
    if(start < end){
        int mid = (end + start ) / 2;
        merge_sort(start,mid);
        merge_sort(mid+1,end);
        merge(start,mid,end);
    }
}

int main(void)
{
    merge_sort(0,MAX_SIZE - 1);
    show(wait_sort,MAX_SIZE);
    return 0;

}

// 算法分析 平均时间复杂度 O(nlogn) 最优时间复杂度 O(nlogn) (当原始序列与期望排序顺序一致时) 最坏时间复杂度 O(nlogn) 辅助存储O(n) 稳定排序.