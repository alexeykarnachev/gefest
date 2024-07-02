#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::crosshair {

class Crosshair {
private:
    entt::entity entity;

    Vector3 start_position;
    Matrix matrix;

public:
    Vector3 start_offset;

    float length;
    float thickness;
    float attenuation;
    float start_alpha;

    Crosshair(
        entt::entity entity,
        Vector3 start_offset,
        float length,
        float thickness,
        float attenuation,
        float start_alpha
    );

    void update();
    void draw();
};

}  // namespace gefest::crosshair
