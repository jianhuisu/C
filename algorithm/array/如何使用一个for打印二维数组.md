## 如何使用一个for打印二维数组

常规打印先打印`for + for`,使用一个`for`的话将二维数组看成分段的一维数组.

    #include <stdio.h>
    
    int main(void)
    {
        char name[4][5] = {
                {'a','b','c','d','e'},
                {'a','b','c','d','e'},
                {'a','b','c','d','e'},
                {'a','b','f','d','e'},
        };
    
        int i;
        for(i = 0;i< 4 * 5;i++)
        {
            printf("name[%d][%d] => %c ",i/5,i%5,name[i/5][i%5]);
            if( (i + 1) % 5  == 0 ){
                printf("\n");
            }
        }
        
        return 0;
    }