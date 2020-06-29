/**
 * 树型选择排序 - 堆排序
 * 堆排序与快速排序的区别
 * 堆排序的适用场景
 */

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

void adjustMinHeap(int a[],int pos,int len)
{
    int temp;
    int child;

    for(temp = a[pos]; 2 * pos + 1 <= len;pos = child)
    {
        child = 2 * pos + 1;
        if(child < len && a[child] > a[child + 1]){
            child++;
        }

        if( a[child] < temp ){
            a[pos] = a[child];
        } else {
            break;
        }
    }

    a[pos] = temp;

}

void Swap(int * a, int * b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void MyMinHeapSort(int array[],int len)
{
    int i;
    for(i = len/2 - 1;i>=0; i--){
        adjustMinHeap(array,i,len -1);
    }

    for(i = len - 1;i>=0;i--){
        Swap(&array[0],&array[i]);
        adjustMinHeap(array,0,i-1);
    }
}


int main(void)
{
    int array[] = {0,13,1,14,27,18};
    MyMinHeapSort(array,6);
    show(array,6);
    return 0;
}

// 简单选择排序的 时间复杂度 最优 O(n^2) 最坏 O(n^2) 平均 O(n^2) ，辅助空间O(1) ，适用场景： n较小时使用