#include <stdio.h>
void main(void)
{
    int num;
    char name[5];
    FILE *fp;
    if ((fp = fopen("t.txt", "w")) == NULL)
        printf("cannot open file!\n");

    // num 是整型变量 需要使用 取地址运算符获取地址 name 是字符型数组  , 数组名 即为 数组首元素地址
   scanf("%d %s",&num,name);

   fprintf(fp, "%d %s", num, name);
   fclose(fp);

   if ((fp = fopen("tt.txt", "w")) == NULL)
        printf("cannot open file!\n");
   fwrite(&num, sizeof(int), 1, fp);
   fwrite(name, sizeof(char), 5, fp);
   fclose(fp);
}
