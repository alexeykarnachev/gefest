#include "collider.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest::collider {

Collider::Collider(entt::entity entity, float sphere_radius)
    : entity(entity)
    , type(Type::SPHERE)
    , sphere(Sphere{.radius = sphere_radius}) {}

Collider::Collider(
    entt::entity entity, float box_width, float box_height, float box_length
)
    : entity(entity)
    , type(Type::BOX)
    , box(Box{
          .width = box_width,
          .height = box_height,
          .length = box_length,
      }) {}

bool check_sphere_line_collision(
    Vector3 start, Vector3 end, Vector3 center, float radius
) {
    Vector3 vec = Vector3Subtract(end, start);
    Vector3 dir = Vector3Normalize(vec);
    Ray ray = {.position = start, .direction = dir};

    RayCollision collision = GetRayCollisionSphere(ray, center, radius);
    if (!collision.hit) return false;

    float length = Vector3Length(vec);
    bool is_hit = collision.distance <= length;

    return is_hit;
}

bool check_box_line_collision(Vector3 start, Vector3 end) {
    return false;
}

bool Collider::check_line_collision(Vector3 start, Vector3 end) {
    auto tr = registry::registry.get<transform::Transform>(this->entity);

    bool is_hit = false;
    switch (this->type) {
        case Type::SPHERE: {
            Vector3 center = tr.position;
            float radius = this->sphere.radius;
            is_hit = check_sphere_line_collision(start, end, center, radius);
        } break;
        case Type::BOX: {
            is_hit = check_box_line_collision(start, end);
        } break;
    }

    return is_hit;
}

void Collider::draw_sphere() {
    static int n_rings = 16;
    static int n_slices = 16;

    auto tr = registry::registry.get<transform::Transform>(this->entity);

    DrawSphereWires(tr.position, this->sphere.radius, n_rings, n_slices, WHITE);
}

void Collider::draw_box() {
    auto tr = registry::registry.get<transform::Transform>(this->entity);

    DrawCubeWires(
        tr.position, this->box.width, this->box.height, this->box.length, WHITE
    );
}

void Collider::draw() {
    switch (this->type) {
        case Type::SPHERE: this->draw_sphere(); break;
        case Type::BOX: this->draw_box(); break;
    }
}

}  // namespace gefest::collider
