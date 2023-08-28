#include "utils.hpp"

#include <cstdarg>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>

namespace zifmann::zgame::core::utils {
namespace string {

std::string format_str(const char* format, ...) {
    va_list arglist;
    va_start(arglist, format);
    char target[256];
    sprintf(target, format, arglist);
    va_end(arglist);
    return std::string(target);
}

std::vector<std::string> split_str(const std::string& string,
                                   const std::string& delimiter) {
    std::vector<std::string> pieces;
    size_t pos = 0;
    size_t n = delimiter.length();
    while (true) {
        auto end = string.find(delimiter, pos);
        if (end == std::string::npos)
            break;
        else {
            pieces.push_back(string.substr(pos, end - pos));
            pos = end + n;
        }
    }
    if (pos < string.length()) {
        pieces.push_back(string.substr(pos, string.length() - 1));
    }
    return pieces;
}

std::string join_str(const std::vector<std::string>& pieces,
                     const std::string& joiner) {
    std::stringstream stream;
    for (auto& piece : pieces) {
        stream << piece;
        if (piece != pieces.back()) stream << joiner;
    }
    return stream.str();
}

}  // namespace string

Signature SignatureHelper(int count, ...) {
    va_list args;
    va_start(args, count);
    Signature signature;
    for (int i = 0; i < count; i++) {
        size_t id = va_arg(args, size_t);
        signature.set(id, true);
    }
    va_end(args);
    return signature;
}

}  // namespace zifmann::zgame::core::utils
