#include "sun.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "resources.hpp"

namespace gefest::sun {

Vector3 POSITION = {600.0, 500.0, -600.0};
static float RADIUS = 50.0;

static Color COLOR = {255, 240, 255, 255};
static Vector3 ATTENUATION = {1.0, 0.0, 0.0};
static float INTENSITY = 1.0;

static Matrix MATRIX;

void set_shader_point_light(Shader shader) {
    int color_loc = GetShaderLocation(shader, "point_light.color");
    int position_loc = GetShaderLocation(shader, "point_light.position");
    int attenuation_loc = GetShaderLocation(shader, "point_light.attenuation");
    int intensity_loc = GetShaderLocation(shader, "point_light.intensity");

    auto color = ColorNormalize(COLOR);

    SetShaderValue(shader, color_loc, &color, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, position_loc, &POSITION, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, attenuation_loc, &ATTENUATION, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, intensity_loc, &INTENSITY, SHADER_UNIFORM_FLOAT);
}

void update() {
    Matrix t = MatrixTranslate(POSITION.x, POSITION.y, POSITION.z);
    Matrix s = MatrixScale(RADIUS, RADIUS, RADIUS);

    MATRIX = MatrixMultiply(s, t);
}

void draw_geosphere() {
    Mesh mesh = resources::SPHERE_MESH;
    Material material = resources::SUN_MATERIAL;

    // draw sphere
    DrawMesh(mesh, material, MATRIX);
}

void draw() {
    draw_geosphere();
}

}  // namespace gefest::sun
