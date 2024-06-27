#include "asteroid.hpp"

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"
#include "registry.hpp"
#include "transform.hpp"
#include <cstdio>

namespace gefest::asteroid {

Asteroid::Asteroid(entt::entity entity)
    : entity(entity) {}

void Asteroid::update() {}

void Asteroid::draw() {
    static float radius = 1.0;

    auto &tr = registry::registry.get<transform::Transform>(this->entity);

    DrawSphere(tr.position, radius, BROWN);
}

}  // namespace gefest::asteroid
