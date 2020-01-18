#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace TstBits {

    Scene::Scene() {
        
    }

    Scene::~Scene() {
        for (sf::Drawable* item : m_drawables) {
            delete item;
            m_drawables.pop_back();
        }
    }

    void Scene::OnRender(sf::RenderTarget& target) {
        target.clear(m_clearColor);
        for (auto drawable : m_drawables) {
            target.draw(*drawable);
        }
    }

}