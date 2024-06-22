#include "dynamic_body.hpp"

namespace gefest {
namespace dynamic_body {

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

void DynamicBody::apply_force(Vector3 direction, float magnitude) {}

void DynamicBody::apply_torque(Vector3 magnitude) {}

void DynamicBody::update() {}

}  // namespace dynamic_body
}  // namespace gefest
