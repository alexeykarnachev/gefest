#include "skybox.hpp"

#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"

namespace gefest::skybox {

float STARS_FREQUENCY = 200.0;
float STARS_MIN_BRIGHTNESS = 0.9;

static float SKYBOX_RADIUS = 1000000.0;
static Matrix SKYBOX_MATRIX;

void update() {
    auto entity = registry::registry.view<registry::Player>().front();
    auto tr = registry::registry.get<transform::Transform>(entity);

    Matrix t = MatrixTranslate(tr.position.x, tr.position.y, tr.position.z);
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

    // draw sphere
    DrawMesh(mesh, material, SKYBOX_MATRIX);
}

}  // namespace gefest::skybox
