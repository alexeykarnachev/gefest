#pragma once

#include "entt/entity/fwd.hpp"

namespace gefest {
namespace ship {

enum class ControllerType {
    MANUAL,
    DUMMY,
};

class Ship {
public:
    entt::entity entity;
    ControllerType controller_type;

    float max_torque = 30.0;
    float max_force = 4000.0;

    Ship(entt::entity entity, ControllerType controller_type);

    void update();
};

}  // namespace ship
}  // namespace gefest
