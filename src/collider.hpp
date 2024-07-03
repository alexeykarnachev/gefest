#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::collider {

enum class Type {
    SPHERE,
    BOX,
};

struct Sphere {
    float radius;
};

struct Box {
    float width;
    float height;
    float length;
};

class Collider {
private:
    const entt::entity entity;

    const Type type;

    union {
        Sphere sphere;
        Box box;
    };

    void draw_sphere();
    void draw_box();

public:
    Collider(entt::entity entity, Sphere sphere);
    Collider(entt::entity entity, Box box);

    bool check_line_collision(Vector3 start, Vector3 end);

    void draw();
};

}  // namespace gefest::collider
