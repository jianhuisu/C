## 预处理

    #define STR "hello,"\
        "world"
    #include <stdio.h>
    
    int main(int argc,char ** argv)
    {
        printf(" %s \n",STR);
        return 0;
    }
    
展开
    
    gcc -E test_expand.c -o test_expand.i
    
下面是展开后的部分内容

    # 1 "test_expand.c"
    # 1 "<built-in>"
    # 1 "<command-line>"
    # 1 "/usr/include/stdc-predef.h" 1 3 4
    # 1 "<command-line>" 2
    # 1 "test_expand.c"
    
    
    
    
    ... ... 
    
    # 1 "/usr/include/stdio.h" 1 3 4
    # 27 "/usr/include/stdio.h" 3 4
    # 1 "/usr/include/features.h" 1 3 4
    # 375 "/usr/include/features.h" 3 4
    # 1 "/usr/include/sys/cdefs.h" 1 3 4
    # 392 "/usr/include/sys/cdefs.h" 3 4
    # 1 "/usr/include/bits/wordsize.h" 1 3 4
    # 393 "/usr/include/sys/cdefs.h" 2 3 4
    # 376 "/usr/include/features.h" 2 3 4
    # 399 "/usr/include/features.h" 3 4
    # 1 "/usr/include/gnu/stubs.h" 1 3 4
    # 10 "/usr/include/gnu/stubs.h" 3 4
    # 1 "/usr/include/gnu/stubs-64.h" 1 3 4
    # 11 "/usr/include/gnu/stubs.h" 2 3 4
    # 400 "/usr/include/features.h" 2 3 4
    # 28 "/usr/include/stdio.h" 2 3 4
    
    
    
    
    
    # 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/stddef.h" 1 3 4
    # 212 "/usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/stddef.h" 3 4
    typedef long unsigned int size_t;
    # 34 "/usr/include/stdio.h" 2 3 4
    
    
    extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
    # 913 "/usr/include/stdio.h" 3 4
    extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
    
    
    
    extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
    
    
    extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
    # 943 "/usr/include/stdio.h" 3 4
    
    # 8 "test_expand.c" 2
    
    int main(int argc,char ** argv)
    {
     printf(" %s \n","hello," "world");
     return 0;
    }

预处理之后的stdout中仍然包含 `#` 但是Macro已经被全部展开

