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

}  // namespace gefest::planet
