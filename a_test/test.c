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


int merge(int start,int mid,int end){

    int n1 = mid - start + 1;
    int n2 = end - mid;

    // assign left_seq / right seq
    int left[n1];
    int right[n2];

    int i = 0,j = 0;

    while(i < n1){
        left[i] = wait_sort[start+i];
        i++;
    }

    while(j < n2){
        right[j] = wait_sort[mid+j+1];
        j++;
    }

//    show(left,n1);
//    show(right,n2);

    i = j = 0;
    int p = start;

    // kernel merge , use three pointer , step add ,until one seq is empty
    while( i < n1 && j < n2 ){

        if(left[i] < right[j]){
            wait_sort[p] = left[i];
            i++;
            p++;
        }

        if(left[i] > right[j]){
            wait_sort[p] = right[j];
            j++;
            p++;
        }

    }

    // copy left seq space
    while(i < n1){
        wait_sort[p] = left[i];
        p++;
        i++;
    }

    while(j < n2){
        wait_sort[p] = right[j];
        p++;
        j++;
    }

}

void merge_sort(int start , int end){
    if(start < end ){
        int mid = (start + end ) / 2;
        merge_sort(start,mid);
        merge_sort(mid + 1, end);
        merge(start,mid,end);
    }
}

int main(void)
{
    //merge(0,2,5);
    merge_sort(0,MAX_SIZE - 1);
    show(wait_sort,MAX_SIZE);
    return 0;
}

