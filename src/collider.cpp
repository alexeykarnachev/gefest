#include "collider.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest::collider {

// -----------------------------------------------------------------------
// collider
Collider::Collider(entt::entity entity, Sphere sphere)
    : entity(entity)
    , type(Type::SPHERE)
    , sphere(sphere) {}

Collider::Collider(entt::entity entity, Box box)
    : entity(entity)
    , type(Type::BOX)
    , box(box) {}

bool Collider::check_line_collision(Vector3 start, Vector3 end) {
    auto tr = registry::registry.get<transform::Transform>(this->entity);

    switch (this->type) {
        case Type::SPHERE: return this->sphere.check_line_collision(tr, start, end);
        case Type::BOX: return this->box.check_line_collision(tr, start, end);
    }

    return false;
}

void Collider::draw() {
    auto tr = registry::registry.get<transform::Transform>(this->entity);

    switch (this->type) {
        case Type::SPHERE: return this->sphere.draw(tr);
        case Type::BOX: return this->box.draw(tr);
    }
}

// -----------------------------------------------------------------------
// sphere
void Sphere::draw(transform::Transform tr) {
    static int n_rings = 16;
    static int n_slices = 16;

    DrawSphereWires(tr.position, this->radius, n_rings, n_slices, WHITE);
}

bool Sphere::check_line_collision(transform::Transform tr, Vector3 start, Vector3 end) {
    Vector3 vec = Vector3Subtract(end, start);
    Vector3 dir = Vector3Normalize(vec);
    Ray ray = {.position = start, .direction = dir};

    RayCollision collision = GetRayCollisionSphere(ray, tr.position, radius);
    if (!collision.hit) return false;

    float length = Vector3Length(vec);
    bool is_hit = collision.distance <= length;

    return is_hit;
}

// -----------------------------------------------------------------------
// sphere
void Box::draw(transform::Transform tr) {
    // TODO: not implemented yet
}

bool Box::check_line_collision(transform::Transform tr, Vector3 start, Vector3 end) {
    // TODO: not implemented yet
    return false;
}

}  // namespace gefest::collider
