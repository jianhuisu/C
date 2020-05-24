#include <stdio.h>
#define LEN 5
int a[LEN] = {10,5,2,4,7};

/*
 *  execute process
 *
 *   insert 5 ,  5 10 2 4 7
 *   insert 2 ,  5 2 10 4 7  -> 2 5 10 4 7
 *   insert 4 ,  2 5 4 10 7  -> 2 4 5 10 7
 *   insert 7 ,  2 4 5 7 10
*/

void insert_sort(void)
{
    int i,j;
    int key;

    for(j = 1;j < LEN ; j++){
        key = a[j];

        i = j - 1;
        while(i >= 0 && key < a[i]){
            // move small left , move big right
            a[i+1] = a[i] ;
            i--;
        }

        a[i+1] = key;
    }

    printf("a :{ %d  %d %d %d %d }\n",a[0],a[1],a[2],a[3],a[4]);
}

int main(int argc,char * argv[])
{
    printf("hello \n");
    insert_sort();
    return 0;
}
