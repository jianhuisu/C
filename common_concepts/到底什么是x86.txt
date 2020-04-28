下载rpm包的时候经常会看见 x86_32、x86_64、x86 、x64、noarch 这些后缀，看着头疼，这里区分一下

x86是一种CPU指令集的泛称(有些人会称呼为x86架构 世上本没有路 走的人多了,也就成了路)
CPU架构是CPU厂商给属于同一系列的CPU产品定的一个规范，主要目的是为了区分不同类型CPU的重要标示。

    x86是指intel的开发的一种32位指令集，从386开始时代开始的，一直沿用至今，是一种CISC指令集，
所有intel早期的cpu，amd早期的cpu都支持这种指令集(intel与AMD渊源颇深)。

    x84_64是x86指令集CPU开始迈向64位的时候，有两种选择：
        1、向下兼容x86
        2、完全重新设计指令集，不兼容x86

    此时，intel的竞争对手AMD抢跑，比Intel率先制造出了商用的兼容x86的CPU，AMD称之为AMD64，
    抢了64位PC的第一桶金，得到了用户的认同。而Intel则选择了设计一种不兼容x86的全新x64位指令集，
    称之为IA-64，但是比AMD晚了一步，由于IA-64的发展不好，所以被迫开始支持AMD64的指令集，
    但是换了个名字，叫x86_64，表示是x86指令集的64扩展，大概是不愿意承认AMD先设计出来。
    ！！所以 x86_64,x64,AMD64基本上是同一个东西！！
    我们现在用的intel/AMD的PC机的CPU基本上都是x86_64，注意区别于移动设备领域的处理器
　　 x86、x86_64主要的区别就是32位和64位的问题，x86中只有8个32位通用寄存器：
            eax,ebx,ecx，edx, ebp, esp, esi, edi
    x86_64把这8个通用寄存器扩展成了64位的，并且比x86增加了若干个寄存器（好像增加了8个，变成了总共16个通用寄存器）。
    反过来，如果没有寄存器位数增加的支持，单靠64位的指令集只是徒有虚名。
    因为操作系统是基于硬件的,硬件的核心代表就是CPU,所以操作系统也有32位/64位之分
    (32位的操作系统可以运行在64位的CPU上,但是64位的操作系统无法运行在32位的CPU上)

noarch:代表跟硬件体系结构无关，代表该包与平台无关，具有良好的移植性

>> 基本上可以这么说，intel是PC领域处理器的王者，但是在移动设备市场，他却已经落后许多，
目前在移动设备市场，ARM处理器的市场份额超过90%，展露出王者之相，intel的压力也很大

CPU还会经常提到的一个名词叫体系结构

    CISC  复杂指令集
            AMD
    RISC  精简指令集
            ARM，MIPS、PowerPC(IBM)

而至于为什么要叫x86，可能跟最开始发布的CPU型号命名有关(猜测)，CPU的型号是不断迭代的，CPU的发布顺序如下（intel公司CPU发版顺序）

    i286
    i386
    i486
    i586 586处理器发布之后，为了避免与AMD公司的命名雷同，采用了全新的系列命名 Pentium (即奔腾系列)
    ...（中间穿插着赛扬系列处理器的发布）
    pentium系列陆续发布
    core系列 (酷睿系列) 陆续发布 i3 i5 i7 i9 i10 : 酷睿系列比奔腾系列性能高，功耗低
    xeon(至强)

如何查看自己的操作系统位数与CPU信息？

    使用 uname 、cat /proc/cpuinfo 、sysctl machdep.cpu 等命令

台式机/centos7

    [guangsujiqiang@su-ct7 bp]$>uname -s
    Linux
    [guangsujiqiang@su-ct7 bp]$>uname -n
    su-ct7
    [guangsujiqiang@su-ct7 bp]$>uname -r
    3.10.0-1062.4.1.el7.x86_64
    [guangsujiqiang@su-ct7 bp]$>uname -v
    #1 SMP Fri Oct 18 17:15:30 UTC 2019
    [guangsujiqiang@su-ct7 bp]$>uname -m // print the machine hardware name.
    x86_64
    [guangsujiqiang@su-ct7 bp]$>uname -p
    x86_64
    [guangsujiqiang@su-ct7 bp]$>uname -i
    x86_64
    [guangsujiqiang@su-ct7 bp]$>uname -o
    GNU/Linux

mac pro

    [sujianhui@ ~]$>uname -s
    Darwin
    [sujianhui@ ~]$>uname -n
    sujianhuideMBP
    [sujianhui@ ~]$>uname -r
    18.7.0
    [sujianhui@ ~]$>uname -v
    Darwin Kernel Version 18.7.0: Tue Aug 20 16:57:14 PDT 2019; root:xnu-4903.271.2~2/RELEASE_X86_64
    [sujianhui@ ~]$>uname -m  // print the machine hardware name.
    x86_64
    [sujianhui@ ~]$>uname -p  // print the machine processor architecture name.
    i386


参考资料

    https://www.cnblogs.com/shoshana-kong/p/10606470.html
    天梯图  http://www.mydrivers.com/zhuanti/tianti/cpu/index.html