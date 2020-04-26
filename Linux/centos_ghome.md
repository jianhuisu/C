## centos7.2 + ghome

### 全角和半角是什么？有什么区别

其实全角和半角是针对中文输入法输入字符的不同状态
全角模式：输入一个字符占用2个字符
半角模式：输入一个字符占用1个字符

全角模式输出的字符和半角不同,但是汉字的话2个模式都是占用2个字符
某些特殊的函数，比如命令就不能用全角输入

we common use : 半角模式

### 解决Linux CLion不能输入中文的问题

搜狗中文输入在Linux下其他程序中均可正常使用，Linux下的CLion无法使用中文输入法。 这与CLion的程序应用环境有关系。在clion.sh配置文件中尾部加入下面3个选项：

    export GTK_IM_MODULE=fcitx
    export QT_IM_MODULE=fcitx
    export XMODIFIERS=@im=fcitx\



### desktop quick icon under ghome

    [sujianhui@nlp applications]$ pwd
    /usr/local/share/applications
    [sujianhui@nlp applications]$ cat jetbrains-clion.desktop
    [Desktop Entry]
    Version=1.0
    Type=Application
    Name=CLion
    Icon=/usr/local/clion-2020.1/bin/clion.svg
    Exec="/usr/local/clion-2020.1/bin/clion.sh" %f
    Comment=A cross-platform IDE for C and C++
    Categories=Development;IDE;
    Terminal=false
    StartupWMClass=jetbrains-clion

