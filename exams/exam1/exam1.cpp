#include <stdio.h>
#include <stdlib.h>

#include "exam1.h"

// Global variables accessible in Exam 1
extern "C"
{
    int buf[] = {10, 20, 30, 40};
}

int main(int argc, char **argv)
{
    unsigned long res = 0;
    printf("Preparing to run the first test (move and add a value to a register)\n");
    res = first_func();
    EQ(res, (unsigned long)22);

    printf("Preparing to run the second test (move and subtract a value from a register)\n");
    res = second_func();
    EQ(res, (unsigned long)7);

    printf("Preparing to run the third test (moving and multiply a value from a register)\n");
    res = third_func();
    EQ(res, (unsigned long)35);

    printf("Preparing to run the fourth test (moving and dividing a value from a register)\n");
    res = fourth_func();
    EQ(res, (unsigned long)20);

    printf("Preparing to run the fifth test (using lea to calculate the next item in a list)\n");
    res = fifth_func();
    EQ((unsigned long)buf[3], (unsigned long)res); // Third element (30)

    return 0;
}
