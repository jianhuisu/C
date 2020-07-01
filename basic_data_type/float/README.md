## 浮点数

### 浮点数不适合进行精确比较

浮点数进行算术运算时会有精度损失问题.

**浮点型的精度有限，不适合用`==`运算符做精确比较**.以下代码可以说明问题：

    double i = 20.0;
    double j = i / 7.0;
    if (j * 7.0 == i)
        printf("Equal.\n");
    else
        printf("Unequal.\n");
    
不同平台的浮点数实现有很多不同之处，在我的平台上运行这段程序结果为`Unequal`，
即使在你的平台上运行结果为Equal，你再把i改成其它值试试，总有些值会使得结果为`Unequal`.

在PHP中,如果你想比较两个浮点数,可以采用如下方式

    <?php
    
        $a = round(10/3,2);
        $b = round(10/3.1,2);
        
        var_dump($a,$b);
    
    	if($a == $b){
    		echo 1;
    	} else {
    		echo 2;
    	}
    
结果为
    
    [sujianhui@nlp a_test]$ php 1.php 
    float(3.33)
    float(3.23)
    2
    
这是因为浮点数精度问题,在小数部分的末尾部分是不同的.如果需要比较,去要明确比较的位数.
比如上文中只需要保留两位小数，然后进行比较,可以采用如下方式：

    $c = (int)($a * 100)    
    $d = (int)($b * 100)
    
    if($c == $d){
        echo 1;
    } else {
        echo 2;
    }
    
输出结果为`1`,浮点数不适合比较,那么就转换为整数.
还有一种方式,使用‵bccomp‵函数.

    <?php
    
    echo bccomp('1', '2') . "\n";   // -1
    echo bccomp('1.00001', '1', 3); // 0
    echo bccomp('1.00001', '1', 5); // 1
    
    ?>
      
### C语言数字字符串与整型的相互转换

使用库函数将数字转换为字符串.
    
 - itoa()：将整型值转换为字符串。
 - ltoa()：将长整型值转换为字符串。
 - ultoa()：将无符号长整型值转换为字符串。
 - gcvt()：将浮点型数转换为字符串，取四舍五入。
 - ecvt()：将双精度浮点型值转换为字符串，转换结果中不包含十进制小数点。
 - fcvt()：指定位数为转换精度，其余同ecvt()。
 
这里的转化有很多陷阱,使用之前要查看man page.
          
    #include <stdio.h>
    #include <stdlib.h>
    
    int main(void)
    {
        int a = atoi(" 45455sdfassdf");
        printf(" %d \n ",a);
        return 0;
    }
