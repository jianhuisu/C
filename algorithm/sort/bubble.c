#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

void var_dump(const int arr[],int elementsCount);
/*
 * sort from left , move max(99,12) right ,move min(99,12) left, after on cycle ,can make sure the
 * rightest number is max number in given set
 * 按从左致右 从小到大 排序
 * */

void main(void){

    //int waitToSort[MAX_SIZE] = {99,12,88,4,66,3,666,34,55,100};
    int waitToSort[MAX_SIZE] = {10,9,8,7,6,5,4,3,2,1};
    printf("there is %d elements in array \n", sizeof(waitToSort) / sizeof(waitToSort[0]));

    var_dump(waitToSort,MAX_SIZE);

    int i,j,tmp;

    // n 个元素两两比较,需要(n-1)次 得出本次比较的最大值
    for(j=9;j>0;j--){
        for(i=0;i<j;i++){

            if(waitToSort[i] > waitToSort[i+1]){
                tmp = waitToSort[i];
                waitToSort[i] = waitToSort[i+1];
                waitToSort[i+1] = tmp;
            }
        }
        var_dump(waitToSort,MAX_SIZE);
    }

}

/*
 *  情况下n个数字进行 bubble sort
 *  (n-1)*(n-1) + (n-1)*(n-1-1) + ... (n-1) * 1 = (n-1)(n-1+1) => n(n-1) => n^2 - n
 *
 *  最好情况下 时间复杂度 O(n)
 *  最坏情况下 时间复杂度 O(n^2)
 *  平均时间复杂度 O(n^2)
 * */

void var_dump(const int arr[],int elementsCount){

    int i;

    printf("\n");
    for(i=0;i < elementsCount;i++){
        printf(" %4d ",arr[i]);
    }
    printf("\n");

}