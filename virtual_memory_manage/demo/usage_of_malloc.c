#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    typedef struct{
        int length;
        char *name;
    }u_t;

    int c = 1;

    while(c<100){
    //while(c){

        u_t * ptr = malloc(sizeof(u_t));

        if(ptr != NULL ){
            ptr->length = c;
            ptr->name = malloc(1000);
            strcpy(ptr->name,"hello");
            printf("malloc 1000 bytes ; number : %d , name : %s \n",ptr->length,ptr->name);

            // 如果把释放内存操作注释 那么会造成内存泄露
            free(ptr->name);
            free(ptr);
            ptr = NULL;
            c++;

        } else {
            printf("out of memory,total use %u bytes \n",1000 * c );
            exit(1);
        }

    }

    return 0;
}

