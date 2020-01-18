#include "Settings.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace TstBits {
    class Application {
    private:
        Settings m_settings;
        sf::Clock m_clock;
        sf::RenderWindow m_window;
        bool m_isRunning;

        void ProcessInput() {}

        void Update(float deltaTime) {}

        void Draw() {}

    public:
        Application(const Settings& settings) : m_settings(settings) {}
        ~Application() {}
        void Run() {
            m_isRunning = true;
            // Logger::Log("Started application.");
            while (m_isRunning) {
                // Create the window
                while(/*window.isOpen()*/true) {
                    // Poll events
                    m_clock.restart();
                    Update(m_clock.getElapsedTime().asSeconds());
                }
            }
        }
    };
}