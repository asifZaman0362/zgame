#include "assetmanager.hpp"

#include <cstdint>
#include <fstream>

#include "logger.hpp"
#include "obj.hpp"
#include "shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace zifmann::logger;

namespace zifmann::zgame::core {
namespace AssetManager {

// TODO: use shared ptr?
static std::unordered_map<std::string, std::shared_ptr<Texture>> texture_files;
static std::unordered_map<std::string, std::shared_ptr<SoundBuffer>>
    audio_files;
static std::unordered_map<std::string, std::shared_ptr<Font>> font_files;
static std::unordered_map<std::string, ShaderProgram> shader_programs;
static std::unordered_map<std::string, std::shared_ptr<obj_loader::ObjData>>
    obj_models;

Texture::Texture() = default;
Texture::~Texture() { glDeleteTextures(1, &texture); }

bool Texture::loadFromFile(const std::string& path) {
    unsigned char* data =
        stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        stbi_image_free(data);
        return false;
    }
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    return true;
}

unsigned int Texture::get_id() { return texture; }

std::shared_ptr<Texture> LoadTexture(const std::string& name) {
    if (texture_files[name])
        return texture_files[name];
    else {
        auto texture = std::make_shared<Texture>();
        if (!texture->loadFromFile(name)) {
            log_error("Failed to load texture!");
            return nullptr;
        }
        texture_files[name] = texture;
        return texture;
    }
}

std::shared_ptr<SoundBuffer> LoadAudio(const std::string& name) {
    if (audio_files[name])
        return audio_files[name];
    else {
        auto buffer = std::make_shared<SoundBuffer>();
        buffer->loadFromFile(name);
        audio_files[name] = buffer;
        return buffer;
    }
}

std::shared_ptr<Font> LoadFont(const std::string& name) {
    if (font_files[name])
        return font_files[name];
    else {
        auto font = std::make_shared<Font>();
        font->loadFromFile(name);
        font_files[name] = font;
        return font;
    }
}

ShaderProgram LoadShaderProgram(const std::string& vert,
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
        return 0;
    }
    shader_programs[fullname] = program_id;
    return shader_programs[fullname];
}

std::shared_ptr<obj_loader::ObjData> LoadObjModel(const std::string& path) {
    if (obj_models[path]) {
        return obj_models[path];
    } else {
        obj_loader::ObjData data;
        auto res = obj_loader::load_file(path, data);
        if (res != obj_loader::ObjLoadStatus::Success) {
            log_error("Failed to load obj model!");
            return nullptr;
        }
        obj_models[path] = std::make_shared<obj_loader::ObjData>(data);
        return obj_models[path];
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

void DeleteObjModel(const std::string& path) {
    if (obj_models[path]) {
        obj_models.erase(path);
    }
}

void DeleteShaderProgram(const std::string& shader) {
    if (shader_programs[shader]) {
        glDeleteProgram(shader_programs[shader]);
    }
}

void ClearResources() {
    texture_files.clear();
    audio_files.clear();
    font_files.clear();
}

}  // namespace AssetManager
}  // namespace zifmann::zgame::core
