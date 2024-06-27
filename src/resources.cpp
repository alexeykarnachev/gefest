#include "resources.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <fstream>
#include <sstream>
#include <string>

namespace gefest::resources {

Mesh PLANE_MESH;
Mesh SPHERE_MESH;
Mesh CYLINDER_MESH;

Material GEOSPHERE_MATERIAL;
Material SKYBOX_MATERIAL;
Material CROSSHAIR_MATERIAL;
Material PROJECTILE_MATERIAL;
Material ASTEROID_MATERIAL;

Model RED_FIGHTER_MODEL;

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
    // plane mesh
    Mesh mesh = GenMeshPlane(1.0, 1.0, 1, 1);
    PLANE_MESH = mesh;

    // sphere mesh
    int n_rings = 64;
    int n_slices = 64;
    mesh = GenMeshSphere(1.0, n_rings, n_slices);
    SPHERE_MESH = mesh;

    // cylinder mesh
    mesh = GenMeshCylinder(1.0, 1.0, n_slices);
    CYLINDER_MESH = mesh;

    // geosphere material
    Material material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "geosphere.frag");
    GEOSPHERE_MATERIAL = material;

    // skybox material
    material = LoadMaterialDefault();
    material.shader = load_shader("skybox.vert", "skybox.frag");
    SKYBOX_MATERIAL = material;

    // crosshair material
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "crosshair.frag");
    CROSSHAIR_MATERIAL = material;

    // projectile material
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "projectile.frag");
    PROJECTILE_MATERIAL = material;

    // asteroid material
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "asteroid.frag");
    ASTEROID_MATERIAL = material;

    // red fighter model
    Model model = LoadModel("./resources/models/red_fighter/RedFighter.obj");
    model.transform = MatrixIdentity();
    RED_FIGHTER_MODEL = model;
}

void unload() {
    UnloadMesh(PLANE_MESH);
    UnloadMesh(SPHERE_MESH);

    UnloadMaterial(GEOSPHERE_MATERIAL);
    UnloadMaterial(SKYBOX_MATERIAL);
    UnloadMaterial(CROSSHAIR_MATERIAL);
    UnloadMaterial(PROJECTILE_MATERIAL);
    UnloadMaterial(ASTEROID_MATERIAL);

    UnloadModel(RED_FIGHTER_MODEL);
}

}  // namespace gefest::resources
