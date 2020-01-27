#include "Application.hpp"
#include "input_manager.hpp"
#include "logger.hpp"
#include <SFML/Window/Event.hpp>

namespace TstBits {

    Application::Application(const Settings& settings) 
        : m_settings(settings) {}

    Application::~Application() {}

    void Application::Run() {
        m_isRunning = true;
        Logger::LogMsg("Started Application");
        while (m_isRunning) {
            
            sf::VideoMode videoMode;
            videoMode.width = m_settings.SCREEN_WIDTH;
            videoMode.height = m_settings.SCREEN_HEIGHT;

            sf::ContextSettings ctxSettings;
            ctxSettings.majorVersion = m_settings.GL_VERSION_MAJOR;
            ctxSettings.minorVersion = m_settings.GL_VERSION_MINOR;
            ctxSettings.sRgbCapable = m_settings.SRGB_MODE;
            ctxSettings.depthBits = m_settings.DEPTH_BITS;
            ctxSettings.attributeFlags = m_settings.GL_CORE_PROFILE ? 
                sf::ContextSettings::Core : sf::ContextSettings::Default;
            
            m_window.create(videoMode, m_settings.WINDOW_TITLE, 
                m_settings.WINDOW_STYLE, ctxSettings);
            if (m_settings.VERTICAL_SYNC)
                m_window.setVerticalSyncEnabled(true);
            else if (m_settings.FRAMERATE_LIMIT > 0)
                m_window.setFramerateLimit(m_settings.FRAMERATE_LIMIT);

            while(m_window.isOpen()) {
                sf::Event e{};
                while(m_window.pollEvent(e)) {
                    ProcessInput(e);
                }
                m_clock.restart();
                Update(m_clock.getElapsedTime().asSeconds());
                Draw();
            }

        }
    }

    void Application::Stop() {
        m_isRunning = false;
        if (m_window.isOpen()) {
            m_window.close();
            // SceneManager.DestroyAll();
        }
    }

    void Application::ProcessInput(const sf::Event& event) {
        if (event.type == sf::Event::Closed) Stop();
        else if (event.type == sf::Event::KeyPressed)
            InputManager::m_keysDownThisFrame.push_back(event.key.code);
        else if (event.type == sf::Event::KeyReleased)
            InputManager::m_keysUpThisFrame.push_back(event.key.code);
    }

    void Application::Update(const float& dt) {
    }

    void Application::Draw() {
        m_window.display();
    }
}