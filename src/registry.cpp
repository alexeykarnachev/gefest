#include "registry.hpp"

#include "dynamic_body.hpp"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "ship.hpp"
#include "transform.hpp"

namespace gefest {
namespace registry {

entt::registry registry;

entt::entity create_ship(Vector3 position, ship::ControllerType controller_type) {
    auto entity = registry::registry.create();

    ship::Ship ship(entity, controller_type);
    transform::Transform transform(position);
    dynamic_body::DynamicBody body(entity, 1000.0, 1000.0, 1.0, 10.0);

    registry::registry.emplace<ship::Ship>(entity, ship);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<dynamic_body::DynamicBody>(entity, body);

    return entity;
}

entt::entity create_player_ship(Vector3 position) {
    auto entity = create_ship(position, ship::ControllerType::MANUAL);
    registry::registry.emplace<Player>(entity);
    return entity;
}

}  // namespace registry
}  // namespace gefest
