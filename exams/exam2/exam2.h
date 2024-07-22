#include <string.h>
#include <math.h>

// Function prototypes
extern size_t ex_strlen(char *string);
extern void copy_reverse(char *string, char *buff, size_t len);
extern size_t find_largest(size_t *, size_t);
extern int find_min(int, int);
extern void swap_func(float *, float *);

#define PRINT_COLOR(x) "\x1b[" x "m"
#define COLOR_NORMAL PRINT_COLOR("0")
#define COLOR_RED PRINT_COLOR("31")
#define COLOR_GREEN PRINT_COLOR("32")

#define IS_LARGEST(c1, ar, sz)              \
    do                                      \
    {                                       \
        size_t lg = ar[0];                  \
        for (size_t i = 1; i < sz; ++i)     \
            lg = (ar[i] > lg) ? ar[i] : lg; \
        EQ(lg, c1);                         \
    } while (0)

#define printf_color(fmt, args...)             \
    do                                         \
    {                                          \
        printf(fmt "\n" COLOR_NORMAL, ##args); \
    } while (0)

#define success(fmt, args...)                  \
    do                                         \
    {                                          \
        printf_color(COLOR_GREEN fmt, ##args); \
    } while (0)

#define danger(fmt, args...)                 \
    do                                       \
    {                                        \
        printf_color(COLOR_RED fmt, ##args); \
    } while (0)

// Macro for checking equality
#define EQ(x, y)                                                                  \
    do                                                                            \
    {                                                                             \
        if (x == y)                                                               \
            success("[*] Success! Values are equal!");                            \
        else                                                                      \
            danger("[x] Test Failed! Value %zu does not match value %zu!", x, y); \
    } while (0)

// Macro for checking equality
#define EQ_I(x, y)                                                              \
    do                                                                          \
    {                                                                           \
        if (x == y)                                                             \
            success("[*] Success! Values are equal!");                          \
        else                                                                    \
            danger("[x] Test Failed! Value %u does not match value %u!", x, y); \
    } while (0)

// Macro for checking equality
#define EQ_F(x, y)                                                              \
    do                                                                          \
    {                                                                           \
        if (round(x) == round(y))                                               \
            success("[*] Success! Values are equal!");                          \
        else                                                                    \
            danger("[x] Test Failed! Value %f does not match value %f!", x, y); \
    } while (0)

// Macro for checking equality
void STR_EQ(char *x, char *y)
{
    if (x == NULL || y == NULL)
    {
        danger("[x] Test Failed! Value x does not match value y!");
        return;
    }

    size_t res = strcmp(x, y);
    if (res == 0)
    {
        success("[*] Success! Values are equal!");
    }
    else
    {
        danger("[x] Test Failed! Value %s does not match value %s!", x, y);
    }
}
