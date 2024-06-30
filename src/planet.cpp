#include "planet.hpp"

#include "constants.hpp"
#include "drawing.hpp"
#include "light.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "resources.hpp"
#include "sun.hpp"
#include <cstdio>

namespace gefest::planet {

Vector3 POSITION = {0.0, 0.0, 0.0};
float GEOSPHERE_RADIUS = constants::SCALE * 3e4;

int N_LEVELS = 8;
float FREQ_MULT = 1.84;
float AMPL_MULT = 0.60;
float FREQ_INIT = 1.27;

float WATER_LEVEL = 0.50;
float SAND_LEVEL = 0.51;
float GRASS_LEVEL = 0.57;
float ROCK_LEVEL = 0.61;

static float PLANET_ROTATION_SPEED = 0.001 * PI;

static int RENDER_TEXTURE_SIZE = 4096;
static RenderTexture RENDER_TEXTURE;
static Matrix MATRIX;

void generate() {
    if (IsRenderTextureReady(RENDER_TEXTURE)) {
        UnloadRenderTexture(RENDER_TEXTURE);
    }

    RENDER_TEXTURE = LoadRenderTexture(RENDER_TEXTURE_SIZE, RENDER_TEXTURE_SIZE);
    auto shader = resources::GEOSPHERE_TEXTURE_SHADER;

    rlDisableBackfaceCulling();
    BeginTextureMode(RENDER_TEXTURE);
    BeginShaderMode(shader);

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

    DrawRectangle(0, 0, 1, 1, BLANK);

    EndShaderMode();
    EndTextureMode();

    rlEnableBackfaceCulling();

    SetTextureFilter(RENDER_TEXTURE.texture, TEXTURE_FILTER_BILINEAR);
}

void update() {
    float rotation_angle = PLANET_ROTATION_SPEED * GetTime();

    Matrix t = MatrixTranslate(POSITION.x, POSITION.y, POSITION.z);
    Matrix r = MatrixRotate({0.0, 1.0, 0.0}, rotation_angle);
    Matrix s = MatrixScale(GEOSPHERE_RADIUS, GEOSPHERE_RADIUS, GEOSPHERE_RADIUS);

    MATRIX = MatrixMultiply(MatrixMultiply(r, s), t);
}

void draw() {
    light::PointLight point_light = sun::get_point_light();
    Texture texture = RENDER_TEXTURE.texture;
    drawing::draw_sphere(texture, MATRIX, point_light);
}

}  // namespace gefest::planet
