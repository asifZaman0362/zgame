#include "assetmanager.hpp"

namespace zifmann::zgame::core {
namespace AssetManager {

std::weak_ptr<Texture> LoadTexture(const std::string& name) {
    if (texture_files[name])
        return texture_files[name];
    else {
        auto texture = std::make_shared<Texture>();
        texture->loadFromFile(name);
        texture_files[name] = texture;
        return texture;
    }
}

std::weak_ptr<SoundBuffer> LoadAudio(const std::string& name) {
    if (audio_files[name])
        return audio_files[name];
    else {
        auto buffer = std::make_shared<SoundBuffer>();
        buffer->loadFromFile(name);
        audio_files[name] = buffer;
        return buffer;
    }
}

std::weak_ptr<Font> LoadFont(const std::string& name) {
    if (font_files[name])
        return font_files[name];
    else {
        auto font = std::make_shared<Font>();
        font->loadFromFile(name);
        font_files[name] = font;
        return font;
    }
}

void DeleteTexture(const std::string& name) {
    if (texture_files[name]) {
        texture_files.erase(name);
    }
}

void DeleteAudio(const std::string& name) {
    if (audio_files[name]) {
        audio_files.erase(name);
    }
}

void DeleteFont(const std::string& name) {
    if (font_files[name]) {
        font_files.erase(name);
    }
}

void ClearResources() {
    texture_files.clear();
    audio_files.clear();
    font_files.clear();
}

}  // namespace AssetManager
}  // namespace zifmann::zgame::core