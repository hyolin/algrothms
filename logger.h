#ifndef LOGGER_H_
#define LOGGER_H_
#include <time.h>
#include <stdio.h>
#include <stdarg.h>

enum {
    LL_DEBUG = 0,
    LL_INFO = 1,
    LL_WARN = 2,
    LL_ERROR = 3,
    LL_FATAL = 4,
};

#define LOG(level, format, ...) \
        logger(LL_##level, format, __FILE__, __LINE__, ##__VA_ARGS__)

static const char* LOG_LEVELS[] = {"DEBUG", "INFO", "WARN", "ERROR", "FATAL"};
static const char* LOG_FORMAT = "%Y-%m-%d %H:%M:%M";

void logger(size_t level, const char* format, 
            const char* filename, size_t line, ...) 
{
    char buf[32] = {0};
    time_t now;
    struct tm *tmp;

    now = time(NULL);
    tmp = localtime(&now);

    if (strftime(buf, sizeof(buf), LOG_FORMAT, tmp) == 0) {
        fprintf(stderr, "strftime return 0");
        exit(-1);
    }
    char s[128];
    va_list args;
    va_start(args, format);
    vsprintf(s, format, args);
    va_end(args);
    switch (level) {
        case LL_DEBUG:
        case LL_INFO:
        case LL_WARN:
            fprintf(stdout, "%s %s[line: %d] %s %s\n", \
                    buf, filename, line, LOG_LEVELS[level], s);
            break;
        case LL_ERROR:
            fprintf(stderr, "%s %s[line: %d] %s %s\n", \
                    buf, filename, line, LOG_LEVELS[level], s);
            break;
        case LL_FATAL:
            fprintf(stderr, "%s %s[line: %d] %s %s\n", \
                    buf, filename, line, LOG_LEVELS[level], s);
            exit(-1); 
    }
}

#endif
