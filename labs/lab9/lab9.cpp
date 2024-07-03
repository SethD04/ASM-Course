#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab9.h"

char str[] = "Super awesome test string.\0";

char *copystring(char *src, int len)
{
    char *tmp = NULL;

    if (NULL == src || 0 == len)
        return NULL;

    if (NULL == (tmp = (char *)malloc(len + 1)))
    {
        danger("[x] Allocation failed!\n");
        return tmp;
    }

    memset(tmp, 0x00, len + 1);
    memcpy(tmp, src, len);

    return tmp;
}

int main(int argc, char **argv)
{
    char *tmp = NULL;

    printf("Calling first function (printf)\n");
    first_func();

    printf("Calling the second function (function pointer)\n");
    tmp = second_func((void *)copystring, str);
    if (NULL == tmp)
    {
        danger("[x] Failed to copy string!\n");
        return -1;
    }
    EQS((int)0, strcmp(tmp, str));
    free(tmp);

    printf("Calling the third function (fibonacci)\n");
    EQ((size_t)55, third_func(10));

    return 0;
}
