#include "projectile.hpp"

#include "collider.hpp"
#include "constants.hpp"
#include "health.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"

namespace gefest::projectile {

static float THICKNESS = 0.15f * constants::SCALE;

Matrix get_matrix(transform::Transform tr, float length) {
    Matrix t = MatrixTranslate(tr.position.x, tr.position.y, tr.position.z);
    Matrix r = MatrixMultiply(
        MatrixRotateX(DEG2RAD * -90.0), QuaternionToMatrix(tr.rotation)
    );
    Matrix s = MatrixScale(THICKNESS, length, THICKNESS);

    Matrix mat = MatrixMultiply(s, MatrixMultiply(r, t));

    return mat;
}

Projectile::Projectile(entt::entity entity, entt::entity owner, float speed, float damage)
    : entity(entity)
    , owner(owner)
    , speed(speed)
    , damage(damage) {}

void Projectile::update() {
    if (this->ttl <= 0.0) {
        registry::registry.destroy(this->entity);
        return;
    }

    auto &tr = registry::registry.get<transform::Transform>(this->entity);

    Vector3 velocity = Vector3Scale(tr.get_forward(), this->speed);
    Vector3 step = Vector3Scale(velocity, constants::DT);
    float length = Vector3Length(step);
    Matrix mat = get_matrix(tr, length);

    Vector3 start = tr.position;
    Vector3 end = Vector3Add(start, step);

    auto view = registry::registry.view<collider::Collider>();
    for (auto target : view) {
        auto collider = registry::registry.get<collider::Collider>(target);

        bool is_hit = collider.check_line_collision(start, end);
        if (!is_hit) continue;

        registry::registry.destroy(this->entity);
        health::Health *health = registry::registry.try_get<health::Health>(target);
        if (health) health->receive_damage(this->damage);

        break;
    }

    this->ttl -= constants::DT;
    this->matrix = mat;
    tr.position = end;
}

void Projectile::draw() {
    Mesh mesh = resources::CYLINDER_MESH;
    Material material = resources::PROJECTILE_MATERIAL;

    DrawMesh(mesh, material, this->matrix);
}

}  // namespace gefest::projectile
