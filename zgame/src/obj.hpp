#ifndef ZIFMANN_ZGAME_CORE_OBJ_HPP
#define ZIFMANN_ZGAME_CORE_OBJ_HPP

#include <fstream>
#include <string>
namespace zifmann::zgame::core::obj_loader {
typedef unsigned int uint;
enum ObjLoadStatus { Success, ReadError, ParseError };
ObjLoadStatus load_file(const std::string& path);
}  // namespace zifmann::zgame::core::obj_loader

#endif
