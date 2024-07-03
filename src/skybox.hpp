#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::skybox {

class Skybox {
private:
    const entt::entity entity;
    Matrix matrix;

public:
    Skybox(entt::entity entity);

    void update();
};

Texture generate_geosphere_texture(
    int size,
    float stars_freq,
    float stars_min_brightness,
    float nebula_freq,
    float nebula_min_brightness
);

}  // namespace gefest::skybox
