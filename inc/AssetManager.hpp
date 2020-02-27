#pragma once
#include <string>
#include <list>
#include <unordered_map>

namespace sf {
    class Texture;
    class Font;
    class SoundBuffer;
}

namespace ze {
    class AssetManager {
    public:
        AssetManager() = delete;
        ~AssetManager();

        static sf::Texture*     LoadTexture(std::string);
        static sf::SoundBuffer* LoadSoundClip(std::string);
        static sf::Font*        LoadFont(std::string);

        static bool UnLoadTexture(std::string);
        static bool UnLoadSound(std::string);
        static bool UnLoadFont(std::string);

        static void UnLoadAll();

    private:
        // static std::list<string> texture_names;
        // static std::list<string> sound_names;
        // static std::list<string> font_names;

        static std::unordered_map<std::string, sf::Texture*>     textures;
        static std::unordered_map<std::string, sf::Font*>        fonts;
        static std::unordered_map<std::string, sf::SoundBuffer*> sounds;
    };
}