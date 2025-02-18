#include "ship.hpp"

#include "constants.hpp"
#include "dynamic_body.hpp"
#include "prefabs.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "transform.hpp"
#include <algorithm>
#include <cstdio>

namespace gefest::ship {

Ship::Ship(
    entt::entity entity,
    ControllerType controller_type,
    float engine_force,
    float pitch_magnitude,
    float roll_magnitude,
    float shoot_rate,
    float projectile_speed,
    float projectile_damage,
    Vector3 projectile_spawn_offset
)
    : entity(entity)
    , controller_type(controller_type)
    , engine_force(engine_force)
    , pitch_magnitude(pitch_magnitude)
    , roll_magnitude(roll_magnitude)
    , shoot_rate(shoot_rate)
    , projectile_speed(projectile_speed)
    , projectile_damage(projectile_damage)
    , projectile_spawn_offset(projectile_spawn_offset) {}

void Ship::reset_controls() {
    this->thrust = 0.0;
    this->roll = 0.0;
    this->pitch = 0.0;
}

void Ship::update_manual_controller() {
    if (IsKeyDown(KEY_SPACE)) this->thrust += 1.0;
    if (IsKeyDown(KEY_D)) this->roll -= 1.0;
    if (IsKeyDown(KEY_A)) this->roll += 1.0;
    if (IsKeyDown(KEY_W)) this->pitch -= 1.0;
    if (IsKeyDown(KEY_S)) this->pitch += 1.0;

    if (IsKeyDown(KEY_ENTER)) shoot();
}

void Ship::update_dummy_controller() {}

void Ship::apply_controls() {
    auto &body = registry::registry.get<dynamic_body::DynamicBody>(this->entity);
    auto &tr = registry::registry.get<transform::Transform>(this->entity);

    Vector3 forward = Vector3RotateByQuaternion(constants::FORWARD, tr.rotation);

    float thrust = std::clamp(this->thrust, -1.0f, 1.0f);
    float engine_force = thrust * this->engine_force;
    body.apply_force(forward, engine_force);

    float pitch = std::clamp(this->pitch, -1.0f, 1.0f);
    float pitch_magnitude = pitch * this->pitch_magnitude;
    body.apply_torque({pitch_magnitude, 0.0, 0.0});

    float roll = std::clamp(this->roll, -1.0f, 1.0f);
    float roll_magnitude = roll * this->roll_magnitude;
    body.apply_torque({0.0, 0.0, roll_magnitude});
}

void Ship::shoot() {
    float time = GetTime();
    float shoot_period = 1.0 / this->shoot_rate;
    float allowed_shoot_time = this->last_shot_time + shoot_period;
    bool can_shoot = allowed_shoot_time <= time;

    if (!can_shoot) return;

    auto body = registry::registry.get<dynamic_body::DynamicBody>(this->entity);
    float speed = this->projectile_speed + body.get_linear_speed();

    prefabs::spawn_projectile(this->entity, speed, this->projectile_damage);
    this->last_shot_time = time;
}

void Ship::update() {
    this->reset_controls();

    switch (this->controller_type) {
        case ControllerType::MANUAL: update_manual_controller(); break;
        case ControllerType::DUMMY: update_dummy_controller(); break;
    }

    this->apply_controls();
}

}  // namespace gefest::ship
