//
// Created by 苏建辉 on 2020/1/11.
//
#include <stdio.h>

int main(int argc,char * argv[])
{
    char name[15] = "sujianhui_0";
    int i;
    for(i = 0;i<15;i++){
        printf(" char is : %c , dec code is : %d \n ",name[i],name[i]);
    }

    printf(" decimal code is :[ int 0 => %d] [int 1 => %d ] [ int 2 => %d ] [char 0 => %d ] [char \\0 => %d ]\n ",0,1,2,'0','\0');

    return 0;
}
/*

[sujianhui@ string]$>gcc -Wall init_string.c && ./a.out
char is : s , dec code is : 115
char is : u , dec code is : 117
char is : j , dec code is : 106
char is : i , dec code is : 105
char is : a , dec code is : 97
char is : n , dec code is : 110
char is : h , dec code is : 104
char is : u , dec code is : 117
char is : i , dec code is : 105
char is : _ , dec code is : 95
char is : 0 , dec code is : 48
 // 注意这里  字符串的末尾自动添加 \0 (alias: Null字符) 字符，占据一个内存单元，其余未显式初始化的内存单元 默认初始化为 \0
 // 并且 整型数字 0 的ascii码十进制值为 0 ，注意 字符 '\0' 、'0' 与 数字 0 之间的区别
char is :  , dec code is : 0
char is :  , dec code is : 0
char is :  , dec code is : 0
char is :  , dec code is : 0

 decimal code is :[ int 0 => 0] [int 1 => 1 ] [ int 2 => 2 ] [char 0 => 48 ] [char \0 => 0 ]



 ascii decimal set

      0 nul    1 soh    2 stx    3 etx    4 eot    5 enq    6 ack    7 bel
       8 bs     9 ht    10 nl    11 vt    12 np    13 cr    14 so    15 si
      16 dle   17 dc1   18 dc2   19 dc3   20 dc4   21 nak   22 syn   23 etb
      24 can   25 em    26 sub   27 esc   28 fs    29 gs    30 rs    31 us
      32 sp    33  !    34  "    35  #    36  $    37  %    38  &    39  '
      40  (    41  )    42  *    43  +    44  ,    45  -    46  .    47  /
      // 注意下面这一行 字符0 与 nul 的区别
      48  0    49  1    50  2    51  3    52  4    53  5    54  6    55  7
      56  8    57  9    58  :    59  ;    60  <    61  =    62  >    63  ?
      64  @    65  A    66  B    67  C    68  D    69  E    70  F    71  G
      72  H    73  I    74  J    75  K    76  L    77  M    78  N    79  O
      80  P    81  Q    82  R    83  S    84  T    85  U    86  V    87  W
      88  X    89  Y    90  Z    91  [    92  \    93  ]    94  ^    95  _
      96  `    97  a    98  b    99  c   100  d   101  e   102  f   103  g
     104  h   105  i   106  j   107  k   108  l   109  m   110  n   111  o
     112  p   113  q   114  r   115  s   116  t   117  u   118  v   119  w
     120  x   121  y   122  z   123  {   124  |   125  }   126  ~   127 del


 */