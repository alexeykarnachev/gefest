#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <cfloat>

namespace gefest::ship {

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

    float last_shot_time = -FLT_MAX;

    void reset_controls();
    void update_shooting();
    void update_manual_controller();
    void update_dummy_controller();
    void apply_controls();
    void update_matrix();

public:
    entt::entity entity;
    ControllerType controller_type;

    float engine_force;
    float pitch_magnitude;
    float roll_magnitude;

    Ship(
        entt::entity entity,
        ControllerType controller_type,
        float engine_force,
        float pitch_magnitude,
        float roll_magnitude
    );

    void update();
    void draw();
};

}  // namespace gefest::ship
