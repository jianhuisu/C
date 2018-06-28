第四章 语句
    c 的语句与php的语句结构基本一致 所以权当复习一下

if else

if(express)
{
    ; /* 这是一个空语句*/
}

while( express )
{
    statement

}

在 while 的循环体中 使用 break 语句 永久退出循环
在 while 的循环体中 使用 continue 语句 退出当前循环 执行 express 判断

for

for(express1;express2;express3)
{
    statement;
}

express1 初始化部分  只在循环开始时执行一次
express2 条件部分    循环体每次执行之前调用
express3 调整部分    条件部分执行之前调用

do while
switch

switch 语句书中表述的逻辑非常清晰 这里引用一下

express 的结果必须是整形值

case 标签并不是把 语句列表划分为几部分 而是确定语句列表的 进入点 而已
如下 express 值为 3 时  ，从 case 3 进入语句列表开始执行 一直贯穿至语句列表末尾（case6：statement6）

switch(express)
{
    case 1 :
    case 2 :
    case 3 :
        statement 3
    case 4 :
    case 5 :
    case 6 :
        statement 6
    default:
}

那么如何阻止执行贯穿呢 这里引出 break 的定义
break：划分语句列表为不同部分

备注：每个switch 都要有 default 子句;

goto

goto 语句标签;

语句标签定义:
    标识符:
    example

    goto FUNC_END;
        ...

    FUNC_END:
        printf("jump to here");

goto 语句使用场景 跳出多层循环
出于程序异常反馈角度 作者建议我们尽量避免使用 goto 语句