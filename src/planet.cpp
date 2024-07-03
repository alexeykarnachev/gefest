#include "planet.hpp"

#include "constants.hpp"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "transform.hpp"
#include <cstdio>

namespace gefest::planet {

Planet::Planet(entt::entity entity)
    : entity(entity) {}

void Planet::update() {
    static float rotation_step = 0.001 * PI * constants::DT;

    auto &tr = registry::registry.get<transform::Transform>(this->entity);

    tr.rotate_y(rotation_step);
}

}  // namespace gefest::planet
