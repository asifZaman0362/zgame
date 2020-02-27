#include "AssetManager.hpp"
#include "logger.hpp"
// #include "string.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

using namespace std;

namespace ze {

    #define TEXTURE_PATH "Assets/Textures/"
    #define SOUND_PATH "Assets/Sounds/"
    #define FONT_PATH "Assets/Fonts/"
    #define TEXTURE_EXT ".png"
    #define SOUND_EXT ".ogg"
    #define FONT_EXT ".ttf"

    // std::list<string> AssetManager::texture_names;
    // std::list<string> AssetManager::sound_names;
    // std::list<string> AssetManager::font_names;

    std::unordered_map<std::string, sf::Texture*>        AssetManager::textures;
    std::unordered_map<std::string, sf::SoundBuffer*>    AssetManager::sounds;
    std::unordered_map<std::string, sf::Font*>           AssetManager::fonts;

    AssetManager::~AssetManager() {
        UnLoadAll();
    }

    sf::Texture* AssetManager::LoadTexture(std::string name) {
        auto iterator = textures.find(name);
        if (iterator != textures.end()) return iterator->second;
        else {
            sf::Texture* texture = new sf::Texture();
            if (texture->loadFromFile(TEXTURE_PATH + name + TEXTURE_EXT)) {
                textures[name] = texture;
                return texture;
            } else {
                Logger::LogErr("Error 404! File not found!");
            }
        }
        return nullptr;
    }

    sf::Font* AssetManager::LoadFont(std::string name) {
        auto iterator = fonts.find(name);
        if (iterator != fonts.end()) return iterator->second;
        else {
            sf::Font* font = new sf::Font();
            if (font->loadFromFile(FONT_PATH + name + FONT_EXT)) {
                fonts[name] = font;
                return font;
            } else {
                Logger::LogErr("Error 404! File not found!");
            }
        }
        return nullptr;
    }

    sf::SoundBuffer* AssetManager::LoadSoundClip(std::string name) {
        auto iterator = sounds.find(name);
        if (iterator != sounds.end()) return iterator->second;
        else {
            sf::SoundBuffer* sound = new sf::SoundBuffer();
            if (sound->loadFromFile(SOUND_PATH + name + SOUND_EXT)) {
                sounds[name] = sound;
                return sound;
            } else {
                Logger::LogErr("Error 404! File not found!");
            }
        }
        return nullptr;
    }

    void AssetManager::UnLoadAll() {
        for (auto var : textures) delete var.second;
        for (auto var : sounds) delete var.second;
        for (auto var : fonts) delete var.second;
        textures.clear();
        fonts.clear();
        sounds.clear();
    }
}