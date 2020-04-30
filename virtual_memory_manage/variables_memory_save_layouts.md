## 变量的存储布局

全局变量存储 .bss .data section中
局部变量存储在stack中
使用malloc分配的内存存储在heap中

### 如何查看符号表 

    readelf -a a.out | grep -B3 -A100 'Symbol table'

### 参考资料

http://akaedu.github.io/book/ch19s03.html