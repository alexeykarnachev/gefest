#include "resources.hpp"

#include "raylib/raylib.h"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace gefest::resources {

Mesh PLANE_MESH;
Mesh CYLINDER_MESH;

Shader GEOSPHERE_TEXTURE_SHADER;
Shader SKYBOX_TEXTURE_SHADER;
Shader SUN_TEXTURE_SHADER;
Shader ASTEROID_TEXTURE_SHADER;

Material MODEL_MATERIAL;
Material SKYBOX_MATERIAL;
Material GEOSPHERE_MATERIAL;
Material SUN_MATERIAL;
Material ASTEROID_MATERIAL;
Material CROSSHAIR_MATERIAL;
Material PROJECTILE_MATERIAL;

Model SPHERE_MODEL;
Model RED_FIGHTER_MODEL;
std::vector<Model> ASTEROID_MODELS;

namespace fs = std::filesystem;

static std::vector<std::string> get_file_paths(const std::string &dir_path) {
    std::vector<std::string> file_paths;

    for (const auto &entry : fs::recursive_directory_iterator(dir_path)) {
        if (fs::is_regular_file(entry.path())) {
            file_paths.push_back(entry.path().string());
        }
    }

    return file_paths;
}

static std::string get_shader_file_path(const std::string &file_name) {
    auto file_path = "resources/shaders/" + file_name;
    return file_path;
}

static std::string load_shader_src(const std::string &file_name) {
    const std::string version_src = "#version 460 core";
    std::ifstream common_file(get_shader_file_path("common.glsl"));
    std::ifstream shader_file(get_shader_file_path(file_name));

    std::stringstream common_stream, shader_stream;
    common_stream << common_file.rdbuf();
    shader_stream << shader_file.rdbuf();

    std::string common_src = common_stream.str();
    std::string shader_src = shader_stream.str();

    std::string full_src = version_src + "\n" + common_src + "\n" + shader_src;

    return full_src;
}

static Shader load_shader(
    const std::string &vs_file_name, const std::string &fs_file_name
) {
    std::string vs, fs;

    vs = load_shader_src(vs_file_name);
    fs = load_shader_src(fs_file_name);
    Shader shader = LoadShaderFromMemory(vs.c_str(), fs.c_str());

    return shader;
}

static Material load_material(
    const std::string &vs_file_name, const std::string &fs_file_name
) {
    Material material = LoadMaterialDefault();
    material.shader = load_shader(vs_file_name, fs_file_name);
    return material;
}

static std::vector<Model> load_models(std::string dir_path) {
    std::vector<Model> models;
    for (auto file_path : get_file_paths(dir_path)) {
        models.push_back(LoadModel(file_path.c_str()));
    }

    return models;
}

static void unload_models(std::vector<Model> models) {
    for (auto model : models) {
        UnloadModel(model);
    }
}

void load() {
    PLANE_MESH = GenMeshPlane(1.0, 1.0, 1, 1);
    CYLINDER_MESH = GenMeshCylinder(1.0, 1.0, 64);

    GEOSPHERE_TEXTURE_SHADER = load_shader("screen_rect.vert", "geosphere_texture.frag");
    SKYBOX_TEXTURE_SHADER = load_shader("screen_rect.vert", "skybox_texture.frag");
    SUN_TEXTURE_SHADER = load_shader("screen_rect.vert", "sun_texture.frag");
    ASTEROID_TEXTURE_SHADER = load_shader("screen_rect.vert", "asteroid_texture.frag");

    MODEL_MATERIAL = load_material("base.vert", "model.frag");
    SKYBOX_MATERIAL = load_material("skybox.vert", "skybox.frag");
    GEOSPHERE_MATERIAL = load_material("base.vert", "sphere.frag");
    SUN_MATERIAL = load_material("base.vert", "sun.frag");
    ASTEROID_MATERIAL = load_material("base.vert", "model.frag");
    CROSSHAIR_MATERIAL = load_material("base.vert", "crosshair.frag");
    PROJECTILE_MATERIAL = load_material("base.vert", "projectile.frag");

    SPHERE_MODEL = LoadModel("./resources/models/primitives/icosphere_4.obj");
    RED_FIGHTER_MODEL = LoadModel("./resources/models/red_fighter/RedFighter.obj");
    ASTEROID_MODELS = load_models("./resources/models/asteroids");
}

void unload() {
    // TODO: put assets in corresponding vectors and unload them iteratively.
    // Introduce some kind of simple assets manager.

    UnloadMesh(PLANE_MESH);
    UnloadMesh(CYLINDER_MESH);

    UnloadShader(GEOSPHERE_TEXTURE_SHADER);
    UnloadShader(SKYBOX_TEXTURE_SHADER);
    UnloadShader(SUN_TEXTURE_SHADER);
    UnloadShader(ASTEROID_TEXTURE_SHADER);

    UnloadMaterial(MODEL_MATERIAL);
    UnloadMaterial(SKYBOX_MATERIAL);
    UnloadMaterial(GEOSPHERE_MATERIAL);
    UnloadMaterial(SUN_MATERIAL);
    UnloadMaterial(ASTEROID_MATERIAL);
    UnloadMaterial(CROSSHAIR_MATERIAL);
    UnloadMaterial(PROJECTILE_MATERIAL);

    UnloadModel(SPHERE_MODEL);
    UnloadModel(RED_FIGHTER_MODEL);
    unload_models(ASTEROID_MODELS);
}

}  // namespace gefest::resources
