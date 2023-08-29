#ifndef ZGAME_CORE_ASSETMANAGER_H
#define ZGAME_CORE_ASSETMANAGER_H

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>

#include "material.hpp"
#include "obj.hpp"

namespace zifmann::zgame::core {
namespace AssetManager {

extern std::unordered_map<std::string, std::shared_ptr<rendering::Material>> materials;

typedef unsigned int Shader;
typedef unsigned int ShaderProgram;

class Texture {
   private:
    int width;
    int height;
    int nrChannels;
    unsigned int texture;

   public:
    Texture();
    ~Texture();
    bool loadFromFile(const std::string&);
    unsigned int get_id();
};
class SoundBuffer {
   public:
    bool loadFromFile(const std::string&) { return false; }
};
class Font {
   public:
    bool loadFromFile(const std::string&) { return false; }
};

/// @brief Loads texture into memory
/// @param filename: Filename of the texture
std::shared_ptr<Texture> LoadTexture(const std::string& filename);
/// @brief Loads audio clip into memory
/// @param filename: Filename of the audio clip
std::shared_ptr<SoundBuffer> LoadAudio(const std::string& filename);
/// @brief Loads font into memory
/// @param filename: Filename of the font
std::shared_ptr<Font> LoadFont(const std::string& filename);

/// @brief Loads, compiles and links a shader program into memory
/// @param vertex_source Filename of the vertex shader source
/// @param fragment_source Filename of the fragment shader source
/// @return
ShaderProgram LoadShaderProgram(const std::string& vertex_source,
                                const std::string& fragment_source);

/// @brief Loads an OBJ file into memory from disk
/// @param path Path to the model to load
/// @return
std::shared_ptr<obj_loader::ObjData> LoadObjModel(const std::string& path);

template<typename T>
concept DerivesMaterial = std::is_base_of_v<rendering::Material, T>;

/// @brief Loads a material of type T where T: Material
/// @param name the name of the material
/// @return
template <DerivesMaterial T>
std::shared_ptr<T> LoadMaterial(const std::string& name);

template <DerivesMaterial T>
std::shared_ptr<T> LoadMaterial(const std::string& name) {
    if (materials.contains(name))
        return std::static_pointer_cast<T>(materials[name]);
    else {
        materials[name] = std::make_shared<T>();
        return std::static_pointer_cast<T>(materials[name]);
    }
}


/// @brief Deletes and unloads texture from memory
/// @param filename: Filename of the texture
void DeleteTexture(const std::string& filename);
/// @brief Deletes and unloads audio clip from memory
/// @param filename: Filename of the audio clip
void DeleteAudio(const std::string& filename);
/// @brief Deletes and unloads font file from memory
/// @param filename: Filename of the font
void DeleteFont(const std::string& filename);
/// @brief Deletes an obj file from memory
/// @param path
/// @return
void DeleteObjModel(const std::string& path);

/// @brief Deletes a material by name
/// @param name
template <DerivesMaterial T>
void DeleteMaterial(const std::string& name);

/// @brief Clears all resources that were loaded since startup
void ClearResources();

}  // namespace AssetManager
}  // namespace zifmann::zgame::core

#endif
