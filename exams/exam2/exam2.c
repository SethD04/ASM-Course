#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exam2.h"

char *buf[100];
float *tempfloat1;
float *tempfloat1;

void find_largest_test()
{
    size_t nums1[] = {20, 1, 4, 17, 42, 18, 49, 12};
    size_t nums2[] = {444, 11, 90, 600, 1, 22, 49, 12};
    size_t nums3[] = {0, 55, 200, 100, 32, 18, 99, 6};
    size_t nums4[] = {500, 1, 4, 17, 42, 18, 49, 12};

    // Test 1
    size_t res = find_largest(nums1, sizeof(nums1) / sizeof(size_t));
    IS_LARGEST(res, nums1, sizeof(nums1) / sizeof(size_t));

    // Test 2
    res = find_largest(nums2, sizeof(nums2) / sizeof(size_t));
    IS_LARGEST(res, nums2, sizeof(nums2) / sizeof(size_t));

    // Test 3
    res = find_largest(nums3, sizeof(nums3) / sizeof(size_t));
    IS_LARGEST(res, nums3, sizeof(nums3) / sizeof(size_t));

    // Test 4
    res = find_largest(nums4, sizeof(nums4) / sizeof(size_t));
    IS_LARGEST(res, nums4, sizeof(nums4) / sizeof(size_t));
}

void strlen_test()
{
    char str1[] = "abcdefg";
    char str2[] = "hello";
    char str3[] = "world";
    char str4[] = "goodbye";

    // Test 1
    size_t res = ex_strlen(str1);
    EQ(res, strlen(str1));

    // Test 2
    res = ex_strlen(str2);
    EQ(res, strlen(str2));

    // Test 3
    res = ex_strlen(str3);
    EQ(res, strlen(str3));

    // Test 4
    res = ex_strlen(str4);
    EQ(res, strlen(str4));
}

void copy_reverse_test()
{
    char str1[] = "abcdefghi";
    char str2[] = "hello world!";
    char str3[] = "goodbye see ya";

    char dbuf[255] = {0};

    // Test 1
    memset(dbuf, 0, sizeof(dbuf));
    copy_reverse(str1, dbuf, strlen(str1));
    int res = memcmp("ihgfedcba", dbuf, strlen(str1));
    EQ((size_t)'i', (size_t)dbuf[0]);
    EQ((size_t)'c', (size_t)dbuf[6]);
    EQ((size_t)0, (size_t)res);

    // Test 2
    memset(dbuf, 0, sizeof(dbuf));
    copy_reverse(str2, dbuf, strlen(str2));
    res = memcmp("!dlrow olleh", dbuf, strlen(str2));
    EQ((size_t)'!', (size_t)dbuf[0]);
    EQ((size_t)'e', (size_t)dbuf[10]);
    EQ((size_t)0, (size_t)res);

    // Test 3
    memset(dbuf, 0, sizeof(dbuf));
    copy_reverse(str3, dbuf, strlen(str3));
    res = memcmp("ay ees eybdoog", dbuf, strlen(str3));
    EQ((size_t)'a', (size_t)dbuf[0]);
    EQ((size_t)'g', (size_t)dbuf[13]);
    EQ((size_t)0, (size_t)res);
}

void find_min_test()
{
    int x = 42;
    int y = 10;
    int res = find_min(x, y);
    EQ_I(y, res);

    x = 30;
    y = 21;
    res = find_min(x, y);
    EQ_I(y, res);

    x = 0;
    y = 21;
    res = find_min(x, y);
    EQ_I(x, res);
}

void swap_func_test()
{
    float first[] = {5.0, 1.1, 8.2};
    float second[] = {1.4, 7.2, 3.9};

    swap_func(first, second);
    EQ_F(first[0], 1.4);
    EQ_F(second[0], 5.0);

    swap_func(first + 1, second + 1);
    EQ_F(first[1], 7.2);
    EQ_F(second[1], 1.1);

    swap_func(first + 2, second + 2);
    EQ_F(first[2], 3.9);
    EQ_F(second[2], 8.2);
}

int main(int argc, char **argv)
{
    unsigned long res = 0;
    printf("Preparing to run the first test (ex_strlen)\n");
    strlen_test();

    printf("Preparing to run the second test (find_largest)\n");
    find_largest_test();

    printf("Preparing to run the third test (copy_reverse)\n");
    copy_reverse_test();

    printf("Preparing to run the fourth test (find_min)\n");
    find_min_test();

    printf("Preparing to run the fifth test (swap_func)\n");
    swap_func_test();

    return 0;
}
