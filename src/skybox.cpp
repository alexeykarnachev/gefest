#include "skybox.hpp"

#include "camera.hpp"
#include "drawing.hpp"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"

namespace gefest::skybox {

Skybox::Skybox(entt::entity entity)
    : entity(entity) {}

void Skybox::update() {
    auto &tr = registry::registry.get<transform::Transform>(entity);
    tr.position = camera::CAMERA.position;
}

// TODO: factor out texture generation function into a separate unit
Texture generate_geosphere_texture(
    int size,
    float stars_freq,
    float stars_min_brightness,
    float nebula_freq,
    float nebula_min_brightness
) {
    // TODO: this render texture should be registered
    // and cleaned up by resources manager
    RenderTexture render_texture = LoadRenderTexture(size, size);
    auto shader = resources::SKYBOX_TEXTURE_SHADER;

    // stars uniforms
    int stars_freq_loc = GetShaderLocation(shader, "stars_freq");
    int stars_min_brightness_loc = GetShaderLocation(shader, "stars_min_brightness");

    SetShaderValue(shader, stars_freq_loc, &stars_freq, SHADER_UNIFORM_FLOAT);
    SetShaderValue(
        shader, stars_min_brightness_loc, &stars_min_brightness, SHADER_UNIFORM_FLOAT
    );

    // nebula uniforms
    int nebula_freq_loc = GetShaderLocation(shader, "nebula_freq");
    int nebula_min_brightness_loc = GetShaderLocation(shader, "nebula_min_brightness");

    SetShaderValue(shader, nebula_freq_loc, &nebula_freq, SHADER_UNIFORM_FLOAT);
    SetShaderValue(
        shader, nebula_min_brightness_loc, &nebula_min_brightness, SHADER_UNIFORM_FLOAT
    );

    drawing::draw_texture(render_texture, shader);
    return render_texture.texture;
}

}  // namespace gefest::skybox
