#include "planet.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "shaders.hpp"

namespace gefest {
namespace planet {

int N_LEVELS = 8;
float FREQ_MULT = 2.0;
float AMPL_MULT = 0.5;
float FREQ_INIT = 1.0;

float WATER_LEVEL = 0.5;
float SAND_LEVEL = 0.6;
float GRASS_LEVEL = 0.7;
float ROCK_LEVEL = 0.8;

static Vector3 POSITION = {.x = 0.0, .y = 5.0, .z = 0.0};
static Mesh SPHERE;
static Material MATERIAL;

void load() {
    float radius = 4.5;
    int n_rings = 64;
    int n_slices = 64;
    SPHERE = GenMeshSphere(radius, n_rings, n_slices);

    MATERIAL = LoadMaterialDefault();
    MATERIAL.shader = shaders::load_shader("base.vert", "planet.frag");
}

void unload() {
    UnloadMesh(SPHERE);
}

void draw() {
    auto shader = MATERIAL.shader;

    // perlin noise parameters
    int n_levels_loc = GetShaderLocation(shader, "n_levels");
    int freq_mult_loc = GetShaderLocation(shader, "freq_mult");
    int ampl_mult_loc = GetShaderLocation(shader, "ampl_mult");
    int freq_init_loc = GetShaderLocation(shader, "freq_init");

    SetShaderValue(shader, n_levels_loc, &N_LEVELS, SHADER_UNIFORM_INT);
    SetShaderValue(shader, freq_mult_loc, &FREQ_MULT, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampl_mult_loc, &AMPL_MULT, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, freq_init_loc, &FREQ_INIT, SHADER_UNIFORM_FLOAT);

    // terrain parameters
    int water_level_loc = GetShaderLocation(shader, "water_level");
    int sand_level_loc = GetShaderLocation(shader, "sand_level");
    int grass_level_loc = GetShaderLocation(shader, "grass_level");
    int rock_level_loc = GetShaderLocation(shader, "rock_level");

    SetShaderValue(shader, water_level_loc, &WATER_LEVEL, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, sand_level_loc, &SAND_LEVEL, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, grass_level_loc, &GRASS_LEVEL, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, rock_level_loc, &ROCK_LEVEL, SHADER_UNIFORM_FLOAT);

    // sphere transformation
    Matrix translate = MatrixTranslate(POSITION.x, POSITION.y, POSITION.z);
    Matrix transform = translate;

    // draw planet
    DrawMesh(SPHERE, MATERIAL, transform);
}

}  // namespace planet
}  // namespace gefest
