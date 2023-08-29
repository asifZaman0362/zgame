#include "input.hpp"

#include <functional>
#include <vector>

#include "logger.hpp"
#include "packedlist.hpp"
#include <unordered_map>

namespace zifmann::zgame::core::input {

static double last_mouse_x = 10000;
static double last_mouse_y = 10000;

PackedList<KeyListener *, 64> raw_key_listeners;
PackedList<MouseListener *, 64> mouse_listeners;
PackedList<MouseButtonListener *, 64> mouse_button_listeners;
PackedList<ScrollListener *, 64> scroll_listeners;
std::unordered_map<int, PackedList<KeyListener *, 64>> key_listeners;

void key_press_callback(Window, int key, int scancode, int action, int mods) {
    if (key_listeners.contains(key)) {
        for (auto &listener : key_listeners[key]) {
            if (action == GLFW_PRESS || action == GLFW_REPEAT)
                listener->OnKeyPress(key, mods);
            else
                listener->OnKeyRelease(key, mods);
        }
    }

    int count = 0;
    for (auto &listener : raw_key_listeners) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            listener->OnKeyPress(key, mods);
        else
            listener->OnKeyRelease(key, mods);
    }
}

void mouse_cursor_callback(Window window, double xpos, double ypos) {
    if (!(last_mouse_x == 10000 || last_mouse_y == 10000)) {
        double dx = xpos - last_mouse_x;
        double dy = ypos - last_mouse_y;
        for (auto &listener : mouse_listeners) {
            listener->OnMouseMove(dx, dy);
        }
    }
    last_mouse_x = xpos;
    last_mouse_y = ypos;
}
void mouse_button_callback(Window window, int button, int action, int mods) {
    for (auto &listener : mouse_button_listeners) {
        if (action == GLFW_PRESS || action == GLFW_REPEAT)
            listener->OnMouseButtonPress(button, mods);
        else
            listener->OnMouseButtonRelease(button, mods);
    }
}

void scroll_wheel_callback(Window window, double yoffset, double xoffset) {
    for (auto &listener : scroll_listeners) {
        listener->OnMouseScroll(yoffset);
    }
}

void hide_mouse(Window window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void show_mouse(Window window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void lock_mouse(Window window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void unlock_mouse(Window window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void AddRawKeyListener(KeyListener *listener) {
    raw_key_listeners.push_back(listener);
}
void RemoveRawKeyListener(KeyListener *listener) {
    raw_key_listeners.remove(listener);
}
void AddKeyListener(int key, KeyListener *listener) {
    if (key_listeners.contains(key)) {
        key_listeners[key].push_back(listener);
    } else {
        PackedList<KeyListener *, 64> list;
        list.push_back(listener);
        key_listeners[key] = list;
    }
}
void RemoveKeyListener(int key, KeyListener *listener) {
    if (key_listeners.contains(key)) {
        key_listeners[key].remove(listener);
    }
}
void AddMouseListener(MouseListener *listener) {
    mouse_listeners.push_back(listener);
}
void RemoveMouseListener(MouseListener *listener) {
    mouse_listeners.remove(listener);
}
void AddMouseButtonListener(MouseButtonListener *listener) {
    mouse_button_listeners.push_back(listener);
}
void RemoveMouseButtonListener(MouseButtonListener *listener) {
    mouse_button_listeners.remove(listener);
}
void AddScrollListener(ScrollListener *listener) {
    scroll_listeners.push_back(listener);
}

void RemoveScrollListener(ScrollListener *listener) {
    scroll_listeners.remove(listener);
}
}  // namespace zifmann::zgame::core::input
