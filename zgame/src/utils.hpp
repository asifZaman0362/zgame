#ifndef ZGAME_UTILS_FORMAT_H
#define ZGAME_UTILS_FORMAT_H

#include <string>
#include <vector>

namespace zifmann::zgame::core::utils {
namespace string {

std::string format_str(const char *format, ...);

std::vector<std::string> split_str(const std::string &, const std::string &);
std::string join_str(const std::vector<std::string> &, const std::string &);

}  // namespace string
}  // namespace zifmann::zgame::core::utils

#endif