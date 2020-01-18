#include <memory>
#include <stack>

namespace sf {
    class RenderTarget;
}

namespace TstBits {

    class Scene;

    #define MAX_SCENES_RUNNING 2
    using sf::RenderTarget;
    typedef std::unique_ptr<Scene> ScenePtr;
    
    class SceneManager {
    public:
        SceneManager() = delete;
        ~SceneManager();

        static void LoadScene(ScenePtr, bool=true);
        static void RemoveScene();
        static void UpdateScene(float);
        static void DrawScene(RenderTarget&);
        static void DestroyAll();
        //static Scene& GetTopScene();
    private:
        static std::stack<ScenePtr> m_scenes;
    };
}
