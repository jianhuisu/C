## 联合

### union介绍
    
联合是一种数据类型,可以在同一个存储空间内存储不同的数据类型(但是不是同时存储).

### union初始化

    union hold {
        int digit;
        double bigf1;
        char letter;
    };
    
    union hold val_a;
    val_a.letter = 'S';
    union hold val_b = val_a;
    union hold val_c = {88};  // 第一个成员值初始化为 88  
    union hold val_d = {.bigf1=118.2};

### union使用注意事项

    union material {
        int water;
        char ice;
        double steam;
    }    
    
    material eg;
    
    eg.water = 1;    // 把1存储在eg ,占用 4个字节
    eg.ice   = 'D';  // 清除1 存储'D' 占用1个字节
    eg.steam = 2.0;  // 清除'D',存储2.0 占用8个字节

在union中存储数据后,要按照正确的方式读取，否则读取出来的数据可能跟你的期望值不同.观察下面例子的输出:

    #include <stdio.h>
    
    int main(void)
    {
        typedef union {
            int a;
            char b;
            float c;
        } union_demo;
    
        union_demo ud;
    
        ud.c = 4.00;
        printf("sizeof : %u , value : %d %c %f\n",sizeof(union_demo),ud.a,ud.b,ud.c);
    
        ud.b = 'C';
        printf("sizeof : %u , value : %d %c %f\n",sizeof(union_demo),ud.a,ud.b,ud.c);
    
        ud.a = 1;
        printf("sizeof : %u , value : %d %c %f\n",sizeof(union_demo),ud.a,ud.b,ud.c);
    
        return 0;
    }

输出:

    /home/sujianhui/CLionProjects/C/cmake-build-debug/test
    sizeof : 4 , value : 1082130432   4.000000
    sizeof : 4 , value : 1082130499 C 4.000032
    sizeof : 4 , value : 1  0.000000

第一次输出时,内存单元存储值为`float`类型,所以只有最后面的`%f`解析出正确数据.

### union使用场景

1 设计一种表,事先不知道顺序的混合类型,使用联合型的数组,每个联合可以存储任意数据类型.
2 假设用一个结构表示汽车，如果汽车属于驾驶者，需要一个成员描述驾驶者.如果汽车被租赁,需要一个成员描述租赁公司.

    struct car {
        union owner own;
        int own_status;
        char car_name[20];
    }
    
    typedef struct {
        char name[20];
        int age;
    }car_user;
    
    typedef struct {
            char address[20];
            int employee_count;
    }car_company;  
    
    union owner {
        car_company car_com;
        car_user car_u;
    }
    
 - 如果`own_status`为`1`,代表所有者为租赁公司.输出`own.car_com.address`.
 - 如果`own_status`为`2`,代表所有者为个人.输出`own.car_u.name`.