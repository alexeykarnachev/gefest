#include "prefabs.hpp"

#include "dynamic_body.hpp"
#include "projectile.hpp"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest::prefabs {

entt::entity spawn_red_fighter(Vector3 position, ship::ControllerType controller_type) {
    static float mass = 50.0;
    static float linear_damping = 70.0;
    static float moment_of_inertia = 50.0;
    static float angular_damping = 600.0;
    static float engine_force = 400.0;
    static float pitch_magnitude = 500.0;
    static float roll_magnitude = 500.0;
    static float shoot_rate = 2.5;
    static Vector3 projectile_spawn_position = {0.0, 0.0, 0.0};

    auto entity = registry::registry.create();

    ship::Ship ship(
        entity,
        controller_type,
        engine_force,
        pitch_magnitude,
        roll_magnitude,
        shoot_rate,
        projectile_spawn_position
    );
    transform::Transform transform(position);
    dynamic_body::DynamicBody body(
        entity, mass, linear_damping, moment_of_inertia, angular_damping
    );

    registry::registry.emplace<ship::Ship>(entity, ship);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<dynamic_body::DynamicBody>(entity, body);

    return entity;
}

entt::entity spawn_red_fighter_projectile(
    entt::entity owner, Vector3 position, Vector3 direction
) {
    static float speed = 200.0;

    direction = Vector3Normalize(direction);
    Vector3 velocity = Vector3Scale(direction, speed);

    auto entity = registry::registry.create();

    transform::Transform transform(position);
    projectile::Projectile projectile(entity, owner, velocity);

    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<projectile::Projectile>(entity, projectile);

    return entity;
}

}  // namespace gefest::prefabs
