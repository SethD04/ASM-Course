#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "lab10.h"

size_t gettsc()
{
    size_t lowbits, highbits;
    asm("rdtsc"
        : "=a"(lowbits), "=d"(highbits));
    return (lowbits | (highbits << 32));
}

void getvstr(char **buf)
{
    uint32_t p1, p2, p3, p4;
    char *tmp = NULL;
    if (NULL == buf)
        return;

    if (NULL == (tmp = (char *)malloc(17)))
    {
        printf("[x] Out of memory!\n");
        return;
    }
    memset(tmp, 0x00, 17);
    asm("xor %rax,%rax");
    asm("cpuid"
        : "=b"(p1),               // rbx
          "=d"(p2),               // rdx
          "=c"(p3),               // rcx
          "=a"(p4));              // rax
    memcpy(tmp, &p1, sizeof(p1)); // tmp is rdi
    memcpy((tmp + 4), &p2, sizeof(p2));
    memcpy((tmp + 8), &p3, sizeof(p3));
    memcpy((tmp + 12), &p4, sizeof(p4));
    *buf = tmp;
}

int main(int argc, char **argv)
{
    size_t first = 0;
    size_t second = 0;
    char *tmp = NULL;
    char idbuf[20] = {0};

    printf("Preparing to run first_func (Get timestamp)\n");
    first = gettsc();
    asm("xor %rax,%rax");
    second = first_func();
    CLOSE(second, first);

    getvstr(&tmp);
    if (NULL == tmp)
    {
        printf("[x] Allocation failed!\n");
        return -1;
    }

    printf("Preparing to run second_func (Get vendor string)\n");
    second_func(idbuf, tmp);
    EQ((size_t)0, (size_t)strcmp(idbuf, tmp));
    printf("Your vendor ID string is: %s\n", idbuf);
    free(tmp);

    return 0;
}
