cmake_minimum_required(VERSION 3.25)
project(zgame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include_directories(opengl/include)
if (WIN32)
    link_directories(lib)
endif()
set(OPENGL_FILES opengl/src/glad.c)

set(SOURCE_FILES 
    zgame/src/main.cpp zgame/src/shader.cpp zgame/src/shader.hpp
    zgame/src/game.hpp zgame/src/game.cpp zgame/src/window.hpp 
    zgame/src/window.cpp zgame/src/triangle.hpp zgame/src/triangle.cpp
    zgame/src/mesh.hpp zgame/src/mesh.cpp zgame/src/assetmanager.hpp
    zgame/src/assetmanager.cpp zgame/src/logger.hpp zgame/src/logger.cpp
    zgame/src/obj.hpp zgame/src/obj.cpp zgame/src/utils.cpp zgame/src/utils.hpp
    zgame/src/gameobject.hpp zgame/src/gameobject.cpp
)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} ${OPENGL_FILES})
#file(COPY zgame/res DESTINATION .)
add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy_assets.cmake)
add_dependencies(${CMAKE_PROJECT_NAME} copy_assets)
if (WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME} glfw3 kernel32 opengl32)
elseif (LINUX)
    target_link_libraries(${CMAKE_PROJECT_NAME} glfw)
endif()
