//
// Created by guangsujiqiang on 1/10/20.  递归实现求最大公约数
//
#include <stdio.h>


int get_gcd(int a,int b);

int get_gcd(int a,int b)
{
    int gt,lt,remainder;

    if(a == b){
        return a;
    } else if (a>b){
       gt = a;
       lt = b;
    } else {
        gt = b;
        lt = a;
    }

    int remainder = gt % lt;

    // base case
    if(remainder == 1){
        return 1;
    }

    if(remainder == 0){
        return lt;
    } else {
        return get_gcd(lt,remainder);
    }
}

int main(int argc,char *argv[])
{
    puts("hello world");
    int a = 4;
    int b = 3;
    int gcd = get_gcd(1,2);
    printf("great common divisor [ %d , %d ] is %d \n",a,b,gcd);
    return 0;
}


