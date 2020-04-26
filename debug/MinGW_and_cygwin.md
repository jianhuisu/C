## difference between MinGW and cygwin

gcc、make这些都是linux下的工具，在windows下怎么办呢？这个不用担心，早有人帮我们弄好了，前辈们将这些linux下的工具，移植到了windows下，
现在有两种主流方案，一种是MinGW，另一种是cygwin。我们只需要安装这两种软件中的一种，就可以在windows下使用本来在linux下才能使用的工具了.

 - mingw 修改编译器,让window下的编译器把诸如fork的调用翻译成等价的形式
 - cygwin 修改库,让window提供一个类似unix提供的库,他们对程序的接口如同unix一样,而这些库,当然是由win32的API实现的

我选择了cygwin

### reference material

 - https://blog.csdn.net/embededvc/article/details/6829010
 - https://www.cnblogs.com/grey-wolf/p/12637730.html
