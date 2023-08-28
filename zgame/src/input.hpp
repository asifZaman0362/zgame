#ifndef ZIFMANN_ZGAME_CORE_INPUT_HPP
#define ZIFMANN_ZGAME_CORE_INPUT_HPP
#include "window.hpp"

namespace zifmann::zgame::core::input {

class KeyListener {
   public:
    virtual void OnKeyPress(int, int) = 0;
    virtual void OnKeyRelease(int, int) = 0;
};

class MouseListener {
   public:
    virtual void OnMouseMove(double, double) = 0;
};

class MouseButtonListener {
   public:
    virtual void OnMouseButtonPress(int, int) = 0;
    virtual void OnMouseButtonRelease(int, int) = 0;
};

class ScrollListener {
   public:
    virtual void OnMouseScroll(double offset) = 0;
};

void key_press_callback(Window window, int key, int scancode, int action,
                        int mods);
void mouse_cursor_callback(Window window, double xpos, double ypos);
void mouse_button_callback(Window window, int button, int action, int mods);
void scroll_wheel_callback(Window window, double yoffset, double xoffset);

void hide_mouse(Window window);
void show_mouse(Window window);
void lock_mouse(Window window);
void unlock_mouse(Window window);

void AddRawKeyListener(KeyListener *);
void RemoveRawKeyListener(KeyListener *);
void AddKeyListener(KeyListener *);
void RemoveKeyListener(KeyListener *);
void AddMouseListener(MouseListener *);
void RemoveMouseListener(MouseListener *);
void AddMouseButtonListener(MouseButtonListener *);
void RemoveMouseButtonListener(MouseButtonListener *);
void AddScrollListener(ScrollListener *);
void RemoveScrollListener(ScrollListener *);

}  // namespace zifmann::zgame::core::input
#endif
