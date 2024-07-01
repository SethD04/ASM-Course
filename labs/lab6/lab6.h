// Function prototypes
extern "C"
{
    size_t get_flags(void);
    size_t first_func(void);
    size_t second_func(void);
    size_t third_func(void);
}

#define CF_SET(x) x &(1 << 0)
#define OF_SET(x) x &(1 << 11)

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
#define T(x)                                                             \
    do                                                                   \
    {                                                                    \
        if (x)                                                           \
            success("[*] Success!\n");                                   \
        else                                                             \
            danger("[x] Test Failed! Value did not evaluate to true\n"); \
    } while (0)
