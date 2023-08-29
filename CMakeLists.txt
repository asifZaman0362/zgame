cmake_minimum_required(VERSION 3.7)
project(zgame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (WIN32)
    include_directories(external/include/windows)
    link_directories(external/lib/windows)
elseif (APPLE)
    find_package(glfw3 3.4 REQUIRED)
    find_package(opengl REQUIRED)
endif()

if (NOT APPLE)
    set(GLAD_SRC external/src/glad.c)
    include_directories(external/include/glad)
endif()

include_directories(external/include/common)

set(SOURCE_FILES 
    zgame/src/main.cpp zgame/src/shader.cpp zgame/src/game.cpp
    zgame/src/window.cpp zgame/src/mesh.cpp zgame/src/assetmanager.cpp 
    zgame/src/input.cpp zgame/src/obj.cpp zgame/src/utils.cpp
    zgame/src/camera.cpp zgame/src/material.cpp zgame/src/scene.cpp 
    zgame/src/ecs.cpp zgame/src/renderer.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES} ${GLAD_SRC})
if (APPLE)
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
endif()
#file(COPY zgame/res DESTINATION .)
add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy_assets.cmake)
add_dependencies(${CMAKE_PROJECT_NAME} copy_assets)
if (WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME} glfw3 kernel32 opengl32)
elseif (LINUX)
    target_link_libraries(${CMAKE_PROJECT_NAME} glfw)
elseif (APPLE)
    target_link_libraries(${CMAKE_PROJECT_NAME} glfw "-framework Cocoa" "-framework OpenGL" "-framework IOKit" ${OPENGL_gl_LIBRARY})
endif()
