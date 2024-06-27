#include "prefabs.hpp"

#include "asteroid.hpp"
#include "collider.hpp"
#include "constants.hpp"
#include "dynamic_body.hpp"
#include "gmodel.hpp"
#include "health.hpp"
#include "projectile.hpp"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"

namespace gefest::prefabs {

entt::entity spawn_red_fighter(Vector3 position, ship::ControllerType controller_type) {
    static Vector3 scale = {0.1, 0.1, 0.1};

    static float mass = 50.0;
    static float linear_damping = 70.0;
    static float moment_of_inertia = 50.0;
    static float angular_damping = 600.0;

    static float engine_force = 400.0;
    static float pitch_magnitude = 500.0;
    static float roll_magnitude = 500.0;

    static float shoot_rate = 7.0;
    static float projectile_speed = 80.0;
    static float projectile_damage = 500.0;
    static Vector3 projectile_spawn_offset = {0.0, 0.0, 0.0};

    auto entity = registry::registry.create();

    ship::Ship ship(
        entity,
        controller_type,
        engine_force,
        pitch_magnitude,
        roll_magnitude,
        shoot_rate,
        projectile_speed,
        projectile_damage,
        projectile_spawn_offset
    );
    gmodel::GModel gmodel(entity, resources::RED_FIGHTER_MODEL);
    transform::Transform transform(position, scale);
    dynamic_body::DynamicBody body(
        entity, mass, linear_damping, moment_of_inertia, angular_damping
    );

    registry::registry.emplace<ship::Ship>(entity, ship);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<dynamic_body::DynamicBody>(entity, body);

    return entity;
}

entt::entity spawn_projectile(
    entt::entity owner, transform::Transform transform, float speed, float damage
) {
    auto entity = registry::registry.create();

    projectile::Projectile projectile(entity, owner, speed, damage);

    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<projectile::Projectile>(entity, projectile);

    return entity;
}

entt::entity spawn_asteroid(Vector3 position) {
    static Vector3 scale = Vector3One();
    static float collider_sphere_radius = 2.0;
    static float health_max_val = 1000.0;

    auto entity = registry::registry.create();

    Mesh mesh = resources::get_asteroid_mesh();
    Material material = resources::ASTEROID_MATERIAL;

    asteroid::Asteroid asteroid(entity);
    gmodel::GMesh gmesh(entity, mesh, material);
    transform::Transform transform(position, scale);
    collider::Collider collider(entity, collider_sphere_radius);
    health::Health health(entity, health_max_val);

    registry::registry.emplace<asteroid::Asteroid>(entity, asteroid);
    registry::registry.emplace<gmodel::GMesh>(entity, gmesh);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<collider::Collider>(entity, collider);
    registry::registry.emplace<health::Health>(entity, health);

    return entity;
}

}  // namespace gefest::prefabs
