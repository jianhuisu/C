#include <stdio.h>
#define MAX_SIZE 10
int wait_sort[MAX_SIZE] = {19,100,34,34,3,43,2,6,8,0,1};

void swap(int * a, int * b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void show(int * a,int len){
    int i;
    for(i = 0;i<len;i++){
        printf(" %4d ",a[i]);
    }
    puts("");
}

void sort(int *a,int left,int right)
{
    if(left >= right){
        return;
    }

    show(wait_sort,MAX_SIZE);

    int i = left;
    int j = right;
    int pivot = a[i];

    while(i < j){
        while(i<j && pivot <= a[j]){
            j--;
        }
        a[i] = a[j];

        while(i<j && pivot >= a[i]){
            i++;
        }
        a[j] = a[i];
    }

    a[i] = pivot;

    sort(a,left,i-1);
    sort(a,i+1,right);

}

int main(){
    show(wait_sort,MAX_SIZE);
    sort(wait_sort,0,MAX_SIZE - 1);
    return 0;
}