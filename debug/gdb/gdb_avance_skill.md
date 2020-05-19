
##### 格式化输出显示结构体

`p  s` or `p *s` 这样显示出来的结构体，很难在调试的时候一眼捕捉到有用的信息，往往需要仔细找找。
GDB提供了格式化输出显示结构体的选项，`set print pretty off/on`，

##### 显示在h后面的10个元素

`base@length`,因此，要想显示在h后面的10个元素，可以使用`h@10`：   

    (gdb) p $12.value.str
    $13 = (zend_string *) 0x10e9de0
    (gdb) p *$12.value.str
    $14 = {
      gc = {
        refcount = 1, 
        u = {
          v = {
            type = 6 '\006', 
            flags = 7 '\a', 
            gc_info = 0
          }, 
          type_info = 1798
        }
      }, 
      h = 9223378990886268924, 
      len = 6, 
      val = "s"
    }
    (gdb) p *$12.value.str.val@6  
    $15 = "string"

