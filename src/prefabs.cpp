#include "prefabs.hpp"

#include "asteroid.hpp"
#include "camera.hpp"
#include "collider.hpp"
#include "constants.hpp"
#include "crosshair.hpp"
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
#include "ship.hpp"
#include "skybox.hpp"
#include "sun.hpp"
#include "transform.hpp"

namespace gefest::prefabs {

entt::entity spawn_red_fighter(Vector3 position, ship::ControllerType controller_type) {
    auto entity = registry::registry.create();

    ship::Ship ship(
        entity,
        controller_type,
        constants::SCALE * 1.5e4,  // engine_force
        500.0,  // pitch_magnitude
        500.0,  // roll_magnitude
        7.0,  // shoot_rate
        constants::SCALE * 500.0,  // projectile_speed
        500.0,  // projectile_damage
        {0.0, 0.0, 0.0}  // projectile_spawn_offset
    );
    crosshair::Crosshair crosshair(
        entity,
        {constants::SCALE * 1.15f, 0.0, -constants::SCALE * 0.08f},  // start_offset
        constants::SCALE * 1e3,  // length
        constants::SCALE * 0.05f,  // thickness
        15.0,  // attenuation
        0.95  // start_alpha
    );
    dynamic_body::DynamicBody body(
        entity,
        20.0,  // mass
        70.0,  // linear_damping
        50.0,  // moment_of_inertia
        600.0  // angular_damping
    );
    gmodel::GModel gmodel(
        entity,
        resources::RED_FIGHTER_MODEL,
        resources::RED_FIGHTER_MATERIAL,
        resources::RED_FIGHTER_MODEL.materials[0].maps[0].texture,
        false
    );
    transform::Transform transform(
        entity, position, Vector3Scale(Vector3One(), constants::SCALE)
    );

    registry::registry.emplace<ship::Ship>(entity, ship);
    registry::registry.emplace<crosshair::Crosshair>(entity, crosshair);
    registry::registry.emplace<dynamic_body::DynamicBody>(entity, body);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);

    return entity;
}

entt::entity spawn_projectile(entt::entity owner, float speed, float damage) {
    static float thickness = 0.15f * constants::SCALE;
    static float length = speed * constants::DT;

    auto owner_ship = registry::registry.get<ship::Ship>(owner);
    auto owner_tr = registry::registry.get<transform::Transform>(owner);

    auto entity = registry::registry.create();

    Model model = resources::CYLINDER_MODEL;
    Material material = resources::PROJECTILE_MATERIAL;
    Vector3 position = Vector3Add(owner_tr.position, owner_ship.projectile_spawn_offset);
    Vector3 scale = {thickness, length, thickness};
    Quaternion rotation = QuaternionMultiply(
        owner_tr.rotation, QuaternionFromAxisAngle(constants::RIGHT, -0.5 * PI)
    );

    gmodel::GModel gmodel(entity, model, material, {}, false);
    projectile::Projectile projectile(entity, owner, speed, damage);
    transform::Transform transform(entity, position, scale, rotation);

    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<projectile::Projectile>(entity, projectile);
    registry::registry.emplace<transform::Transform>(entity, transform);

    return entity;
}

// TODO: celestial body prefabs look pretty similar. Maybe factor out...
entt::entity spawn_asteroid(Vector3 position) {
    auto entity = registry::registry.create();

    int idx = GetRandomValue(0, resources::ASTEROID_MODELS.size() - 1);
    Model model = resources::ASTEROID_MODELS[idx];
    Material material = resources::ASTEROID_MATERIAL;
    Texture texture = asteroid::generate_geosphere_texture(4094);

    asteroid::Asteroid asteroid(entity);
    gmodel::GModel gmodel(entity, model, material, texture, false);
    transform::Transform transform(
        entity, position, Vector3Scale(Vector3One(), constants::SCALE * 10.0)
    );
    collider::Collider collider(
        entity,
        constants::SCALE * 20.0  // sphere_radius
    );
    health::Health health(
        entity,
        1000.0  // max_val
    );

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
    transform::Transform transform(entity, position, scale);

    registry::registry.emplace<planet::Planet>(entity, planet);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);

    return entity;
}

entt::entity spawn_sun(Vector3 position, float radius) {
    auto entity = registry::registry.create();

    Vector3 scale = Vector3Scale(Vector3One(), radius);
    Model model = resources::SPHERE_MODEL;
    Material material = resources::SUN_MATERIAL;
    Texture texture = sun::generate_geosphere_texture(4094);

    sun::Sun sun(entity);
    gmodel::GModel gmodel(entity, model, material, texture, false);
    transform::Transform transform(entity, position, scale);
    light::PointLight point_light(
        entity,
        WHITE,
        {1.0, 0.0, 0.0},  // attenuation
        1.0  // intensity
    );

    registry::registry.emplace<sun::Sun>(entity, sun);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<light::PointLight>(entity, point_light);

    return entity;
}

entt::entity spawn_skybox() {
    auto entity = registry::registry.create();

    Vector3 position = camera::CAMERA.position;
    Model model = resources::SPHERE_MODEL;
    Material material = resources::SKYBOX_MATERIAL;
    Texture texture = skybox::generate_geosphere_texture(4094, 300.0, 0.83, 1.3, 0.3);

    skybox::Skybox skybox(entity);
    gmodel::GModel gmodel(entity, model, material, texture, true);
    transform::Transform transform(entity, position, Vector3Scale(Vector3One(), 1e4));
    light::AmbientLight ambient_light(
        entity,
        {255, 255, 255, 255},  // color
        0.1  // intensity
    );

    registry::registry.emplace<skybox::Skybox>(entity, skybox);
    registry::registry.emplace<gmodel::GModel>(entity, gmodel);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<light::AmbientLight>(entity, ambient_light);

    return entity;
}

}  // namespace gefest::prefabs
