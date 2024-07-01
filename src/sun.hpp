#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::sun {

class Sun {
private:
    entt::entity entity;
    Matrix matrix;

public:
    Sun(entt::entity entity);

    void update();
};

Texture generate_geosphere_texture(int size);

}  // namespace gefest::sun
