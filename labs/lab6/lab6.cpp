#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab6.h"

int main(int argc, char **argv)
{
    size_t flags = 0;
    printf("Preparing to run first function (Carrying)\n");
    first_func();
    flags = get_flags();
    T(CF_SET(flags));

    flags = 0;
    printf("Preparing to run second function (Overflow)\n");
    second_func();
    flags = get_flags();
    T(OF_SET(flags));

    flags = 0;
    printf("Preparing to run third function (Setting both OF and CF)\n");
    third_func();
    flags = get_flags();
    T(OF_SET(flags) && CF_SET(flags));

    return 0;
}
