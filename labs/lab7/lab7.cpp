#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab7.h"

char buf[] = "Has anyone ever been as far as decided to look more like";
size_t values[] = {10, 20, 30, 40, 50};

int main(int argc, char **argv)
{
    printf("Preparing to run first function (Larger Number)\n");
    size_t result = first_func(2, 2);
    EQ(VALUES_EQUAL, result);
    result = first_func(2, 1);
    EQ(FIRST_GREATER, result);
    result = first_func(10, 20);
    EQ(SECOND_GREATER, result);

    printf("Preparing to run second function (Sum)\n");
    result = second_func(values, (size_t)5);
    EQ((size_t)150, result);

    printf("Preparing to run third function (String length)\n");
    result = third_func(buf);
    EQ(strlen(buf), result);

    return 0;
}
