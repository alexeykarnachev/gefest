#include "projectile.hpp"

#include "constants.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest::projectile {

Projectile::Projectile(entt::entity entity, entt::entity owner, Vector3 velocity)
    : entity(entity)
    , owner(owner)
    , velocity(velocity) {}

void Projectile::update() {
    if (this->ttl <= 0.0) {
        registry::registry.destroy(this->entity);
        return;
    }

    auto &tr = registry::registry.get<transform::Transform>(this->entity);
    Vector3 step = Vector3Scale(this->velocity, constants::DT);
    Vector3 position = Vector3Add(tr.position, step);

    tr.position = position;
    this->ttl -= constants::DT;
}

void Projectile::draw() {
    auto tr = registry::registry.get<transform::Transform>(this->entity);

    DrawSphere(tr.position, 0.1, YELLOW);
}

}  // namespace gefest::projectile
