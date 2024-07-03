#pragma once

#include "entt/entity/fwd.hpp"

namespace gefest::projectile {

class Projectile {

public:
    const entt::entity entity;
    const entt::entity owner;

    Projectile(entt::entity entity, entt::entity owner, float speed, float damage);

    void update();

private:
    float ttl = 5.0;
    float speed;
    float damage;
};

}  // namespace gefest::projectile
