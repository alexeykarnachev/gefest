#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest {
namespace dynamic_body {

class DynamicBody {
public:
    entt::entity entity;

    Vector3 linear_velocity = {0.0, 0.0, 0.0};
    Vector3 angular_velocity = {0.0, 0.0, 0.0};
    Vector3 net_force = {0.0, 0.0, 0.0};
    Vector3 net_torque = {0.0, 0.0, 0.0};

    float mass;
    float linear_damping;

    float moment_of_inertia;
    float angular_damping;

    DynamicBody(
        entt::entity entity,
        float mass,
        float linear_damping,
        float moment_of_inertia,
        float angular_damping
    );

    void apply_force(Vector3 direction, float magnitude);
    void apply_torque(Vector3 magnitude);

    void update();
};

}  // namespace dynamic_body
}  // namespace gefest