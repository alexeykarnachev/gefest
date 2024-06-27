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

Material SUN_MATERIAL;
Material GEOSPHERE_MATERIAL;
Material SKYBOX_MATERIAL;
Material CROSSHAIR_MATERIAL;
Material PROJECTILE_MATERIAL;
Material ASTEROID_MATERIAL;

Model RED_FIGHTER_MODEL;
static Model ASTEROID_MODEL;

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

    Model model;
    Material material;

    // geosphere
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "sun.frag");
    SUN_MATERIAL = material;

    // geosphere
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "geosphere.frag");
    GEOSPHERE_MATERIAL = material;

    // skybox
    material = LoadMaterialDefault();
    material.shader = load_shader("skybox.vert", "skybox.frag");
    SKYBOX_MATERIAL = material;

    // crosshair
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "crosshair.frag");
    CROSSHAIR_MATERIAL = material;

    // projectile
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "projectile.frag");
    PROJECTILE_MATERIAL = material;

    // asteroid
    model = LoadModel("./resources/models/asteroids/asteroids.obj");
    material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "asteroid.frag");
    ASTEROID_MODEL = model;
    ASTEROID_MATERIAL = material;

    // red fighter
    model = LoadModel("./resources/models/red_fighter/RedFighter.obj");
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
    UnloadModel(ASTEROID_MODEL);
}

Mesh get_asteroid_mesh() {
    int n_meshes = ASTEROID_MODEL.meshCount;
    int idx = GetRandomValue(0, n_meshes - 1);
    return ASTEROID_MODEL.meshes[idx];
}

}  // namespace gefest::resources
