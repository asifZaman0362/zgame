#include <SFML/Graphics/RenderWindow.hpp>
#include "Settings.hpp"

namespace sf {
    class Event;
}

namespace TstBits {
    class Settings;
    class Application {
    
    public:
        Application(const Settings&);
        ~Application();
        
        void Run();
        void Stop();

    private:
        Settings m_settings;
        sf::Clock m_clock;
        sf::RenderWindow m_window;
        bool m_isRunning;

        void ProcessInput(const sf::Event&);
        void Update(const float&);
        void Draw();
    };
}