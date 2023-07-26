#ifndef ZIFMANN_LOGGER_HPP
#define ZIFMANN_LOGGER_HPP


#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <stdarg.h>
#include <iostream>

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)
#define log_debug(message, ...) log(zifmann::logger::core::logger_level::Debug, message, __FILENAME__, __LINE__, ##__VA_ARGS__)
#define log_error(message, ...) log(zifmann::logger::core::logger_level::Error, message, __FILENAME__, __LINE__, ##__VA_ARGS__)
#define log_info(message, ...) log(zifmann::logger::core::logger_level::Info, message, __FILENAME__, __LINE__, ##__VA_ARGS__)
#define log_warn(message, ...) log(zifmann::logger::core::logger_level::Warning, message, __FILENAME__, __LINE__, ##__VA_ARGS__)
#define log_assert(condition, message, ...) assert(condition, message, __FILENAME__, __LINE__, ##__VA_ARGS__)
#define dump(path) zifmann::logger::core::dump_logs(path)


namespace zifmann::logger::core {

    enum logger_level {
        Warning,
        Debug,
        Error,
        Info
    };

    static std::vector<std::string> logs;
    static std::string filepath;

    // @param level The logger level for the current log
    // @param format The format of the string to built from the given arguments
    // @param filename The name of the file from where the function is being called
    // @param line_number The line number of the line calling this function
    void log(const logger_level level, const std::string &format, const std::string &filename, const int line_number, ...);

    void myassert(const bool expression, const std::string &format, const std::string &filename, const int line_number, ...);

    // @param filepath The full path of the file where to dump the logs
    void dump_logs(const std::string &filepath);

    void init_logger(const std::string &path);

    #define BLK "\e[1;30m"
    #define RED "\e[1;31m"
    #define GRN "\e[1;32m"
    #define YEL "\e[1;33m"
    #define BLU "\e[1;34m"
    #define MAG "\e[1;35m"
    #define CYN "\e[1;36m"
    #define WHT "\e[1;37m"
    #define RESET "\e[0m"


}

#endif
