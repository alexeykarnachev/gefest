#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::projectile {

class Projectile {

public:
    entt::entity entity;
    entt::entity owner;

    Projectile(entt::entity entity, entt::entity owner, Vector3 velocity);

    void update();
    void draw();

private:
    float ttl = 5.0;
    Vector3 velocity;
};

}  // namespace gefest::projectile
