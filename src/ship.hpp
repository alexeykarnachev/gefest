#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest {
namespace ship {

enum class ControllerType {
    MANUAL,
    DUMMY,
};

class Ship {
private:
    float thrust = 0.0;
    float roll = 0.0;
    float pitch = 0.0;

    Matrix matrix;

    void reset_controls();
    void update_manual();
    void update_dummy();
    void apply_controls();
    void update_matrix();

public:
    entt::entity entity;
    ControllerType controller_type;

    float max_engine_force = 4000.0;

    Ship(entt::entity entity, ControllerType controller_type);

    void update();
    void draw();
};

}  // namespace ship
}  // namespace gefest
