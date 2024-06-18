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

static float RADIUS = 5.0;
static Vector3 POSITION = {0.0, 5.0, 0.0};

static Mesh SPHERE;
static Material MATERIAL;

void load() {
    int n_rings = 64;
    int n_slices = 64;
    SPHERE = GenMeshSphere(RADIUS, n_rings, n_slices);

    MATERIAL = LoadMaterialDefault();
    MATERIAL.shader = shaders::load_shader("base.vert", "planet.frag");
}

void unload() {
    UnloadMesh(SPHERE);
}

void draw() {
    // tmp: keep sun here for now
    Vector3 sun_position = {20.0, 20.0, 20.0};
    DrawSphere(sun_position, 2.0, RED);

    auto shader = MATERIAL.shader;

    // perlin noise uniforms
    int n_levels_loc = GetShaderLocation(shader, "n_levels");
    int freq_mult_loc = GetShaderLocation(shader, "freq_mult");
    int ampl_mult_loc = GetShaderLocation(shader, "ampl_mult");
    int freq_init_loc = GetShaderLocation(shader, "freq_init");

    SetShaderValue(shader, n_levels_loc, &N_LEVELS, SHADER_UNIFORM_INT);
    SetShaderValue(shader, freq_mult_loc, &FREQ_MULT, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampl_mult_loc, &AMPL_MULT, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, freq_init_loc, &FREQ_INIT, SHADER_UNIFORM_FLOAT);

    // terrain uniforms
    int water_level_loc = GetShaderLocation(shader, "water_level");
    int sand_level_loc = GetShaderLocation(shader, "sand_level");
    int grass_level_loc = GetShaderLocation(shader, "grass_level");
    int rock_level_loc = GetShaderLocation(shader, "rock_level");

    SetShaderValue(shader, water_level_loc, &WATER_LEVEL, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, sand_level_loc, &SAND_LEVEL, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, grass_level_loc, &GRASS_LEVEL, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, rock_level_loc, &ROCK_LEVEL, SHADER_UNIFORM_FLOAT);

    // geometry uniforms
    int planet_radius_loc = GetShaderLocation(shader, "planet_radius");
    int planet_position_loc = GetShaderLocation(shader, "planet_position");
    int sun_position_loc = GetShaderLocation(shader, "sun_position");

    SetShaderValue(shader, planet_radius_loc, &RADIUS, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, planet_position_loc, &POSITION, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, sun_position_loc, &sun_position, SHADER_UNIFORM_VEC3);

    // sphere transformation
    Matrix translate = MatrixTranslate(POSITION.x, POSITION.y, POSITION.z);
    Matrix transform = translate;

    // draw planet
    DrawMesh(SPHERE, MATERIAL, transform);
}

}  // namespace planet
}  // namespace gefest
