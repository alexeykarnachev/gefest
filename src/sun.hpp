#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::sun {

class Sun {
private:
    const entt::entity entity;
    Matrix matrix;

public:
    Sun(entt::entity entity);

    void update();
};

}  // namespace gefest::sun
