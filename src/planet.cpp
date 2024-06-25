#include "planet.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "resources.hpp"

namespace gefest::planet {

Vector3 PLANET_POSITION = {0.0, 0.0, 0.0};

int N_LEVELS = 8;
float FREQ_MULT = 1.84;
float AMPL_MULT = 0.60;
float FREQ_INIT = 1.27;

float WATER_LEVEL = 0.50;
float SAND_LEVEL = 0.51;
float GRASS_LEVEL = 0.57;
float ROCK_LEVEL = 0.61;

static float GEOSPHERE_RADIUS = 50.0;
static float PLANET_ROTATION_SPEED = 0.001 * PI;
static Vector3 SUN_POSITION = {100.0, 100.0, 100.0};

static Matrix MATRIX;

void update() {
    float rotation_angle = PLANET_ROTATION_SPEED * GetTime();

    Matrix t = MatrixTranslate(PLANET_POSITION.x, PLANET_POSITION.y, PLANET_POSITION.z);
    Matrix r = MatrixRotate({0.0, 1.0, 0.0}, rotation_angle);
    Matrix s = MatrixScale(GEOSPHERE_RADIUS, GEOSPHERE_RADIUS, GEOSPHERE_RADIUS);

    MATRIX = MatrixMultiply(MatrixMultiply(r, s), t);
}

void draw_planet_body() {
    // tmp: keep sun here for now
    DrawSphere(SUN_POSITION, 2.0, RED);

    Mesh mesh = resources::SPHERE_MESH;
    Material material = resources::GEOSPHERE_MATERIAL;
    Shader shader = material.shader;

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
    int planet_radius_loc = GetShaderLocation(shader, "geosphere_radius");
    int planet_position_loc = GetShaderLocation(shader, "planet_position");
    int sun_position_loc = GetShaderLocation(shader, "sun_position");

    SetShaderValue(shader, planet_radius_loc, &GEOSPHERE_RADIUS, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, planet_position_loc, &PLANET_POSITION, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, sun_position_loc, &SUN_POSITION, SHADER_UNIFORM_VEC3);

    // draw sphere
    DrawMesh(mesh, material, MATRIX);
}

void draw() {
    draw_planet_body();
}

}  // namespace gefest::planet
