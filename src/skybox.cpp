#include "skybox.hpp"

#include "camera.hpp"
#include "raylib/raymath.h"
#include "resources.hpp"

namespace gefest::skybox {

float STARS_FREQUENCY = 300.0;
float STARS_MIN_BRIGHTNESS = 0.83;

float NEBULA_FREQUENCY = 1.3;
float NEBULA_MIN_BRIGHTNESS = 0.3;

static float SKYBOX_RADIUS = 1000000.0;
static Matrix SKYBOX_MATRIX = MatrixIdentity();

void update() {
    Vector3 position = camera::CAMERA.position;

    Matrix t = MatrixTranslate(position.x, position.y, position.z);
    Matrix s = MatrixScale(SKYBOX_RADIUS, SKYBOX_RADIUS, SKYBOX_RADIUS);

    SKYBOX_MATRIX = MatrixMultiply(s, t);
}

void draw() {
    auto mesh = resources::SPHERE_MESH;
    auto material = resources::SKYBOX_MATERIAL;
    auto shader = material.shader;

    // stars uniforms
    int stars_frequency_loc = GetShaderLocation(shader, "stars_frequency");
    int stars_min_brightness_loc = GetShaderLocation(shader, "stars_min_brightness");

    SetShaderValue(shader, stars_frequency_loc, &STARS_FREQUENCY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(
        shader, stars_min_brightness_loc, &STARS_MIN_BRIGHTNESS, SHADER_UNIFORM_FLOAT
    );

    // nebula uniforms
    int nebula_frequency_loc = GetShaderLocation(shader, "nebula_frequency");
    int nebula_min_brightness_loc = GetShaderLocation(shader, "nebula_min_brightness");

    SetShaderValue(shader, nebula_frequency_loc, &NEBULA_FREQUENCY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(
        shader, nebula_min_brightness_loc, &NEBULA_MIN_BRIGHTNESS, SHADER_UNIFORM_FLOAT
    );

    // draw sphere
    DrawMesh(mesh, material, SKYBOX_MATRIX);
}

}  // namespace gefest::skybox