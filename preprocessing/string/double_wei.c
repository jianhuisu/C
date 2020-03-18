//
// Created by guangsujiqiang on 3/17/20.
//

#define CONCAT(a, b) a##b
// !!!! 注意 变量宏定义 CONCAT("ddd",ccccc) 中传参 使用了错误的方式 实参只能是 不被双引号包裹的字符串
CONCAT(ddd,cccc)

/*

[guangsujiqiang@su-ct7 string]$>cpp double_wei.c
# 1 "double_wei.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "double_wei.c"






dddcccc


*/