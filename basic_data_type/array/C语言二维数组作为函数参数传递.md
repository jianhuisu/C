## C语言二维数组作为函数参数传递

#### 二维数组存放方式

二维数组在内存中是按行存放的，先存储第一行，在接着存储第二行…..

#### 二维数组作为函数参数

二维数组作为函数的参数，实参可以直接使用二维数组名，在被调用函数中可以定义形参所有维数的大小，也可以省略以为大小的说明。例如：

    void find（char a[3][10]）;
    void find (char a[ ][10]);

也可以使用数组指针来作为函数参数，例如：

    void find （char (*p)[10]);

但是不能像下面这样使用，例如：

    void find（char a[ ][ ]）;
    void find (char a[3][ ]);

因为从实参传递来的是数组的起始地址，如果在形参中不说明列数，编译器将无法定位元素的的位置。

eg.2 

    int matrix[][5] = {
        {1,   4,  7, 11, 15},
        {2,   5,  8, 12, 19},
        {3,   6,  9, 16, 22},
        {10, 13, 14, 17, 24},
        {18, 21, 23, 26, 30}
    };

函数签名
    
    int searchMatrix(int ** matrix, int matrixRowSize, int matrixColSize, int target) {

使用方式

 - 通过编译 `printf("%d \n",searchMatrix((int **) matrix, row, col, target));`
 - 无法通过编译 `printf("%d \n",searchMatrix( matrix, row, col, target));` error msg `incompatitable pointer types passing int matrix[5][5] to arguments int ** matrix`  


#### 各个维数不固定的二维数组

如果不确定二维数组的维数的话，我们不能使用上面的方法，可以用下面的方法：

手工转变寻址方式
对于数组 int p[m][n];

如果要取p[i][j]的值（i>=0 && m<=0 && j>=0 && n<=0)，编译器是这样寻址的，它的地址为：

    p + i*n + j;

从以上可以看出，如果我们省略了第二维或者更高维的大小，编译器将不知道如何正确的寻址。但是我们在编写程序的时候却需要用到各个维数都不固定的二维数组 作为参数，
这就难办了，编译器不能识别阿，怎么办呢？不要着急，编译器虽然不能识别，但是我们完全可以不把它当作一个二维数组，而是把它当作一个普通的指 针，
再另外加上两个参数指明各个维数，
然后我们为二维数组手工寻址，这样就达到了将二维数组作为函数的参数传递的目的，根据这个思想，我们可以把维数固定 的参数变为维数随即的参数，例如
将

    void find（char a[3][10]）;
    void find (char a[ ][10]);

转换为

    void find (int **a,int m,int n);

在转变后的函数中，array[i][j]这样的式子是不对的，因为编译器不能正确的为它寻址，所以我们需要模仿编译器的行为把
`array[i][j]` 这样的式子手工转变为： `(( int )a+ n*i + j)`;

因为上次做了一道c语言的题，题目要求输入8个字符串，必须将字符串按字典序从小到大排列，排列的必须用函数实现，一下是我的代码：

    #include <stdio.h>
    #include <string.h>
    void range(char str[ ][100]);//传进二维数组
    int main(void)
    {
        char str[8][100];
        int i;
        for(i=0;i<8;i++)
            gets(str[i]);
        range(str);
        for(i=0;i<8;i++)
            printf("%s\n",str[i]);
    
    } 
    
    void range(char str[ ][100])
    {
        int i,j;
        char temp[100];
        for(i=0;i<8-1;i++)
        {
            for(j=0;j<8-i-1;j++)
            {
                if(strcmp(str[j],str[j+1])>0)
                {
                    strcpy(temp,str[j]);
                    strcpy(str[j],str[j+1]);
                    strcpy(str[j+1],temp);
                }
            }
        } 
    }

#### assign

how to assign ?

    int two_sum(int * a, int len,int target,int res_container[][2])
    {
        ...        
    }
    
wrong method

    int r[2];
    r[0] = a[left];
    r[1] = a[right];
    res_container[container_index] = r;    

right method
    
    res_container[container_index][0] = a[left];
    res_container[container_index][1] = a[right];

#### from 

https://blog.csdn.net/weixin_41666244/article/details/80615661