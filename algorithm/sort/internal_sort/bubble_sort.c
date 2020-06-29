#include <stdio.h>
#define MAX_SIZE 10

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


int main(void)
{
    int wait_sort[MAX_SIZE] = {49,38,13,97,76,65,27,49,99,18};
    show(wait_sort,MAX_SIZE);

    int i ,j,tmp;

    for(i=0;i<MAX_SIZE;i++){

        // optimize : for(j = 0;j< MAX_SIZE - 1;j++){
        for(j = 0;j< MAX_SIZE - (i+1);j++){
            if(wait_sort[j] > wait_sort[j+1]){
                tmp = wait_sort[j+1];
                wait_sort[j+1] = wait_sort[j];
                wait_sort[j]   = tmp;
            }
        }
        show(wait_sort,MAX_SIZE);
    }


    /*
        循环部分还可以再次优化 逻辑上更加清晰
        for(j=9;j>0;j--){
        for(i=0;i<j;i++){

            if(waitToSort[i] > waitToSort[i+1]){
                tmp = waitToSort[i];
                waitToSort[i] = waitToSort[i+1];
                waitToSort[i+1] = tmp;
            }
        }
    }

    */



    show(wait_sort,MAX_SIZE);
    return 0;
}

// 算法分析 平均时间复杂度 O(n^2) 最优时间复杂度 O(n) (当原始序列与期望排序顺序一致时) 最坏时间复杂度 O(n^2) (当原始序列与期望排序顺序逆序时) 辅助存储O(1):只借助了temp变量 稳定排序.