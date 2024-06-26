#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"

namespace gefest::projectile {

class Projectile {

public:
    entt::entity entity;
    entt::entity owner;

    Projectile(entt::entity entity, entt::entity owner, float speed);

    void update();
    void draw();

private:
    float ttl = 5.0;
    float speed;

    Matrix matrix = MatrixIdentity();
};

}  // namespace gefest::projectile
