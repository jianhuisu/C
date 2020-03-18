//
// Created by guangsujiqiang on 3/18/20.  函数式宏定义中  允许传空参数
//


#define FOO() foo

#define FOO1(a) foo1##a

#define FOO2(a,b,c) a##b##c

FOO()

FOO1(ddd)

// FOO在定义时带三个参数，在调用时也必须传三个参数给它，空参数的位置可以空着，但必须给够三个参数
FOO2(1,2,3)
FOO2(,2,3)
FOO2(1,,3)
FOO2(1,2,3)
FOO2(,,3)
FOO2(,,)


/*

 [guangsujiqiang@su-ct7 preprocessing]$>cpp empty_args.c
# 1 "empty_args.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "empty_args.c"
# 12 "empty_args.c"

foo

foo1ddd

123
23
13
123
3


 */
