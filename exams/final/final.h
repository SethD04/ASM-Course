#include <string.h>

#define PRINT_COLOR(x) "\x1b[" x "m"
#define COLOR_NORMAL PRINT_COLOR("0")
#define COLOR_RED PRINT_COLOR("31")
#define COLOR_GREEN PRINT_COLOR("32")

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
#define EQ(x, y)                                                                    \
    do                                                                              \
    {                                                                               \
        if (x == y)                                                                 \
            success("[*] Success! Values are equal!\n");                            \
        else                                                                        \
            danger("[x] Test Failed! Value %zu does not match value %zu!\n", x, y); \
    } while (0)

// Macro for checking equality
#define EQ_I(x, y)                                                                         \
    do                                                                                     \
    {                                                                                      \
        if (x == y)                                                                        \
            success("[*] Success! Values are equal!\n");                                   \
        else                                                                               \
            danger("[x] Test Failed! Value %d does not match expected value %d!\n", x, y); \
    } while (0)

// Macro for checking equality
#define VALID_FD(x)                                                                \
    do                                                                             \
    {                                                                              \
        if (x > 0)                                                                 \
            success("[*] Successfully returned file descriptor!\n");               \
        else                                                                       \
            danger("[x] Test Failed! Value %d is not valid file descriptor\n", x); \
    } while (0)

// Macro for checking equality
void STR_EQ(char *x, char *y)
{
    printf("here\n");
    if (x == NULL || y == NULL)
    {
        danger("[x] Test Failed! Value x does not match value y!\n");
        return;
    }
    printf("her2\n");

    size_t res = strcmp(x, y);
    printf("her3\n");

    if (res == 0)
    {
        success("[*] Success! Values are equal!\n");
    }
    else
    {
        danger("[x] Test Failed! Value %s does not match value %s!\n", x, y);
    }
}
