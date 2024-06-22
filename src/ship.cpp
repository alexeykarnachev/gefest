#include "ship.hpp"

namespace gefest {
namespace ship {

Ship::Ship(entt::entity entity, ControllerType controller_type)
    : entity(entity)
    , controller_type(controller_type) {}

void Ship::update() {
}

}  // namespace ship
}  // namespace gefest
