#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab5.h"

extern "C"
{
    unsigned char value[] = {0x9f, 0xb9, 0xaf, 0xaf, 0xa9, 0xbf, 0xbf, 0xed};
    char second_value[] = {'e', 's', 's', '!', 'S', 'u', 'c', 'c'};
    char *value_outbuf = NULL;
    char *second_outbuf = NULL;
};

#define VALUE_ALLOC_SIZE 24

int main(int argc, char **argv)
{

    // allocate memory for value_outbuf
    value_outbuf = (char *)malloc(VALUE_ALLOC_SIZE);
    // check if we successfully allocated memory
    if (NULL == value_outbuf)
    {
        printf("Out of memory, please try running again! :(\n");
        return -1;
    }

    // allocate memory for second_outbuf
    second_outbuf = (char *)malloc(VALUE_ALLOC_SIZE);
    // check if we successfully allocated memory
    if (NULL == second_outbuf)
    {
        printf("Out of memory, please try running again! :(\n");
        return -2;
    }

    // Clear recently allocated memory
    memset(value_outbuf, 0, VALUE_ALLOC_SIZE);
    memset(second_outbuf, 0, VALUE_ALLOC_SIZE);

    printf("Preparing to run first function (using and)\n");
    size_t retval = first_func();
    EQ((size_t)1, retval);

    printf("Preparing to run second function (using or)\n");
    retval = second_func();
    EQ((size_t)3740139503, retval);

    printf("Preparing to run third function (Zeroing RAX)\n");
    retval = third_func();
    EQ((size_t)0, retval);

    printf("Preparing to run fourth function (Bitshift Multiplication)\n");
    retval = fourth_func();
    EQ((size_t)64, retval);

    printf("Preparing to run fifth function (Bitshift Division)\n");
    retval = fifth_func();
    EQ((size_t)2, retval);

    printf("Preparing to run sixth function (rotating bytes)\n");
    sixth_func();
    printf("Rotated output: %s\n", second_outbuf);

    printf("Preparing to run seventh function (decode value)\n");
    seventh_func();
    printf("Decoded Output: %s\n", value_outbuf);

    free(second_outbuf);
    free(value_outbuf);

    return 0;
}
