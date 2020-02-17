#pragma once
#include "string.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <list>
#include <map>


typedef sf::Keyboard::Key KeyCode; // Change to other type if not using SFML

namespace ze
{
    // A basic input handler class
    class InputManager {
    public:
        InputManager() = delete;
        ~InputManager() = default;

        // Returns true if the key was pressed exactly in this frame
        virtual bool IsKeyDown(KeyCode) const;

        // Returns true if the key is down regardless of when it was first pressed
        virtual bool IsKeyHeld(KeyCode) const;

        // Returns the value of the axis with @p name, if registered
        virtual double GetAxis(ze::string) const;

        friend class Application;
    private:
        void AddKeyDown(KeyCode);
        void RemoveKeyDown(KeyCode);
        static std::map<string, double, string::Compare>  m_axes;
        static std::list<KeyCode> m_keysDownThisFrame;
        static std::list<KeyCode> m_keysUpThisFrame;
    };
}
