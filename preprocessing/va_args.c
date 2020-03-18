//
//  宏定义中使用可变参数
//

// 函数式宏定义也可以带可变参数，同样是在参数列表中用...表示可变参数
// 在宏定义中，可变参数的部分用__VA_ARGS__表示，实参中对应...的几个参数可以看成一个参数替换到宏定义中__VA_ARGS__所在的地方。
#define showlist(...) printf(#__VA_ARGS__)
// 当遇到 showlist(...) 传递可变参数时 ，macro 展开为 printf(...) 格式 ,并将实参转化为字符串 , 最终结果类似于 printf("$__VA_ARGS")


#define report(test, ...) ((test)?printf(#test):\
	printf(__VA_ARGS__))
// 这一条函数宏中的 printf(__VA_ARGS__) 为一个实体函数调用  __VA_ARGS__ 直接原样替换 不做类型转化

showlist(The first, second, and third items.);
report(x>y, "x is %d but y is %d", x, y);

/*

[guangsujiqiang@su-ct7 string]$>cpp va_args.c
# 1 "va_args.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "va_args.c"



printf("The first, second, and third items.");
((x>y)?printf("x>y"): printf("x is %d but y is %d", x, y));

 */