#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab8.h"

#define BUFF_SIZE (size_t)256

int main(int argc, char **argv)
{
    {
        char buf1[BUFF_SIZE] = {0};
        char buf2[BUFF_SIZE] = {0};

        memset(buf1, 0x41, BUFF_SIZE);
        printf("Preparing to run first function (Initialize Memory)\n");  
        first_func(buf2, 0x41, BUFF_SIZE);
        EQ((int)0, memcmp(buf1, buf2, BUFF_SIZE));
    }
    {
        char fbuf[BUFF_SIZE + 1] = {0};
        char sbuf[BUFF_SIZE + 1] = {0};

        memset(sbuf, 0x41, BUFF_SIZE);
        printf("Preparing to run second function (Copy memory)\n");
        second_func(fbuf, sbuf, BUFF_SIZE);
        EQ((int)0, memcmp(fbuf, sbuf, BUFF_SIZE));
    }
    {
        char strbuf[] = "abcdef1234";
        printf("Preparing to run third function (String length)\n");
        EQ((int)strlen(strbuf), (int)third_func(strbuf));
    }

    return 0;
}
