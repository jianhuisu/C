#include <stdio.h>

struct name{
    char lib[19];
    char str[19];
    // 匿名结构
    struct {
        char gg[4];
        char cc[4];
    };
};

void main(void)
{
    struct name jianhui = {
        "anonymous",
        "anonymous",
        {"gg","cc"}
    };

    puts(jianhui.lib);
    puts(jianhui.str);

    puts(jianhui.gg);
    puts(jianhui.cc);
}