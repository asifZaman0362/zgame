project(zgame)
set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.5)

set(HEADERS inc/Application.hpp inc/Settings.hpp inc/string.hpp inc/logger.hpp 
inc/input_manager.hpp inc/SceneManager.hpp inc/Scene.hpp inc/Entity.hpp
inc/Systems/PhysicsManager2D.hpp inc/Components/Component.hpp inc/Components/Transform.hpp
inc/Components/PhysicsObject2D.hpp inc/Components/Collider2D.hpp inc/Components/BoxCollider.hpp
inc/Components/CircleCollider.hpp inc/Components/PolygonCollider.hpp inc/Systems/CollisionManager2D.hpp
inc/EmptyScene.hpp inc/AssetManager.hpp)
set(SOURCES src/Application.cpp src/string.cpp src/logger.cpp src/input_manager.cpp src/SceneManager.cpp 
src/Scene.cpp src/Systems/PhysicsManager2D.cpp src/Systems/CollisionManager2D.cpp 
src/Components/CircleCollider.cpp src/Components/BoxCollider.cpp src/EmptyScene.cpp src/AssetManager.cpp)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
include_directories(inc)
find_package(SFML 2.4.2 COMPONENTS system window graphics audio REQUIRED)

add_library(zgame ${HEADERS} ${SOURCES})
add_executable(zgame-sandbox ${HEADERS} ${SOURCES} main.cpp)
target_link_libraries(zgame sfml-system sfml-window sfml-graphics sfml-audio GL)
target_link_libraries(zgame-sandbox sfml-system sfml-window sfml-graphics sfml-audio GL)