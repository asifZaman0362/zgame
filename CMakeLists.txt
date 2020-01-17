project(zgame)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.5)

set(SOURCES inc/Application.hpp)
set(HEADERS src/Application.cpp)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules)
include_directories(inc)
find_package(SFML 2.4.2 COMPONENTS system window graphics audio REQUIRED)

add_library(zgame ${HEADERS} ${SOURCES})
target_link_libraries(zgame -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lGL)
