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