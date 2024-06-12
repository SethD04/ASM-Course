#include <stdio.h>
#include <stdlib.h>

#include "lab3.h"

int main(int argc, char **argv)
{
    printf("Preparing to run the first function (adding values)\n");
    size_t retval = first_func();
    EQ((size_t)20, retval);

    printf("Preparing to run the second function (subtracting values)\n");
    retval = second_func();
    EQ((size_t)10, retval);

    printf("Preparing to run the third function (multiplying)\n");
    retval = third_func();
    EQ((size_t)100, third_func());

    printf("Preparing to run the fourth function (division)\n");
    retval = fourth_func();
    EQ((size_t)6, fourth_func());

    printf("Preparing to run the fifth function (remainder)\n");
    retval = fifth_func();
    EQ((size_t)1, fifth_func());

    return 0;
}
