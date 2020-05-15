## 预处理

expand macro has two ways :
    
 - `gcc -E test_expand.c -o test_expand.i` : `gcc -E` check grammer 
 - `cpp test_expand.c` : `cpp` not check grammer  
    

source code `main.c` 
    
    # define CG(v) (compiler_globals.v)
    # define EG(v) (executor_globals.v)
    # define PG(v) (core_globals.v)
    # define SG(v) (sapi_globals.v)
        
    int main(void)
    {
        if (PG(internal_encoding) && PG(internal_encoding)[0]) {
            return PG(internal_encoding);
        } else if (SG(default_charset)) {
            return SG(default_charset);
        }
    }

expand result :
  
    sujianhui@dev529> cpp php_zend_macro.c
    # 1 "php_zend_macro.c"
    # 1 "<built-in>"
    # 1 "<command-line>"
    # 1 "/usr/include/stdc-predef.h" 1 3 4
    # 1 "<command-line>" 2
    # 1 "php_zend_macro.c"
    
    int main(void)
    {
        if ((core_globals.internal_encoding) && (core_globals.internal_encoding)[0]) {
            return (core_globals.internal_encoding);
        } else if ((sapi_globals.default_charset)) {
            return (sapi_globals.default_charset);
        }
    }


