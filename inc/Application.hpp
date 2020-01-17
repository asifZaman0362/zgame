#include "Settings.hpp"

namespace TstBits {
    class Application {
    private:
        Settings m_settings;
        sf::Clock m_clock;
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
                    Update();
                }
            }
        }
    };
}