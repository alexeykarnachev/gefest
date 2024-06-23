#include "resources.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <fstream>
#include <sstream>
#include <string>

namespace gefest {
namespace resources {

Mesh SPHERE_MESH;

Material GEOSPHERE_MATERIAL;
static Material MODEL_MATERIAL;

Model RED_FIGHTER_MODEL;

static float RED_FIGHTER_SCALE = 0.1;

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
    // sphere mesh
    int n_rings = 64;
    int n_slices = 64;
    Mesh mesh = GenMeshSphere(1.0, n_rings, n_slices);
    SPHERE_MESH = mesh;

    // geosphere material
    Material material = LoadMaterialDefault();
    material.shader = load_shader("base.vert", "geosphere.frag");
    GEOSPHERE_MATERIAL = material;

    // model material
    int n_materials;
    Material *materials = LoadMaterials(
        "./resources/models/red_fighter/RedFighter.mtl", &n_materials
    );
    material = materials[0];
    material.shader = load_shader("base.vert", "model.frag");
    MODEL_MATERIAL = material;

    // red fighter model
    Model model = LoadModel("./resources/models/red_fighter/RedFighter.obj");
    model.materials[0] = MODEL_MATERIAL;
    Matrix mat = MatrixScale(RED_FIGHTER_SCALE, RED_FIGHTER_SCALE, RED_FIGHTER_SCALE);
    model.transform = mat;
    RED_FIGHTER_MODEL = model;
}

void unload() {
    UnloadMesh(SPHERE_MESH);
    UnloadMaterial(GEOSPHERE_MATERIAL);
    UnloadMaterial(MODEL_MATERIAL);
    UnloadModel(RED_FIGHTER_MODEL);
}

}  // namespace resources

}  // namespace gefest
