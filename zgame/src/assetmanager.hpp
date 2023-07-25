#ifndef ZGAME_CORE_ASSETMANAGER_H
#define ZGAME_CORE_ASSETMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

namespace zifmann::zgame::core {
namespace AssetManager {

typedef unsigned int Shader;
typedef unsigned int ShaderProgram;

class Texture {
   public:
    bool loadFromFile(std::string_view) {}
};
class SoundBuffer {
   public:
    bool loadFromFile(std::string_view) {}
};
class Font {
   public:
    bool loadFromFile(std::string_view) {}
};

// TODO: use shared ptr?
static std::unordered_map<std::string, std::shared_ptr<Texture>> texture_files;
static std::unordered_map<std::string, std::shared_ptr<SoundBuffer>>
    audio_files;
static std::unordered_map<std::string, std::shared_ptr<Font>> font_files;
static std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
static std::unordered_map<std::string, std::shared_ptr<ShaderProgram>>
    shader_programs;

/// @brief Loads texture into memory
/// @param filename: Filename of the texture
std::weak_ptr<Texture> LoadTexture(const std::string&);
/// @brief Loads audio clip into memory
/// @param filename: Filename of the audio clip
std::weak_ptr<SoundBuffer> LoadAudio(const std::string&);
/// @brief Loads font into memory
/// @param filename: Filename of the font
std::weak_ptr<Font> LoadFont(const std::string&);

/// @brief Loads, and compiles a shader into memory
/// @param  filename Filename of the shader source
/// @return
std::weak_ptr<Shader> LoadShader(const std::string&);

/// @brief Loads, compiles and links a shader program into memory
/// @param  filename Filename of the shader source
/// @return
std::weak_ptr<Shader> LoadShader(const std::string&);

/// @brief Deletes and unloads texture from memory
/// @param filename: Filename of the texture
void DeleteTexture(const std::string&);
/// @brief Deletes and unloads audio clip from memory
/// @param filename: Filename of the audio clip
void DeleteAudio(const std::string&);
/// @brief Deletes and unloads font file from memory
/// @parama filename: Filename of the font
void DeleteFont(const std::string&);

/// @brief Clears all resources that were loaded since startup
void ClearResources();

}  // namespace AssetManager
}  // namespace zifmann::zgame::core

#endif