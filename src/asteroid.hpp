#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::asteroid {

class Asteroid {
private:
    entt::entity entity;
    Matrix matrix;

public:
    Asteroid(entt::entity entity);

    void update();
};

Texture generate_geosphere_texture(int size);

}  // namespace gefest::asteroid
