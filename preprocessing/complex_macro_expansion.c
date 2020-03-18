//
// Created by guangsujiqiang on 3/18/20.  复杂的宏展开步骤
//

#define sh(x) printf("n" #x "=%d, or %d\n",n##x,alt[x])
#define sub_z  26
sh(sub_z)

// 这个是cpp执行之前我的猜测结果 printf("n" "26" "=%d, or %d\n",n26,alt[26])
// 这个是实际执行结果           printf("n" "sub_z" "=%d, or %d\n",nsub_z,alt[26])

/*


 sh(sub_z)要用sh(x)这个宏定义来展开，形参x对应的实参是sub_z，替换过程如下：

	1 #x要替换成 "sub_z"
	2 n##x要替换成 nsub_z
	3 除了带#和##运算符的参数之外，其它参数在替换之前要对实参本身做充分的展开(这一句非常重要)，所以应该先把sub_z展开成26再替换到alt[x]中x的位置。
	4 现在展开成了printf("n" "sub_z" "=%d, or %d\n",nsub_z,alt[26])，所有参数都替换完了，
      这时编译器会再扫描一遍，再找出可以展开的宏定义来展开，假设nsub_z或alt是变量式宏定义，则会进一步展开。

 */


#define x 3
#define f(a) f(x * (a))
#undef x

#define x 2
#define g f
#define t(a) a

t(t(g)(0) + t)(1);



/*

	先把g展开成f再替换到#define t(a) a中，得到t(f(0) + t)(1);。

	根据#define f(a) f(x * (a))，得到t(f(x * (0)) + t)(1);。

	把x替换成2，得到t(f(2 * (0)) + t)(1);。注意，(很重要 禁止递归展开 / )

 		一开始定义x为3，但是后来用#undef x取消了x的定义，又重新定义x为2。当处理到t(t(g)(0) + t)(1);这一行代码时x已经定义成2了，所以用2来替换。
 		还要注意一点，现在得到的t(f(2 * (0)) + t)(1);中仍然有f，但不能再次根据#define f(a) f(x * (a))展开了，f(2 * (0))就是由展开f(0)得到的，
 		这里面再遇到f就不展开了，这样规定可以避免无穷展开（类似于无穷递归），因此我们可以放心地使用递归定义，例如#define a a[0]，#define a a.member等。

	根据#define t(a) a，最终展开成f(2 * (0)) + t(1);。这时不能再展开t(1)了，因为这里的t就是由展开t(f(2 * (0)) + t)得到的，所以不能再展开了。


 */


