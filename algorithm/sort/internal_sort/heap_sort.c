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
void swap(int * a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void build_big_heap(int a[],int i,int len)
{
    int child;
    child = i*2 + 1;

    while( child < len){

        if( (child + 1) < len && a[child] < a[child+1]){
            child++;
        }

        if(a[i] < a[child]){
            swap(&a[child],&a[i]);
            i = child;
            child = child *2 + 1;
        } else {
            break;
        }

    }
}

// 目的 ： 升序排列数组
// step.1 构建大顶堆
// step.2 交换根结点 与 末尾终端结点
// step.3 对剩元素继续构建大顶堆,交换...
void heap_sort(int a[],int length)
{
    int i;

    // build
    for(i = length / 2 - 1;i>= 0 ;i--){
        build_big_heap(a,i,length);
    }

    // swap
    for(i = length - 1;i>=0 ; i--){
        swap(&a[i],&a[0]);
        build_big_heap(a,0,i );
    }

}

int main(void)
{
    // merge_sort
    // quick_sort
    // heap_sort
    heap_sort(wait_sort,MAX_SIZE);
    show(wait_sort,MAX_SIZE);
    return 0;
}