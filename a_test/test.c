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

void swap(int * i,int * j)
{
        int temp;
        temp = *i;
        *i = *j;
        *j = temp;
}

void quick_sort(int a[],int left,int right)
{
    // 快速错误
    if(left >= right ){
        return ;
    }

    int i = left;
    int j = right;
    int pivot = a[left];

    while(left < right)
    {
        // 从右边找小值
        while(left < right && pivot < a[right]){
            right--;
        }
        swap(&a[left],&a[right]);

        // 从左边找大值
        while(left < right && pivot > a[left]){
            left++;
        }
        swap(&a[left],&a[right]);
    }

    // 递归调用
    quick_sort(a,i,left - 1);
    quick_sort(a,left + 1,j);

}

int main(void)
{
    quick_sort(wait_sort,0,MAX_SIZE - 1);
    show(wait_sort,MAX_SIZE);
    return 0;
}
