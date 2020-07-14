#include <stdio.h>


static int binary_search_use_rec(int findData,int * a,int start,int end)
{
    if(start < end){
        int mid = (start + end) / 2;
        if( findData == a[mid] ){
            //return a[mid];
            return mid;
        } else if(findData < a[mid]){
            return binary_search_use_rec(findData,a,start,mid - 1);
        } else {
            return binary_search_use_rec(findData,a,mid + 1,end);
        }
    }

    return -1;
}

static int binary_search_without_rec(int findData,int * a,int start,int end)
{
    while(start < end){
        int mid = (start + end) / 2;
        if( findData == a[mid] ){
            //return a[mid];
            return mid;
        } else if(findData < a[mid]){
            end = mid - 1;
        } else {
            start = mid + 1;
        }
    }

    return -1;
}

int main(void)
{
    int findData = 3;
    int a[10] = {1,2,3,4,5,6,7,8,9,10};

    printf("index : %d \n",binary_search_without_rec(findData,a,0,9));
    return 0;
}