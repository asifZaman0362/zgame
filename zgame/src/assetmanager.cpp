#include "assetmanager.hpp"

#include "logger.hpp"
#include "shader.hpp"

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

std::weak_ptr<Shader> LoadShader(const std::string& path) {
    if (shaders[path]) {
        return shaders[path];
    }
    using namespace zifmann::zgame::core::rendering::shader;
    unsigned int shader_id;
    char infolog[512];
    if (load_shader(path.c_str(), GL_VERTEX_SHADER, shader_id, infolog) !=
        ShaderLoadStatus::Success) {
        log_error("Failed to load shader! log: %s", infolog);
        return std::weak_ptr<Shader>();
    }
    shaders[path] = std::make_shared<Shader>(shader_id);
    return shaders[path];
}

std::weak_ptr<ShaderProgram> LoadShaderProgram(const std::string& vert,
                                               const std::string& frag) {
    std::string fullname = vert + frag;
    if (shader_programs[fullname]) {
        return shader_programs[fullname];
    }
    using namespace zifmann::zgame::core::rendering::shader;
    unsigned int program_id;
    char infolog[512];
    if (load_shader_program(vert.c_str(), frag.c_str(), program_id, infolog) !=
        ShaderLoadStatus::Success) {
        log_error("Failed to load shader! log: %s", infolog);
        return std::weak_ptr<Shader>();
    }
    shaders[fullname] = std::make_shared<ShaderProgram>(program_id);
    return shaders[fullname];
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
