#include "prefabs.hpp"

#include "asteroid.hpp"
#include "camera.hpp"
#include "collider.hpp"
#include "constants.hpp"
#include "dynamic_body.hpp"
#include "gmodel.hpp"
#include "health.hpp"
#include "light.hpp"
#include "planet.hpp"
#include "projectile.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "resources.hpp"
#include "skybox.hpp"
#include "sun.hpp"
#include "transform.hpp"

namespace gefest::prefabs {

entt::entity spawn_red_fighter(Vector3 position, ship::ControllerType controller_type) {
    static Vector3 scale = Vector3Scale(Vector3One(), constants::SCALE);

    static float mass = 20.0;
    static float linear_damping = 70.0;
    static float moment_of_inertia = 50.0;
    static float angular_damping = 600.0;

    static float engine_force = constants::SCALE * 1.5e4;
    static float pitch_magnitude = 500.0;
    static float roll_magnitude = 500.0;

    static float shoot_rate = 7.0;
    static float projectile_speed = constants::SCALE * 500.0;
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
    gmodel::GModel gmodel(
        entity,
        resources::RED_FIGHTER_MODEL,
        resources::MODEL_MATERIAL,
        resources::RED_FIGHTER_MODEL.materials[0].maps[0].texture,
        false
    );
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

// TODO: celestial body prefabs look pretty similar. Maybe factor out...
entt::entity spawn_asteroid(Vector3 position) {
    static Vector3 scale = Vector3Scale(Vector3One(), constants::SCALE * 10.0);
    static float collider_sphere_radius = constants::SCALE * 20.0;
    static float health_max_val = 1000.0;

    auto entity = registry::registry.create();

    int idx = GetRandomValue(0, resources::ASTEROID_MODELS.size() - 1);
    Model model = resources::ASTEROID_MODELS[idx];
    Material material = resources::ASTEROID_MATERIAL;
    Texture texture = asteroid::generate_geosphere_texture(4094);

    asteroid::Asteroid asteroid(entity);
    gmodel::GModel gmodel(entity, model, material, texture, false);
    transform::Transform transform(position, scale);
    collider::Collider collider(entity, collider_sphere_radius);
    health::Health health(entity, health_max_val);

    registry::registry.emplace<asteroid::Asteroid>(entity, asteroid);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<collider::Collider>(entity, collider);
    registry::registry.emplace<health::Health>(entity, health);

    return entity;
}

entt::entity spawn_planet(Vector3 position, float radius) {
    auto entity = registry::registry.create();

    Vector3 scale = Vector3Scale(Vector3One(), radius);
    Model model = resources::SPHERE_MODEL;
    Material material = resources::GEOSPHERE_MATERIAL;
    Texture texture = planet::generate_geosphere_texture(
        4094, 8, 1.84, 0.60, 1.27, 0.50, 0.51, 0.57, 0.61
    );

    planet::Planet planet(entity);
    gmodel::GModel gmodel(entity, model, material, texture, false);
    transform::Transform transform(position, scale);

    registry::registry.emplace<planet::Planet>(entity, planet);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);

    return entity;
}

entt::entity spawn_sun(Vector3 position, float radius) {
    static float point_light_intensity = 1.0;
    static Vector3 point_light_attenuation = {1.0, 0.0, 0.0};

    auto entity = registry::registry.create();

    Vector3 scale = Vector3Scale(Vector3One(), radius);
    Model model = resources::SPHERE_MODEL;
    Material material = resources::SUN_MATERIAL;
    Texture texture = sun::generate_geosphere_texture(4094);

    sun::Sun sun(entity);
    gmodel::GModel gmodel(entity, model, material, texture, false);
    transform::Transform transform(position, scale);
    light::PointLight point_light(
        entity, WHITE, point_light_attenuation, point_light_intensity
    );

    registry::registry.emplace<sun::Sun>(entity, sun);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<light::PointLight>(entity, point_light);

    return entity;
}

entt::entity spawn_skybox() {
    static Vector3 scale = Vector3Scale(Vector3One(), 1e4);
    static Color ambient_light_color = {255, 255, 255, 255};
    static float ambient_light_intensity = 0.075;

    auto entity = registry::registry.create();

    Vector3 position = camera::CAMERA.position;
    Model model = resources::SPHERE_MODEL;
    Material material = resources::SKYBOX_MATERIAL;
    Texture texture = skybox::generate_geosphere_texture(4094, 300.0, 0.83, 1.3, 0.3);

    skybox::Skybox skybox(entity);
    gmodel::GModel gmodel(entity, model, material, texture, true);
    transform::Transform transform(position, scale);
    light::AmbientLight ambient_light(
        entity, ambient_light_color, ambient_light_intensity
    );

    registry::registry.emplace<skybox::Skybox>(entity, skybox);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<light::AmbientLight>(entity, ambient_light);

    return entity;
}

}  // namespace gefest::prefabs
