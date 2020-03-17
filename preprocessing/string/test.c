//
// Created by guangsujiqiang on 3/17/20.
//

// # 与 形参s 之间可以由 0-n 个 Space 或者 Tab， 预处理之后会被替换为一个空格
#define STR(s) #s
// macro 展开时 会将括号内的 实参 视为一个字符串,并且自动在首尾添加双引号
STR(jianhui su)

#define STR1(s) #s
fputs(STR1(strncmp("ab\"c\0d", "abc", '\4"') == 0) STR(: @\n), s);
// 预处理之后 fputs("strncmp(\"ab\\\"c\\0d\", \"abc\", '\\4\"') == 0" ": @\n", s);

