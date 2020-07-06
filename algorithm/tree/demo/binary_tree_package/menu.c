// 如果我们可以预先排序列表 就可以改进顺序查找

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tree.h"

char menu(void);
void addpet(Tree *pt);
void droppet(Tree * pt);
void showpets(const Tree * pt);
void findpet(const Tree * pt);
void printitem(Item item);
void uppercase(char * str);
char * s_gets(char * st,int n);

int main(void)
{
    Tree pets;
    char choice;

    InitializeTree(&pets);

    while( (choice = menu() ) !='q' )
    {
        switch (choice) {
            case 'a':addpet(&pets);
                break;
            case 'l':showpets(&pets);
                break;
            case 'f':findpet(&pets);
                break;
            case 'n':printf("%d pets in club \n",TreeItemCount(&pets));
                break;
            case 'd':droppet(&pets);
                break;
            default: puts("Switching error");
        }
    }

    DeleteAll(&pets);
    puts("Bye.");

    return 0;
}

char menu(void)
{
    int ch;
    puts("《 Ner Pet Club Membership Program 》");
    puts("Enter the letter corresponding to your choice");
    puts(" a ) add a pet        l ) show list of pets ");
    puts(" n ) number of pets   f ) find pets ");
    puts(" d ) delete a pet     q ) quit ");

    while((ch = getchar()) != EOF)
    {
        // 处理输入缓冲中的剩余内容
        while(getchar() != '\n')
        {
            continue;
        }

        ch = tolower(ch);
        if(strchr("alrfndq",ch) == NULL ){
            puts("Please enter an a , l , f , n ,d or q;");
        } else {
            break;
        }
    }

    if(ch == EOF){
        ch = 'q';
    }

    return ch;

}

void addpet(Tree *pt)
{
    Item temp;
    if(TreeIsFull(pt)){
        puts("No room in the club");
    } else {
        puts("Please enter name of pet:");
        s_gets(temp.petname,SLEN);
        puts("Please enter pet kind:");
        s_gets(temp.petkind,SLEN);

        // 树中只存储大小子母  查询之前需要将查询字符串转换为大小
        uppercase(temp.petkind);
        uppercase(temp.petname);
        AddItem(&temp,pt);
    }
}

void showpets(const Tree * pt)
{
    if(TreeIsEmpty(pt)){
        puts("No entries!");
    } else {
        Traverse(pt,printitem);
    }
}

void printitem(Item item)
{
    printf("Pet : %-19s Kind : %-19s \n",item.petname,item.petkind);
}

void findpet(const Tree * pt)
{
    Item temp;
    if(TreeIsEmpty(pt)){
        puts("No entries !");
        return;
    }

    puts("Please enter name of pet you wish to find:");
    s_gets(temp.petname,SLEN);
    puts("Please enter kind of pet:");
    s_gets(temp.petkind,SLEN);

    uppercase(temp.petname);
    uppercase(temp.petkind);

    printf(" %s the %s ",temp.petname ,temp.petkind);
    if(InTree(&temp,pt)){
        printf("is a memmber \n");
    } else {
        printf("is not a member. \n");
    }
}

void droppet(Tree *pt)
{
    Item temp;

    if(TreeIsEmpty(pt)){
        puts("No entries !");
        return;
    }

    puts("Please enter name of pet you wish to delete:");
    s_gets(temp.petname,SLEN);
    puts("Please enter kind of pet:");
    s_gets(temp.petkind,SLEN);

    uppercase(temp.petname);
    uppercase(temp.petkind);

    printf(" %s the %s ",temp.petname ,temp.petkind);
    if(DeleteItem(&temp,pt)){
        printf("is droped from the Club \n");
    } else {
        printf("is not a member. \n");
    }

}

void uppercase(char * str)
{
    while(*str)
    {
        *str = toupper(*str);
        str++;
    }
}

char * s_gets(char * st,int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st,n,stdin);
    if(ret_val)
    {
        find = strchr(st,'\n');
        if(find){
            // C 字符串以 '\0' 结尾
            *find = '\0';
        } else {
            // 输入行中多出来的字符会继续留在输入缓冲中,成为下一次读入语句的输入
            while(getchar() != '\n'){
                continue;
            }
        }
    }

    return ret_val;
}