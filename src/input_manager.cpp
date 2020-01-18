#include "input_manager.hpp"
#include <SFML/Window/Keyboard.hpp>

using TstBits::InputManager;
using TstBits::string;

std::map<string, double, string::Compare> InputManager::m_axes;
std::list<KeyCode> InputManager::m_keysDownThisFrame;
std::list<KeyCode> InputManager::m_keysUpThisFrame;

bool InputManager::IsKeyDown(KeyCode key) const {
    for (auto k : m_keysDownThisFrame) {
        if (k == key) return true;
    }
    return false;
}

bool InputManager::IsKeyHeld(KeyCode key) const {
    return sf::Keyboard::isKeyPressed(key);
}

double InputManager::GetAxis(string name) const {
    for (auto& item : m_axes) {
        if (name == item.first) return m_axes[name];
    }
    // Log an error
    return 0.0;
}