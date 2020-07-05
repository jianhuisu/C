// 快排
// 归并排序
// 堆排序

#include <stdio.h>
#define MAX_SIZE 10
int wait_sort[MAX_SIZE] = {11,2,53,4,5,6,79,8,19,90};

void show(int s[],int len)
{
    int i;
    for(i = 0;i<len;i++){
        printf("%d ",s[i]);
    }

    printf("\n");
}

void swap(int * a,int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 相较于普通的选择排序 可以快速的选出序列中的极值
// 从叶结点开始向下查找极值 ，大者上移
void build_max_heap(int * s,int start,int end)
{
    int a = s[start];
    if(start >= end){
        return ;
    }

    int child = 2 * start + 1;

    while( child < end ){
        if((child + 1) < end && s[child+1] > s[child]){
            child++;
        }

        if(s[start] < s[child]){
            swap(&s[start],&s[child]);
            child = 2 * child + 1;
        } else {
            break;
        }
    }


}

// 堆排序
// 将序列构建为一个堆,则堆顶是极值,将堆顶元素与序列末尾元素交换, 重复该过程
// 升序 大顶堆
// 降序 小顶堆
void sort(int s[],int len)
{
    int i;
    // 构建一个全序列的大顶堆  从叶子结点学习 插入排序+冒泡排序 下沉小值(其实就是逆向上浮大值)
    for(i = len / 2 - 1 ;i>=0;i--){
        build_max_heap(s,i,len);
    }

    // 交换 继续构建大顶堆
    for(i = len - 1 ;i>=0;i--){
        swap(&s[0],&s[i]);
        build_max_heap(s,0,i);
    }

}

int main(void)
{
    show(wait_sort,MAX_SIZE);
    sort(wait_sort,MAX_SIZE);
    show(wait_sort,MAX_SIZE);
    return 0;
}