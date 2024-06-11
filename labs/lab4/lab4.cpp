#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab4.h"

extern "C"
{
    size_t value = 30;
};

int main(int argc, char **argv)
{
    printf("Preparing to run first function (stack allocation)\n");
    size_t retval = first_func();
    EQ((size_t)0x20, retval);

    printf("Preparing to run second function (register preservation)\n");
    retval = second_func();
    EQ((size_t)1, retval);
    EQ((size_t)6, value);

    return 0;
}
