// Function prototypes
extern "C" float out1;
extern "C" double out2;
extern "C" size_t first_func(void);
extern "C" size_t second_func(int);

#define PRINT_COLOR(x) "\x1b[" x "m"
#define COLOR_NORMAL PRINT_COLOR("0")
#define COLOR_RED PRINT_COLOR("31")
#define COLOR_GREEN PRINT_COLOR("32")
#define COLOR_YELLOW PRINT_COLOR("33")

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

#define close(fmt, args...)                     \
    do                                          \
    {                                           \
        printf_color(COLOR_YELLOW fmt, ##args); \
    } while (0)

// Macro for checking equality
#define EQ(x, y)                                                                      \
    do                                                                                \
    {                                                                                 \
        if (x == y)                                                                   \
            success("[*] Success! Values are equal!\n");                              \
        else                                                                          \
            danger("[x] Test Failed! Value %.8g does not match value %.8g!\n", x, y); \
    } while (0)

#define EQS(x, y)                                                                 \
    do                                                                            \
    {                                                                             \
        if (x == y)                                                               \
            success("[*] Success! Values are equal!\n");                          \
        else                                                                      \
            danger("[x] Test Failed! Value %u does not match value %u!\n", x, y); \
    } while (0)

#define CLOSE(x, y)                                                               \
    do                                                                            \
    {                                                                             \
        if ((x - y) <= 1000)                                                      \
            success("[*] Success! values %zu and %zu are close!\n", x, y);        \
        else                                                                      \
            danger("[x] Test failed! Values %zu and %zu are not close!\n", x, y); \
    } while (0)
