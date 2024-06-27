#include "projectile.hpp"

#include "constants.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"

namespace gefest::projectile {

static float THICKNESS = 0.015;

Projectile::Projectile(entt::entity entity, entt::entity owner, float speed)
    : entity(entity)
    , owner(owner)
    , speed(speed) {}

void Projectile::update() {
    if (this->ttl <= 0.0) {
        registry::registry.destroy(this->entity);
        return;
    }

    auto &tr = registry::registry.get<transform::Transform>(this->entity);

    Vector3 position = tr.position;
    Vector3 velocity = Vector3Scale(tr.get_forward(), this->speed);
    Vector3 step = Vector3Scale(velocity, constants::DT);
    float length = Vector3Length(step);

    Matrix t = MatrixTranslate(position.x, position.y, position.z);
    Matrix r = MatrixMultiply(
        MatrixRotateX(DEG2RAD * -90.0), QuaternionToMatrix(tr.rotation)
    );
    Matrix s = MatrixScale(THICKNESS, length, THICKNESS);
    Matrix mat = MatrixMultiply(s, MatrixMultiply(r, t));

    tr.position = Vector3Add(position, step);
    this->ttl -= constants::DT;
    this->matrix = mat;
}

void Projectile::draw() {
    Mesh mesh = resources::CYLINDER_MESH;
    Material material = resources::PROJECTILE_MATERIAL;

    DrawMesh(mesh, material, this->matrix);
}

}  // namespace gefest::projectile
