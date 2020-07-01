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

// 冒泡排序
// 实现算法像分析长难句一样 ，分析时 从宏观 到微观 ，实现时 从微观 到宏观 ，实现冒泡排序 ，先实现 最内层的两两比较交换 -> 然后是内循环 -> 然后是外循环 -> 优化
// 每趟排序通过 两两比较 选择一个最小值移动到左边
// 然后从剩余序列中 继续 两两比较 继续选取最小值移动到左边

void bubble_sort(int arr[],int length)
{
    // 从序列最左边开始两两比较,取较大着向右移动,一趟排序(即 内循环 for() 整体执行完成一次 ),可以得出最大值，存储在最右边
    // 往复循环 得出次大值，存储在倒数第二位 ...

    int j;
    int i;
    int temp;

    for(i = length - 1;i > 0;i--){
        for(j = 0; j < i;j++){
            if(arr[j] > arr[j+1]){
                temp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j]  = temp;
            }
        }
    }

}

int main(void)
{
    show(wait_sort,MAX_SIZE);
    bubble_sort(wait_sort,MAX_SIZE);
    show(wait_sort,MAX_SIZE);
    return 0;
}

// 冒泡排序的 时间复杂度 最优 O(n) 最坏 O(n^2) 平均 O(n^2) ，辅助空间O(1) 是稳定排序 适用场景： n较小时使用