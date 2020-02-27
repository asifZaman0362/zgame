#pragma once
#include "Scene.hpp"

namespace sf {
    class Text;
}

namespace ze {
    class EmptyScene : public Scene {
    public:
        EmptyScene();
        ~EmptyScene();

        void OnInit() override;
        void OnResume() override;
        void OnPause() override;
        void OnStop() override;
        void OnRender(sf::RenderTarget&) override;
        void OnUpdate(float) override;
    private:
        sf::Text* m_emptyText;
        bool m_isPositioned;
    };
}