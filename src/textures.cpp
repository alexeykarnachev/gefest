#include "textures.hpp"

#include "constants.hpp"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "resources.hpp"
#include "utils.hpp"
#include <cstdio>

namespace gefest::textures {

// NOTE: the fragment shader of the `shader` must be `screen_rect.vert`
Texture generate_texture(int size, Shader shader) {
    RenderTexture render_texture = LoadRenderTexture(size, size);

    // render
    {
        rlDisableBackfaceCulling();
        BeginTextureMode(render_texture);
        BeginShaderMode(shader);

        DrawRectangle(0, 0, 1, 1, BLANK);

        EndShaderMode();
        EndTextureMode();

        rlEnableBackfaceCulling();

        SetTextureFilter(render_texture.texture, TEXTURE_FILTER_BILINEAR);
    }

    Image image = LoadImageFromTexture(render_texture.texture);
    Texture texture = LoadTextureFromImage(image);
    UnloadRenderTexture(render_texture);

    return texture;
}

Texture generate_asteroid_texture(int size) {
    Texture texture = generate_texture(size, resources::ASTEROID_TEXTURE_SHADER);
    return texture;
}

Texture generate_geosphere_texture(
    int size,
    int n_levels,
    float freq_mult,
    float ampl_mult,
    float freq_init,
    float water_level,
    float sand_level,
    float grass_level,
    float rock_level
) {
    auto shader = resources::GEOSPHERE_TEXTURE_SHADER;

    // perlin noise uniforms
    utils::shader::set_int(shader, "n_levels", n_levels);
    utils::shader::set_float(shader, "freq_mult", freq_mult);
    utils::shader::set_float(shader, "ampl_mult", ampl_mult);
    utils::shader::set_float(shader, "freq_init", freq_init);

    // terrain uniforms
    utils::shader::set_float(shader, "water_level", water_level);
    utils::shader::set_float(shader, "sand_level", sand_level);
    utils::shader::set_float(shader, "grass_level", grass_level);
    utils::shader::set_float(shader, "rock_level", rock_level);

    Texture texture = generate_texture(size, shader);
    return texture;
}

Texture generate_skybox_texture(
    int size,
    float stars_freq,
    float stars_min_brightness,
    float nebula_freq,
    float nebula_min_brightness
) {
    auto shader = resources::SKYBOX_TEXTURE_SHADER;

    // stars uniforms
    utils::shader::set_float(shader, "stars_freq", stars_freq);
    utils::shader::set_float(shader, "stars_min_brightness", stars_min_brightness);

    // nebula uniforms
    utils::shader::set_float(shader, "nebula_freq", nebula_freq);
    utils::shader::set_float(shader, "nebula_min_brightness", nebula_min_brightness);

    Texture texture = generate_texture(size, shader);
    return texture;
}

Texture generate_sun_texture(int size) {
    Texture texture = generate_texture(size, resources::SUN_TEXTURE_SHADER);
    return texture;
}

}  // namespace gefest::textures
