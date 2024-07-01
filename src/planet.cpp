#include "planet.hpp"

#include "constants.hpp"
#include "drawing.hpp"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "resources.hpp"
#include <cstdio>

namespace gefest::planet {

Planet::Planet(entt::entity entity)
    : entity(entity) {}

void Planet::update() {}

// TODO: factor out texture generation function into a separate unit
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
    // TODO: this render texture should be registered
    // and cleaned up by resources manager
    RenderTexture render_texture = LoadRenderTexture(size, size);
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

    drawing::draw_texture(render_texture, shader);
    return render_texture.texture;
}

}  // namespace gefest::planet
