//
// Created by 苏建辉 on 2020/1/11. 获取最大公约数
//

#include <stdio.h>


int get_gcd(int a,int b);


int get_gcd(int a ,int b)
{
    int gt,lt;
    int remainder;

    // base case
    if(a == b){
        return a;
    }else if(a > b){
        gt = a;
        lt = b;
    }else {
        gt = b;
        lt = a;
    }

    remainder = gt % lt;

    if( remainder == 0){
        return lt;
    } else {
        return get_gcd(lt,remainder);
    }

}

int main(void)
{
    int a = 11;
    int b = 5;
    printf(" %d  and  %d great common divisor is : %d \n ",a,b,get_gcd(a,b));
    return 0;
}

