cmake_minimum_required(VERSION 3.15)
project(zgame)

set(CMAKE_CXX_STANDARD 17)

include_directories(opengl/include)
link_directories(lib)
set(OPENGL_FILES opengl/src/glad.c)

set(SOURCE_FILES 
    zgame/src/main.cpp zgame/src/shader.cpp zgame/src/shader.hpp
    zgame/src/game.hpp zgame/src/game.cpp zgame/src/window.hpp 
    zgame/src/window.cpp zgame/src/triangle.hpp zgame/src/triangle.cpp
    zgame/src/mesh.hpp zgame/src/mesh.cpp zgame/src/assetmanager.hpp
    zgame/src/assetmanager.cpp
)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} ${OPENGL_FILES})
#file(COPY zgame/res DESTINATION .)
add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy_assets.cmake)
add_dependencies(${CMAKE_PROJECT_NAME} copy_assets)
target_link_libraries(${CMAKE_PROJECT_NAME} glfw3 kernel32 opengl32)