#include "string.hpp"
#include "logger.hpp"
#include "SceneManager.hpp"
#include "Scene.hpp"

namespace TstBits {
    
    std::stack<ScenePtr> SceneManager::m_scenes;

    SceneManager::~SceneManager() {
        DestroyAll();
    }

    void SceneManager::LoadScene(ScenePtr scene, bool replace) {
        if ((m_scenes.size() >= MAX_SCENES_RUNNING || replace) && !m_scenes.empty()) {
            if (m_scenes.size() >= MAX_SCENES_RUNNING)
                Logger::LogErr("SCENE STACK OVERFLOW!! POPPING TOP SCENE!");
            
            m_scenes.top().reset();
            m_scenes.pop();
        } else if (!m_scenes.empty()) m_scenes.top()->OnPause();
        m_scenes.push(std::move(scene));
        m_scenes.top()->OnInit();
    }

    void SceneManager::RemoveScene() {
        // Git good or git rekt
        if (m_scenes.empty()) 
            Logger::LogErr("You on drugs bro? There are no friggin scenes");
        else {
            m_scenes.top().reset();
            m_scenes.pop();
            if (!m_scenes.empty()) m_scenes.top()->OnResume();
        }
    }

    void SceneManager::UpdateScene(float dt) {
        if (m_scenes.empty() || m_scenes.top() == nullptr) 
            Logger::LogErr("No Scene to render!");
        m_scenes.top()->OnUpdate(dt);
    }

    void SceneManager::DrawScene(RenderTarget& target) {
        if (m_scenes.empty() || m_scenes.top() == nullptr) 
            Logger::LogErr("No Scene to render!");
        m_scenes.top()->OnRender(target);
    }

    void SceneManager::DestroyAll() {
        while (!m_scenes.empty()) {
            m_scenes.top()->OnStop();
            m_scenes.top().reset();
            m_scenes.pop();
        }
    }

    // Scene& SceneManager::GetTopScene() {
    //     //return *m_scenes.top().get();
    //     return nullptr;
    // }

}