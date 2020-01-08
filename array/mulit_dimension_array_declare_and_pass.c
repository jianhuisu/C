// 多维数组的声明与传递
// 参考资料 https://akaedu.github.io/book/ch08s05.html
#include <stdio.h>

// 可以省略最高维元素个数 其它维元素个数不可以省略
void dump_two_dimension_array(int td[5][5]){
    int i;
    for(i=0;i<5;i++) {
        printf(" %d ,  %d , %d , %d , %d \n",td[i][0],td[i][1],td[i][2],td[i][3],td[i][4]);
    }
    puts("-------------------------------------------");

}

//  Func((int**)a, 3, 3);
// dump_two_dimension_array use pointer way
void dump_two_dimension_array_up(int *p,int row,int col){
    int i,j;
    int *td;
    for(i=0;i<row;i++) {

        td = p + i; // 得出第二维数组首元素地址
        for(j=0;j<col;j++){
            printf(" %d ",*(td+j));
        }
        printf("\n");
    }

    puts("-------------------------------------------");

}

void main(void)
{
    // 以下两种声明方式同样有效
    int maze[5][5] = {
            1,0,0,0,1,
            1,0,0,0,1,
            1,0,0,0,1,
            1,0,0,0,1,
            1,0,0,0,1
    };

    int maze_clone[5][5] = {
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1}
    };



    printf("%p \n",maze);
    printf("%p \n",maze_clone);

    //dump_two_dimension_array(maze);
    //dump_two_dimension_array(maze_clone);
    dump_two_dimension_array_up(maze,5,5);
    dump_two_dimension_array_up(maze_clone,5,5);
}



