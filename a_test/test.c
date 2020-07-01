#include <stdio.h>
#define MAX_SIZE 10
int wait_sort[MAX_SIZE] = {11,15,20,13,17,65,27,49,99,18};

//#define MAX_SIZE 3
//int wait_sort[MAX_SIZE] = {15,11,20};

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

void build_min_heap(int a[],int cur_node_index,int len)
{
    int child;
    // 保障端有序
    while(cur_node_index < len){
        child = cur_node_index * 2 + 1;

        // 较小者上升
        if(child < len && a[child] > a[child + 1]){
            child++;
        }

        // 三个数中只需要确定最小值即可,根 左 右 三个结点 ，需要两次相互比较即可以得出，如果需要确定三个数的大小顺序，则需要比较三次
        if(child < len && a[child] < a[cur_node_index]){
            swap(&a[child],&a[cur_node_index]);
            cur_node_index = child;
        } else {
            break;
        }
    }


}

void heap_sort(int a[],int len)
{
    // 按降序排列 将无序序列构建为小顶堆
    int i;
    for( i = len/2 - 1;i >= 0; i--){
        build_min_heap(a,i,len - 1);
    }

    // 交换 根结点 与 叶子结点
    for(i = len - 1;i>= 0;i--){
        swap(&a[0],&a[i]);
        build_min_heap(a,0,i - 1);
    }

}

int main(void)
{
    heap_sort(wait_sort,MAX_SIZE);
    show(wait_sort,MAX_SIZE);
    return 0;
}
