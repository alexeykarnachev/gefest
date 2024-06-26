#pragma once

#include "entt/entity/fwd.hpp"
#include "ship.hpp"

namespace gefest::prefabs {

entt::entity spawn_red_fighter(Vector3 position, ship::ControllerType controller_type);

}  // namespace gefest::prefabs
