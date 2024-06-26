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
    void update_manual_controller();
    void update_dummy_controller();
    void apply_controls();
    void update_matrix();

    void shoot();

public:
    entt::entity entity;
    ControllerType controller_type;

    float engine_force;
    float pitch_magnitude;
    float roll_magnitude;

    float shoot_rate;
    float projectile_speed;
    Vector3 projectile_spawn_offset;

    Ship(
        entt::entity entity,
        ControllerType controller_type,
        float engine_force,
        float pitch_magnitude,
        float roll_magnitude,
        float shoot_rate,
        float projectile_speed,
        Vector3 projectile_spawn_offset
    );

    void update();
    void draw();
};

}  // namespace gefest::ship
