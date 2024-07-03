#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::planet {

class Planet {
private:
    const entt::entity entity;
    Matrix matrix;

public:
    Planet(entt::entity entity);

    void update();
};

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

}  // namespace gefest::planet
