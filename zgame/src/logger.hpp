/*
 * A tiny single header logging utility for c++
 * WARNING! Does not support more than 1024 characters in a single line
 * Requires >=C++ 17 but can be modified to also work on older compilers
 */

#ifndef ZIFMANN_LOGGER
#define ZIFMANN_LOGGER

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdint>

namespace zifmann::logger {
#ifdef WIN32
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#elif
#define __FILENAME__                                                         \
    (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 \
                                      : __FILE__)
#endif

inline FILE *log_file;

#define BLK "\e[1;30m"
#define RED "\e[1;31m"
#define GRN "\e[1;32m"
#define YEL "\e[1;33m"
#define BLU "\e[1;34m"
#define MAG "\e[1;35m"
#define CYN "\e[1;36m"
#define WHT "\e[1;37m"
#define RESET "\e[0m"

inline void init() {
    time_t t = time(nullptr);
    tm *ltm = localtime(&t);
    char filename[32];
    auto day = ltm->tm_mday, month = ltm->tm_mon, year = ltm->tm_year + 1900;
    snprintf(filename, 32, "logfile_%02d%02d%04d_%lu.txt", day, month, year,
             (unsigned long)t);
    static FILE *file = fopen(filename, "w");
    if (file == nullptr) fprintf(stderr, "Failed to open log file!");
    log_file = file;
}

inline void flush() {
    fflush(log_file);
    fclose(log_file);
}

inline void log(int level, const char *format, const char *filename,
                const int line_number, ...) {
    static const char *prefix[3] = {"Debug", "Warn", "Error"};
    static const char *colors[4] = {WHT, YEL, RED, RESET};
    time_t t = time(nullptr);
    tm *ltm = localtime(&t);
    int hour = ltm->tm_hour, min = ltm->tm_min, sec = ltm->tm_sec;
    int day = ltm->tm_mday, month = ltm->tm_mon, year = ltm->tm_year + 1900;
    char _format[512];
    snprintf(_format, 512, "%d-%d-%d %d-%d-%d [%s:%d] (**%s): %s\n", day, month,
             year, hour, min, sec, filename, line_number, prefix[level],
             format);
    va_list args;
    va_start(args, line_number);
    char buffer[512];
    vsnprintf(buffer, 512, _format, args);
    va_end(args);
    if (log_file) fprintf(log_file, "%s", buffer);
    fprintf(level == 2 ? stderr : stdout, "%s%s%s", colors[level], buffer, RESET);
}

#define log_debug(message, ...) \
    log(0, message, __FILENAME__, __LINE__, ##__VA_ARGS__)
#define log_warn(message, ...) \
    log(1, message, __FILENAME__, __LINE__, ##__VA_ARGS__)
#define log_error(message, ...) \
    log(2, message, __FILENAME__, __LINE__, ##__VA_ARGS__)

}  // namespace zifmann::logger

#endif
