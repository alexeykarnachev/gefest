#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"

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

    Matrix matrix = MatrixIdentity();

    void reset_controls();
    void update_manual_controller();
    void update_dummy_controller();
    void apply_controls();
    void update_matrix();

public:
    entt::entity entity;
    ControllerType controller_type;

    float max_engine_force = 1000.0;
    float max_pitch_magnitude = 30.0;
    float max_roll_magnitude = 15.0;

    Ship(entt::entity entity, ControllerType controller_type);

    void update();
    void draw();
};

}  // namespace ship
}  // namespace gefest
