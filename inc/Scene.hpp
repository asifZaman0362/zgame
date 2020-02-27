#pragma once
#include <vector>
#include <SFML/Graphics/Color.hpp>

namespace sf {
    class RenderTarget;
    class Drawable;
}

namespace ze {
    class Scene {
    public:
        Scene();
        virtual ~Scene();
        virtual void OnInit()                       = 0;
        virtual void OnResume()                     = 0;
        virtual void OnPause()                      = 0;
        virtual void OnUpdate(float)                = 0;
        virtual void OnStop()                       = 0;
        virtual void OnRender(sf::RenderTarget&);
    protected:
        std::vector<sf::Drawable*> m_drawables;
        sf::Color m_clearColor = sf::Color::Black;
    };
}
