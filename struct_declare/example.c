#include <stdio.h>

struct compound_type{
    int a,b;
};

struct compound_type_1{
    int a,b;
}ct1,ct2;


struct {
    int a,b;
}ct3,ct4;

int main(int argc,char * argv[])
{
    struct compound_type global_v_a = {13,14};

    ct1.a = 13;
    ct1.b = 14;

    ct3.a = 13;
    ct3.b = 14;

    struct local_struct_type{
        float x,y;
    };

    struct local_struct_type z1 = {3.14,5.21};


    printf("struct compound_type : [a => %d , b=> %d ] \n",global_v_a.a,global_v_a.b);
    printf("struct local_struct_type : [a => %f , b=> %f ] \n",z1.x,z1.y);

    puts(" pass ");
    return 0;
}