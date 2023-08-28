#include "input.hpp"

#include <functional>
#include <vector>

namespace zifmann::zgame::core::input {

static double last_mouse_x;
static double last_mouse_y;

std::vector<KeyListener *> key_listeners;
std::vector<MouseListener *> mouse_listeners;
std::vector<MouseButtonListener *> mouse_button_listeners;

void key_press_callback(Window window, int key, int scancode, int action,
                        int mods) {}
void mouse_cursor_callback(Window window, double xpos, double ypos) {}
void mouse_button_callback(Window window, int button, int action, int mods) {}

void scroll_wheel_callback(Window window, double yoffset, double xoffset) {}

void hide_mouse(Window window) {}

void show_mouse(Window window) {}

void lock_mouse(Window window) {}

void unlock_mouse(Window window) {}

void AddKeyListener(KeyListener *listener) {
    key_listeners.push_back(listener);
}
void RemoveKeyListener(KeyListener *listener) {
    auto pos = std::find(key_listeners.begin(), key_listeners.end(), listener);
    if (pos != std::end(key_listeners)) key_listeners.erase(pos);
}
void AddMouseListener(MouseListener *listener) {
    mouse_listeners.push_back(listener);
}
void RemoveMouseListener(MouseListener *listener) {
    auto pos =
        std::find(mouse_listeners.begin(), mouse_listeners.end(), listener);
    if (pos != std::end(mouse_listeners)) mouse_listeners.erase(pos);
}
void AddMouseButtonListener(MouseButtonListener *listener) {
    mouse_button_listeners.push_back(listener);
}
void RemoveMouseButtonListener(MouseButtonListener *listener) {
    auto pos = std::find(mouse_button_listeners.begin(),
                         mouse_button_listeners.end(), listener);
    if (pos != std::end(mouse_button_listeners))
        mouse_button_listeners.erase(pos);
}
}  // namespace zifmann::zgame::core::input