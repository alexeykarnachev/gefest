#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"
#include "transform.hpp"

namespace gefest::collider {

enum class Type {
    SPHERE,
    BOX,
};

struct Sphere {
    float radius;

    bool check_line_collision(transform::Transform tr, Vector3 start, Vector3 end);
    void draw(transform::Transform tr);
};

struct Box {
    float width;
    float height;
    float length;

    bool check_line_collision(transform::Transform tr, Vector3 start, Vector3 end);
    void draw(transform::Transform tr);
};

class Collider {
private:
    const entt::entity entity;

    const Type type;

    union {
        Sphere sphere;
        Box box;
    };

public:
    Collider(entt::entity entity, Sphere sphere);
    Collider(entt::entity entity, Box box);

    bool check_line_collision(Vector3 start, Vector3 end);

    void draw();
};

}  // namespace gefest::collider
