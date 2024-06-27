#pragma once

#include "entt/entity/fwd.hpp"
#include "ship.hpp"
#include "transform.hpp"

namespace gefest::prefabs {

entt::entity spawn_red_fighter(Vector3 position, ship::ControllerType controller_type);

entt::entity spawn_projectile(
    entt::entity owner, transform::Transform transform, float speed, float damage
);

entt::entity spawn_asteroid(Vector3 position);

}  // namespace gefest::prefabs
