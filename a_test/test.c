// 快排  34分钟
// 归并  20分钟
// 堆排序 40
// 冒泡排序
// 插入排序
// 简单选择排序

#include <stdio.h>
#define MAX_SIZE 10
int wait_sort[MAX_SIZE] = {11,15,20,13,17,65,27,49,99,18};


static void show(int * s,int length)
{
    int i ;
    for(i=0;i<length;i++){
        printf(" %d ",s[i]);
    }

    printf("\n");
}

static void swap(int * a ,int *b)
{
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void build_max_heap(int * a, int start ,int end)
{
    if(start >= end ){
        return;
    }

    // 自上而下筛选法
    int child_idx = start * 2 + 1;
    while(child_idx <= end){

        if(child_idx + 1 <= end && a[child_idx] < a[child_idx+1]){
            child_idx++;
        }

        if(a[start] > a[child_idx]){
            //如果父节点大於子节点代表调整完毕，直接跳出函数
            break;
        } else {
            swap(&a[start],&a[child_idx]);
            start = child_idx;
            child_idx = child_idx * 2 + 1;
        }

    }

}

// 堆筛选得出堆顶值
// 将筛选得出的堆顶值与末尾元素互换 ，得出n个元素序列中的最小值 ，
// 往复循环
void sort(int * a, int len)
{

    int i;

    // step.1 因为期望排序顺序为从小到大 ，那么构建一个全序列的大顶堆
    // ！！！！！！！从最后一个分支结点【i = len/2 - 1】开始筛选 自下而上 大值上浮 ，小值下降
    // ！！！！！！！ 注意从分支结点 递减 筛选 【i = len / 2 - 1;i >= 0;i--】
    for(i = len / 2 - 1;i >= 0;i--){
        build_max_heap(a,i,len - 1);
    }

    // step.2 循环堆 n-1 个元素的序列，n-2 个元素的序列 进行 筛选，交换
    for(i = len - 1;i>=0;i--)
    {
        swap(&a[0],&a[i]);
        build_max_heap(a,0,i-1);
    }

}



int main(void)
{
    printf("堆排序\n");
    show(wait_sort,MAX_SIZE);
    sort(wait_sort,MAX_SIZE);
    show(wait_sort,MAX_SIZE);
    return 0;
}

