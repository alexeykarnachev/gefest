#pragma once

#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "raylib/raylib.h"
#include "ship.hpp"

namespace gefest {
namespace registry {

extern entt::registry registry;

struct Player {};

entt::entity create_ship(Vector3 position, ship::ControllerType controller_type);
entt::entity create_player_ship(Vector3 position);

}  // namespace registry
}  // namespace gefest
