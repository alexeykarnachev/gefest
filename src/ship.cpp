#include "ship.hpp"

#include "dynamic_body.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"
#include <algorithm>

namespace gefest {
namespace ship {

Ship::Ship(entt::entity entity, ControllerType controller_type)
    : entity(entity)
    , controller_type(controller_type) {}

void Ship::reset_controls() {
    this->thrust = 0.0;
    this->roll = 0.0;
    this->pitch = 0.0;
}

void Ship::update_manual() {
    if (IsKeyDown(KEY_SPACE)) this->thrust += 1.0;
    if (IsKeyDown(KEY_A)) this->roll -= 1.0;
    if (IsKeyDown(KEY_D)) this->roll += 1.0;
    if (IsKeyDown(KEY_W)) this->pitch -= 1.0;
    if (IsKeyDown(KEY_S)) this->pitch += 1.0;
}

void Ship::update_dummy() {}

void Ship::apply_controls() {
    auto &body = registry::registry.get<dynamic_body::DynamicBody>(this->entity);

    float thrust = std::clamp(this->thrust, 0.0f, 1.0f);
    float engine_force = thrust * this->max_engine_force;

    // body.apply_force(this->control_force_dir, this->max_force);
}

void Ship::update_matrix() {
    this->matrix = MatrixIdentity();
}

void Ship::update() {
    this->reset_controls();

    switch (this->controller_type) {
        case ControllerType::MANUAL: update_manual();
        case ControllerType::DUMMY: update_dummy();
    }

    this->apply_controls();
    this->update_matrix();
}

void Ship::draw() {
    auto &tr = registry::registry.get<transform::Transform>(this->entity);

    Model model = resources::RED_FIGHTER_MODEL;

    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(this->matrix));
    DrawModel(model, tr.position, 1.0, WHITE);
    rlPopMatrix();
}

}  // namespace ship
}  // namespace gefest
