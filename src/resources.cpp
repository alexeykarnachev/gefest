#include "resources.hpp"

#include "light.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace gefest::resources {

Mesh PLANE_MESH;
Mesh SPHERE_MESH;
Mesh CYLINDER_MESH;

Shader GEOSPHERE_TEXTURE_SHADER;
Shader SKYBOX_TEXTURE_SHADER;
Shader SUN_TEXTURE_SHADER;

Material MODEL_MATERIAL;
Material CROSSHAIR_MATERIAL;
Material PROJECTILE_MATERIAL;
static Material SKYBOX_MATERIAL;
static Material SPHERE_MATERIAL;
static Material SUN_MATERIAL;

Model RED_FIGHTER_MODEL;
std::vector<Model> ASTEROID_MODELS;

namespace fs = std::filesystem;

std::vector<std::string> get_file_paths(const std::string &dir_path) {
    std::vector<std::string> file_paths;

    for (const auto &entry : fs::recursive_directory_iterator(dir_path)) {
        if (fs::is_regular_file(entry.path())) {
            file_paths.push_back(entry.path().string());
        }
    }

    return file_paths;
}

std::string get_shader_file_path(const std::string &file_name) {
    auto file_path = "resources/shaders/" + file_name;
    return file_path;
}

std::string load_shader_src(const std::string &file_name) {
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

Shader load_shader(const std::string &vs_file_name, const std::string &fs_file_name) {
    std::string vs, fs;

    vs = load_shader_src(vs_file_name);
    fs = load_shader_src(fs_file_name);
    Shader shader = LoadShaderFromMemory(vs.c_str(), fs.c_str());

    return shader;
}

void load() {
    // plane
    Mesh mesh = GenMeshPlane(1.0, 1.0, 1, 1);
    PLANE_MESH = mesh;

    // sphere
    int n_rings = 64;
    int n_slices = 64;
    mesh = GenMeshSphere(1.0, n_rings, n_slices);
    SPHERE_MESH = mesh;

    // cylinder
    mesh = GenMeshCylinder(1.0, 1.0, n_slices);
    CYLINDER_MESH = mesh;

    Shader shader;
    Model model;
    Material material;

    // geosphere texture shader
    shader = load_shader("screen_rect.vert", "geosphere_texture.frag");
    GEOSPHERE_TEXTURE_SHADER = shader;

    // skybox texture shader
    shader = load_shader("screen_rect.vert", "skybox_texture.frag");
    SKYBOX_TEXTURE_SHADER = shader;

    // skybox texture shader
    shader = load_shader("screen_rect.vert", "sun_texture.frag");
    SUN_TEXTURE_SHADER = shader;

    // model
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "model.frag");
    MODEL_MATERIAL = material;

    // skybox
    material = LoadMaterialDefault();
    material.shader = load_shader("skybox.vert", "skybox.frag");
    SKYBOX_MATERIAL = material;

    // sphere
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "sphere.frag");
    SPHERE_MATERIAL = material;

    // sun
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "sphere.frag");
    SUN_MATERIAL = material;

    // crosshair
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "crosshair.frag");
    CROSSHAIR_MATERIAL = material;

    // projectile
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "projectile.frag");
    PROJECTILE_MATERIAL = material;

    // asteroids
    for (auto file_path : get_file_paths("./resources/models/asteroids")) {
        model = LoadModel(file_path.c_str());
        model.materials[0].shader = load_shader("base.vert", "model.frag");
        ASTEROID_MODELS.push_back(model);
    }

    // red fighter
    model = LoadModel("./resources/models/red_fighter/RedFighter.obj");
    model.transform = MatrixIdentity();
    model.materials[0].shader = load_shader("base.vert", "model.frag");
    RED_FIGHTER_MODEL = model;
}

void unload() {
    UnloadMesh(PLANE_MESH);
    UnloadMesh(SPHERE_MESH);

    UnloadShader(SKYBOX_TEXTURE_SHADER);
    UnloadShader(GEOSPHERE_TEXTURE_SHADER);

    UnloadMaterial(MODEL_MATERIAL);
    UnloadMaterial(SKYBOX_MATERIAL);
    UnloadMaterial(SPHERE_MATERIAL);
    UnloadMaterial(SUN_MATERIAL);
    UnloadMaterial(CROSSHAIR_MATERIAL);
    UnloadMaterial(PROJECTILE_MATERIAL);

    UnloadModel(RED_FIGHTER_MODEL);
    for (auto model : ASTEROID_MODELS) {
        UnloadModel(model);
    }
}

Material get_skybox_material(Texture texture) {
    Material material = resources::SKYBOX_MATERIAL;

    material.maps[0].texture = texture;

    return material;
}

Material get_sphere_material(Texture texture) {
    Material material = resources::SPHERE_MATERIAL;
    material.maps[0].texture = texture;
    int is_light_disabled = 1;

    int is_light_disabled_loc = GetShaderLocation(material.shader, "is_light_disabled");

    SetShaderValue(
        material.shader, is_light_disabled_loc, &is_light_disabled, SHADER_UNIFORM_INT
    );

    return material;
}

Material get_sphere_material(Texture texture, light::PointLight point_light) {
    Material material = resources::SPHERE_MATERIAL;
    material.maps[0].texture = texture;
    int is_light_disabled = 0;

    int is_light_disabled_loc = GetShaderLocation(material.shader, "is_light_disabled");

    SetShaderValue(
        material.shader, is_light_disabled_loc, &is_light_disabled, SHADER_UNIFORM_INT
    );
    point_light.set_shader_uniform(material.shader);

    return material;
}

Model get_asteroid_model() {
    int n_models = ASTEROID_MODELS.size();
    int idx = GetRandomValue(0, n_models - 1);
    return ASTEROID_MODELS[idx];
}

}  // namespace gefest::resources
