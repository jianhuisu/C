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

// 选择排序-简单选择排序 这是学起来最简单的排序方法 ，最符合我们的惯用思维
// 选择一个序列中的最小值,放在最左边,
// 在剩余序列中选择最小值，放在剩余序列的最左边
void simple_select_sort(int arr[],int length)
{
    // 从序列中选出最小值放在最左边
    // 从剩余序列中选出最小值放在最左边
    // 往复循环 最终得到非递减序列
    int min_v_index;
    int j;
    int i;
    int temp;

    for(i = 0;i<length;i++){
        min_v_index = i;
        for(j = i+1; j < length;j++){

            // 取两者比较中较小者
            if(arr[min_v_index] > arr[j]){
                min_v_index = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[min_v_index];
        arr[min_v_index] = temp;

    }

}

int main(void)
{
    show(wait_sort,10);
    simple_select_sort(wait_sort,10);
    show(wait_sort,10);
    return 0;
}

// 简单选择排序的 时间复杂度 最优 O(n^2) 最坏 O(n^2) 平均 O(n^2) ，辅助空间O(1) 不是稳定排序 适用场景： n较小时使用