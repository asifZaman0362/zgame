#ifndef ZGAME_UTILS_FORMAT_H
#define ZGAME_UTILS_FORMAT_H

#include <string>
#include <vector>

#include "ecs.hpp"

namespace zifmann::zgame::core::utils {
namespace string {

std::string format_str(const char *format, ...);

std::vector<std::string> split_str(const std::string &, const std::string &);
std::string join_str(const std::vector<std::string> &, const std::string &);

}  // namespace string

Signature SignatureHelper(int count, ...);

#ifdef __GNUC__
#define PACK(__Declaration__) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK(__Declaration__) \
    __pragma(pack(push, 1)) __Declaration__ __pragma(pack(pop))
#endif


}  // namespace zifmann::zgame::core::utils

#endif
