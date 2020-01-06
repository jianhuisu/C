#include <stdio.h>
#define LEN 6
void arr_dump(int arr[]);
void arr_dump_plus(int arr[],int length);

int main()
{
    int arr[LEN] = {2,1,3,5,4,6};

    printf("array address is [%p] ; array use [%6d] bytes ,have [%6d] elements , one of these use [%6d] bytes \n",arr, sizeof(arr),
           sizeof(arr) / sizeof(int), sizeof(int));
    arr_dump(arr);
    arr_dump_plus(arr,sizeof(arr) / sizeof(int));
    return 0;
}

/*
    数组名被当作实参传递以后 转化为一个指向数组首元素地址的指针标量。
    数组名并不完全等同于指针 ，只能说数组名在某些场景中下可以当作指针来使用。
    所以这就是为什么在数组声明处 使用 sizeof(arr) 可以返回数组所占字节数 ，
    但是如果将数组名当作函数的实参传递，在调用函数中使用sizeof(arr)时，无法获得数组所占用的字节数
    传参时 发生了类型转换,数组名丢失了一部分信息 转化成一个普通的指针变量

    这里最重要的一点就是 数组名 并不完全等同与 指针
    只有当数组名在表达式中使用时，编译器才会为它产生一个指针常量。而只有以下两种情况，才不被当做指针常量：

    sizeof(数组名)：返回数组长度（所占的字节数，不是数组元素个数）
    &数组名：产生一个指向数组的指针，而不是一个指向某个指针常量的指针

    以上内容来源：《C和指针》P141~142
    https://segmentfault.com/q/1010000003848156

 */
void arr_dump(int arr[]){

    // 实际上这里 sizeof(arr) 返回的是一个指向 数组的指针 所占用的字节数
    printf("array address is [%p] ; array use [%6d] bytes ,have [%6d] elements , one of these use [%6d] bytes \n",arr, sizeof(arr),
           sizeof(arr) / sizeof(int), sizeof(int));

}

/*
        [guangsujiqiang@su-ct7 array]$>gcc how_to_get_array_elements_num.c && ./a.out
        array address is [0x7ffd7d648ee0] ; array use [    24] bytes ,have [     6] elements , one of these use [     4] bytes
        array address is [0x7ffd7d648ee0] ; array use [     8] bytes ,have [     2] elements , one of these use [     4] bytes
*/


void arr_dump_plus(int arr[],int length){

    printf("array address is [%p] ; array use [%6d] bytes ,have [%6d] elements , one of these use [%6d] bytes \n", arr,
           sizeof(int) * length,
           length, sizeof(int));

    int i;
    printf(" \narray (lengths: %d)(\n ",length);
    for(i=0;i<length;i++) {
        printf(" %d => %d,\n ",i,arr[i]);
    }
    printf("\n)\n ");

}

/*

    [guangsujiqiang@su-ct7 array]$>gcc how_to_get_array_elements_num.c && ./a.out
    array address is [0x7ffef3184530] ; array use [    24] bytes ,have [     6] elements , one of these use [     4] bytes
    array address is [0x7ffef3184530] ; array use [     8] bytes ,have [     2] elements , one of these use [     4] bytes  // 输出中包含错误
    array address is [0x7ffef3184530] ; array use [    24] bytes ,have [     6] elements , one of these use [     4] bytes

    array (lengths: 6)(
      0 => 2,
      1 => 1,
      2 => 3,
      3 => 5,
      4 => 4,
      5 => 6,
    )


 */