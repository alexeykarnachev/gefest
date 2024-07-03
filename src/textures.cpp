#include "textures.hpp"

#include "constants.hpp"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "resources.hpp"
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
    int n_levels_loc = GetShaderLocation(shader, "n_levels");
    int freq_mult_loc = GetShaderLocation(shader, "freq_mult");
    int ampl_mult_loc = GetShaderLocation(shader, "ampl_mult");
    int freq_init_loc = GetShaderLocation(shader, "freq_init");

    SetShaderValue(shader, n_levels_loc, &n_levels, SHADER_UNIFORM_INT);
    SetShaderValue(shader, freq_mult_loc, &freq_mult, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, ampl_mult_loc, &ampl_mult, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, freq_init_loc, &freq_init, SHADER_UNIFORM_FLOAT);

    // terrain uniforms
    int water_level_loc = GetShaderLocation(shader, "water_level");
    int sand_level_loc = GetShaderLocation(shader, "sand_level");
    int grass_level_loc = GetShaderLocation(shader, "grass_level");
    int rock_level_loc = GetShaderLocation(shader, "rock_level");

    SetShaderValue(shader, water_level_loc, &water_level, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, sand_level_loc, &sand_level, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, grass_level_loc, &grass_level, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, rock_level_loc, &rock_level, SHADER_UNIFORM_FLOAT);

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

    Texture texture = generate_texture(size, shader);
    return texture;
}

Texture generate_sun_texture(int size) {
    Texture texture = generate_texture(size, resources::SUN_TEXTURE_SHADER);
    return texture;
}

}  // namespace gefest::textures
