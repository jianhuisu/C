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

// 排序为非递减序列  => 稳定的类递增序列

//1 确定初始序列 list ,插入结点 x
//    以待排序 数据记录的首元素为初始序列,首元素的下一个元素为插入结点
//
//2 确定插入结点下表,确定初始序列长度
//    若插入结点下标为 i,则初始序列长度为 i-1
//
//3 遍历初始序列中元素m,逐个与插入结点比较.当  x < m ,交换x,m位置 ,当x > m 时,终止向左比较,进行下一趟排序,

int main(void)
{
    int wait_sort[MAX_SIZE] = {49,38,13,97,76,65,27,49,99,18};
    show(wait_sort,MAX_SIZE);

    int i ,j,tmp;

    // 从数组中的第二个元素开始插入比较 ，即从数组下标为1的元素开始插入比较
    for(i = 1;i < MAX_SIZE;i++){

        for(j = i ;j>0;j--){

            // 如果 后者小于前者 那么 交换位置
            if(wait_sort[j] < wait_sort[j-1]){
                tmp =     wait_sort[j];
                wait_sort[j] = wait_sort[j-1];
                wait_sort[j-1] = tmp;
                //break;
            } else {
                break;
            }

        }
    }

    show(wait_sort,MAX_SIZE);

    return 0;
}

// 算法分析 平均时间复杂度 O(n^2) 最优时间复杂度 O(n) (当原始序列与期望排序顺序一致时) 最坏时间复杂度 O(n^2) (当原始序列与期望排序顺序逆序时) 辅助存储O(1):只借助了temp变量 稳定排序.