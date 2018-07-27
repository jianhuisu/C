#include <stdio.h>

struct name{
    char age[40];
    char sex[40];
};

struct fir{
    struct name su;
    char face[40];
};

// 指向结构的指针
void main(void)
{
    struct fir coll[2] = {
        {
            {"age:18","sex:1"},
            "white face"
        },
        {
            {"age:20","sex:2"},
            "black face"
        },

    };

    struct fir * him ;

    printf("#1 address: %p , #2 address: %p \n",&coll[0],&coll[1]);

    him = &coll[0];
    printf("#1 value: %s , #2 value: %s \n",him->face,(*him).face);
    him++;
    printf("#1 value: %s , #2 value: %s \n",him->face,(*him).face);

}
#if 0
#1 address: 0x7fff0c1d15d0 , #2 address: 0x7fff0c1d1648
#1 value: white face , #2 value: white face
#1 value: black face , #2 value: black face


him 是一个指向结构的指针 但是 him->face 是该指针所指向结构的一个成员

如果 library 是一个结构变量 那么需要使用 &library 形式获取变量地址

    him = &library   （library 等价于 &coll[0] ）
    进而推导出  him = &coll[0];

    *him 等价于 library
    那么
    (*him).face 等价于 library.face





#endif