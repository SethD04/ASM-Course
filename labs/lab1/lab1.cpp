#include <stdio.h>
#include <stdlib.h>

#include "lab1.h"

// Global variables accessible in Lab 1
extern "C"
{
    unsigned long value = 0;
    unsigned long buf[] = {10, 20, 30, 40};
    unsigned long val1 = 10;
    unsigned long val2 = 40;
}

int main(int argc, char **argv)
{
    printf("Preparing to run the first test (moving a value to a register)\n");
    unsigned long result1 = first_func();
    EQ(result1, (unsigned long)42);

    printf("Preparing to run the second test (moving the contents of one register into another)\n");
    unsigned long result2 = second_func();
    EQ(result2, (unsigned long)80);

    printf("Preparing to run the third test (moving a value from a register to memory)\n");
    third_func();
    EQ(value, (unsigned long)32);

    value = 255;
    printf("Preparing to run the fourth test (moving a value from memory into a register)\n");
    unsigned long result3 = fourth_func();
    EQ(result3, (unsigned long)255);

    printf("Preparing to run the fifth test (using lea to calculate the next item in a list)\n");
    unsigned long result4 = fifth_func();
    EQ(result4, buf[2]);

    printf("Preparing to run the sixth test (using xchg to swap two array values)\n");
    sixth_func();
    EQ(val2, (unsigned long)10);
    EQ(val1, (unsigned long)40);

    return 0;
}
