//
// Created by guangsujiqiang on 1/9/20.
//
#include <stdio.h>
#include <math.h>

void main(void)
{
    double pi=3.1416;
    printf(" %f \n",sin(pi/2));
}

/*
    [guangsujiqiang@su-ct7 func_call]$>gcc math.c
    /tmp/ccqbYX2i.o: In function `main':
    math.c:(.text+0x28): undefined reference to `sin'
    collect2: error: ld returned 1 exit status

    [guangsujiqiang@su-ct7 func_call]$>gcc math.c -lm
    [guangsujiqiang@su-ct7 func_call]$>./a.out
    1.000000

 */

