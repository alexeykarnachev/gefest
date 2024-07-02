#pragma once

#include "entt/entity/fwd.hpp"
#include "ship.hpp"

namespace gefest::prefabs {

entt::entity spawn_red_fighter(Vector3 position, ship::ControllerType controller_type);

entt::entity spawn_projectile(entt::entity owner, float speed, float damage);

entt::entity spawn_asteroid(Vector3 position);
entt::entity spawn_planet(Vector3 position, float radius);
entt::entity spawn_sun(Vector3 position, float radius);
entt::entity spawn_skybox();

}  // namespace gefest::prefabs
