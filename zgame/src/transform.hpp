#ifndef ZIFMANN_ZGAME_TRANSFORM_HPP
#define ZIFMANN_ZGAME_TRANSFORM_HPP

#include "types.hpp"

namespace zifmann::zgame::core {
    struct Transform {
        vec3 position;
        vec3 euler_rotation;
        vec3 scale;
    };
}

#endif
