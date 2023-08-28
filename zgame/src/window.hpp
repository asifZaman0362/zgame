#ifndef ZIFMANN_ZGAME_CORE_WINDOW_HPP
#define ZIFMANN_ZGAME_CORE_WINDOW_HPP
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace zifmann::zgame::core {
enum WindowStyle { Fullscreen, Windowed, BorderlessWindow };

struct WindowSettings {
    const unsigned short width = 800;
    const unsigned short height = 600;
    const unsigned short version_major = 3;
    const unsigned short version_minor = 3;
    const bool fullscreen = false;
    char title[512] = "GLFW window";
    // more options (not yet implemented)
    const unsigned short framerate;
    const bool vertical_sync;
    const WindowStyle style;
};

typedef GLFWwindow* Window;

Window create_window(WindowSettings settings);

void close_window(Window window);
}  // namespace zifmann::zgame::core
#endif
