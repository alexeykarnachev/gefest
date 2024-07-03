#pragma once

#include "raylib/raylib.h"

namespace gefest::textures {

Texture generate_texture(int size, Shader shader);
Texture generate_asteroid_texture(int size);
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
);
Texture generate_skybox_texture(
    int size,
    float stars_freq,
    float stars_min_brightness,
    float nebula_freq,
    float nebula_min_brightness
);
Texture generate_sun_texture(int size);

}  // namespace gefest::textures
