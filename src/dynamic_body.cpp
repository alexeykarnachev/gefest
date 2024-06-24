#include "dynamic_body.hpp"

#include "constants.hpp"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest::dynamic_body {

DynamicBody::DynamicBody(
    entt::entity entity,
    float mass,
    float linear_damping,
    float moment_of_inertia,
    float angular_damping
)
    : entity(entity)
    , mass(mass)
    , linear_damping(linear_damping)
    , moment_of_inertia(moment_of_inertia)
    , angular_damping(angular_damping) {}

float DynamicBody::get_linear_speed() {
    return Vector3Length(this->linear_velocity);
}

float DynamicBody::get_angular_speed() {
    return Vector3Length(this->angular_velocity);
}

float DynamicBody::get_net_force_magnitude() {
    return Vector3Length(this->net_force);
}

float DynamicBody::get_net_torque_magnitude() {
    return Vector3Length(this->net_torque);
}

void DynamicBody::apply_force(Vector3 direction, float magnitude) {
    Vector3 force = Vector3Scale(Vector3Normalize(direction), magnitude);
    this->net_force = Vector3Add(this->net_force, force);
}

void DynamicBody::apply_torque(Vector3 magnitude) {
    this->net_torque = Vector3Add(this->net_torque, magnitude);
}

void DynamicBody::update() {
    auto &transform = registry::registry.get<transform::Transform>(this->entity);

    // Update linear velocity
    Vector3 damping_force = Vector3Scale(this->linear_velocity, -this->linear_damping);
    Vector3 net_force = Vector3Add(this->net_force, damping_force);
    Vector3 linear_acceleration = Vector3Scale(net_force, 1.0f / this->mass);
    this->linear_velocity = Vector3Add(
        this->linear_velocity, Vector3Scale(linear_acceleration, constants::DT)
    );
    this->net_force = Vector3Zero();

    // Update angular velocity
    Vector3 damping_torque = Vector3Scale(this->angular_velocity, -this->angular_damping);
    Vector3 net_torque = Vector3Add(this->net_torque, damping_torque);
    Vector3 angular_acceleration = Vector3Scale(
        net_torque, 1.0f / this->moment_of_inertia
    );
    this->angular_velocity = Vector3Add(
        this->angular_velocity, Vector3Scale(angular_acceleration, constants::DT)
    );
    this->net_torque = Vector3Zero();

    // Apply linear velocity
    Vector3 linear_step = Vector3Scale(this->linear_velocity, constants::DT);
    Vector3 position = Vector3Add(transform.position, linear_step);
    transform.position = position;
    if (Vector3Length(this->linear_velocity) < EPSILON) {
        this->linear_velocity = Vector3Zero();
    }

    // Apply angular velocity
    Vector3 angular_step = Vector3Scale(this->angular_velocity, constants::DT);
    transform.rotation = QuaternionMultiply(
        transform.rotation,
        QuaternionFromEuler(angular_step.x, angular_step.y, angular_step.z)
    );
    if (Vector3Length(this->angular_velocity) < EPSILON) {
        this->angular_velocity = Vector3Zero();
    }
}

}  // namespace gefest::dynamic_body
