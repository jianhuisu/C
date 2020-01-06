//
// Created by guangsujiqiang on 1/6/20.  插入排序   参考 LinuxC编程一站式学习 http://yayi.me/doc/C/ch11s02.html
//

#include <stdio.h>
#define LEN 6
int * insert_sort(int arr[]);
void arr_dump(int arr[],int len);

int main()
{
    int age[LEN] = {2,1,3,5,4,6};
    arr_dump(age,LEN);
    printf(" ---------------------------------- \n");
    insert_sort(age);

}

// 将数组按从左至右 从小到大排序
int * insert_sort(int arr[])
{
    int i,j,key,tmp;
    for(j=1;j<LEN;j++){

        arr_dump(arr,LEN);
        key = arr[j];
        i = j-1;

        // 移动一位之后 立即对左边进行排序 确保左边一直处于有序状态
        // 将最小值移动到最左边
        while(i >= 0 && arr[i] > key){
            tmp = arr[i+1];
            arr[i+1] = arr[i];
            arr[i] = tmp;
            i--;
        }

    }

}

void arr_dump(int arr[],int len){

    int i;
    //printf(" \narray (lengths: %d)(\n ",len);
    for(i=0;i<len;i++) {
        // printf(" %d => %d,\n ",i,arr[i]);
        printf(" %d ",arr[i]);
    }
    //printf("\n)\n ");
    printf("\n ");

}

/*
    复杂度分析
    长度为N的集合 将集合按从左至右 从小到大排序

最坏时间复杂度

    1 * 1 + 1 * 2 + ... 1*(n-1) = 1 + 2 + 3 + ... (n - 1) = (1 + (n -1)) / 2 = 0.5n

 */


/*

    下面为精简写法
    #include <stdio.h>

    #define LEN 5
    int a[LEN] = { 10, 5, 2, 4, 7 };

    void insertion_sort(void)
    {
    int i, j, key;
    for (j = 1; j < LEN; j++) {
        printf("%d, %d, %d, %d, %d\n",
               a[0], a[1], a[2], a[3], a[4]);
        key = a[j];
        i = j - 1;
        while (i >= 0 && a[i] > key) {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
    printf("%d, %d, %d, %d, %d\n",
           a[0], a[1], a[2], a[3], a[4]);
    }

    int main(void)
    {
    insertion_sort();
    return 0;
    }

*/
