#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::collider {

class Collider {
private:
    const entt::entity entity;

    // collider type
    enum class Type {
        SPHERE,
        BOX,
    };
    const Type type;

    // collider data
    struct Sphere {
        float radius;
    };

    struct Box {
        float width;
        float height;
        float length;
    };

    union {
        Sphere sphere;
        Box box;
    };

    void draw_sphere();
    void draw_box();

public:
    Collider(entt::entity entity, float sphere_radius);
    Collider(entt::entity entity, float box_width, float box_height, float box_length);

    bool check_line_collision(Vector3 start, Vector3 end);

    void draw();
};

}  // namespace gefest::collider
