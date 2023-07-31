#include "logger.hpp"

namespace zifmann::logger::core {

void init_logger(const std::string &path) { filepath = path; }

void log(const logger_level level, const std::string &format,
         const std::string &filename, const int line_number, ...) {
    va_list args;
    va_start(args, line_number);
    std::stringstream string_builder;
    auto t = time(nullptr);
    tm *ltm = localtime(&t);
    switch (level) {
        case logger_level::Error:
            string_builder << RED << "Error**" << RESET;
            break;
        case logger_level::Debug:
            string_builder << WHT << "Debug**" << RESET;
            break;
        case logger_level::Warning:
            string_builder << YEL << "Warn**" << RESET;
            break;
        case logger_level::Info:
            string_builder << BLU << "Info**" << RESET;
            break;
    }
    string_builder << "\t (" << ltm->tm_hour << ":" << ltm->tm_min << ":"
                   << ltm->tm_sec << ") ";
    string_builder << "in " << filename << ":" << line_number << ": ";
    bool format_start = false;
    for (size_t i = 0; i < format.length(); i++) {
        if (format_start) {
            switch (format[i]) {
                case '%':
                    string_builder << '%';
                    break;
                case 'i': {
                    int i = (int)va_arg(args, int);
                    string_builder << i;
                    break;
                }
                case 'h': {
                    unsigned int i = (unsigned int)va_arg(args, unsigned int);
                    string_builder << i;
                    break;
                }
                case 'u': {
                    unsigned long long i = (unsigned long long)va_arg(args, unsigned long long);
                    string_builder << i;
                    break;
                }
                case 'f':
                case 'd': {
                    double d = (double)va_arg(args, double);
                    string_builder << d;
                    break;
                }
                case 'b': {
                    int b = (int)va_arg(args, int);
                    string_builder << (b ? "true" : "false");
                    break;
                }
                case 's': {
                    const char *s = (const char *)va_arg(args, const char *);
                    string_builder << s;
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    string_builder << c;
                    break;
                }
                default:
                    log_error("Invalid format specified!");
            }
            format_start = false;
        } else {
            if (format[i] == '%')
                format_start = true;
            else
                string_builder << format[i];
        }
    }
    va_end(args);
    logs.push_back(string_builder.str());
    if (level == zifmann::logger::core::Error)
        std::cerr << string_builder.str() << "\n";
    else
        std::cout << string_builder.str() << "\n";
}

void myassert(const bool expression, const std::string &format,
              const std::string &filename, const int line_number, ...) {
    if (!expression) {
        va_list list;
        va_start(list, line_number);
        log(logger_level::Error, "Assertion Error: " + format, filename,
            line_number, list);
        va_end(list);
        exit(1);
    }
}

void dump_logs(const std::string &filepath) {
    std::stringstream path_formatter;
    auto t = time(nullptr);
    tm *ltm = localtime(&t);
    path_formatter << "log_" << ltm->tm_mday << "_" << ltm->tm_mon << "_"
                   << (ltm->tm_year + 1900) << "_" << ltm->tm_hour << "_"
                   << ltm->tm_min << "_" << ltm->tm_sec << ".txt";
    std::ofstream logfile(path_formatter.str(), std::ios::out);
    for (auto &str : logs) {
        logfile << str << "\n";
    }
    logfile.close();
}

}  // namespace zifmann::logger::core
