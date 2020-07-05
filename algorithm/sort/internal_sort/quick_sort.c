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

void swap(int * i,int * j)
{
    int temp;
    temp = *i;
    *i = *j;
    *j = temp;
}

void sort(int *a, int left, int right)
{
    // 快速错误
    if(left >= right){
        return ;
    }
    show(a,6);
    int i = left;
    int j = right;
    int key = a[left];  // 选取第一个元素为枢纽点

    // 快速排序的一次划分算法从两头交替搜索，直到low和high重合，因此其时间复杂度是O(n)；
    while(i < j)
    {
        // 从右向左寻找第一个小于枢纽点的元素 ， 与最低位元素进行 位置互换
        while(i < j && key <= a[j])
        {
            j--;/*向前寻找*/
        }
        swap(&a[i],&a[j]);

        // 从左向右寻找第一个大于枢纽点的元素 ，从左边序列剔除,插入右边序列(即与枢纽点互换，保证元素在枢纽点的右侧序列)
        while(i < j && key >= a[i])
        {
            i++;
        }

        swap(&a[i],&a[j]);
        //a[j] = a[i];
    }

    //a[i] = key;/*当在当组内找完一遍以后就把中间数key回归*/
    sort(a, left, i - 1);/*最后用同样的方式对分出来的左边的小组进行同上的做法*/
    sort(a, i + 1, right);/*用同样的方式对分出来的右边的小组进行同上的做法*/
}


int main(void)
{
    int arr[6] = {3 ,9 ,4 ,2 ,7 ,1};
    sort(arr,0,5);
    show(arr,6);
    return 0;
}

// 疑问： 快速排序是如何保证 左边的任意一个数 小于 右边序列中的任意一个数 : 数往两边扔 ，多挑几次，多扔几次 ，就可以保证左边小于右边

