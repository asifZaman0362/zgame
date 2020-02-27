#include "EmptyScene.hpp"
#include "AssetManager.hpp"
#include "logger.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace ze {
    
    EmptyScene::EmptyScene() {}
    
    EmptyScene::~EmptyScene() {
        Logger::LogMsg("Deleted Scene");
    }

    void EmptyScene::OnInit() {
        m_isPositioned = false;
        m_clearColor = sf::Color::Blue;
        m_emptyText = new sf::Text();
        m_emptyText->setFont(*AssetManager::LoadFont("Roboto"));
        m_emptyText->setString("Empty Scene :(");
        m_drawables.push_back(m_emptyText);
    }

    void EmptyScene::OnUpdate(float dt) {

    }

    void EmptyScene::OnRender(sf::RenderTarget& target) {
        if (!m_isPositioned) {
            float x = m_emptyText->getGlobalBounds().width/2;
            float y = m_emptyText->getGlobalBounds().height/2;
            m_emptyText->setPosition(target.getSize().x/2 - x, target.getSize().y/2 - y);
        }
        Scene::OnRender(target);
    }

    void EmptyScene::OnPause() {

    }

    void EmptyScene::OnResume() {
        
    }

    void EmptyScene::OnStop() {

    }

}