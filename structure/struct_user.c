#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct user{
    int id;
    char name[40];
};

typedef struct user_alias{
    int id;
    char name[40];
}USERALIAS;

typedef char BYTE;

void main(void)
{
    struct user employee;
    USERALIAS employee1;
    BYTE name[10] = "my name";

    employee.id   = 10010;
    strcpy(employee.name,"sjh");
    printf("today entry employee id is %d and name is %s \n",employee.id,employee.name);

    scanf("%s %d",&employee1.name,&employee1.id);
    printf("today entry employee1 id is %d and name is %s \n",employee1.id,employee1.name);

    printf("typedef  %s \n",name);
}

