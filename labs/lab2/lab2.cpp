#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab2.h"

// Global variables accessible in Lab 2
extern "C"
{
    size_t value = -30;
}

int main(int argc, char **argv)
{
    char vals[] = {'D', 'C'};
    printf("Preparing to run first function (copying a byte)\n");
    size_t retval = first_func();
    EQ((size_t)6, retval);

    printf("Preparing to run the second function (swapping low and high)\n");
    size_t res = second_func();
    EQ_C(((char *)&res)[0], vals[0]);
    EQ_C(((char *)&res)[1], vals[1]);

    return 0;
}
