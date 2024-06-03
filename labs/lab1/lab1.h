// Function prototypes
extern "C" unsigned long first_func(void);
extern "C" unsigned long second_func(void);
extern "C" void third_func(void);
extern "C" unsigned long fourth_func(void);
extern "C" unsigned long fifth_func(void);
extern "C" void sixth_func(void);

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
