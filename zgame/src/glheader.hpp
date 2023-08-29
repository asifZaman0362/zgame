#ifndef GL_HEADER_HPP
#define GL_HEADER_HPP

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#else
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#ifndef __APPLE__
#include <glad/glad.h>
#endif

#endif
