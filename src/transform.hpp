#pragma once

#include "raylib/raylib.h"
#include "raylib/raymath.h"

namespace gefest::transform {

class Transform {
public:
    Vector3 position = Vector3Zero();
    Vector3 scale = Vector3One();
    Quaternion rotation = QuaternionIdentity();

    Transform(Vector3 position);
    Transform(Vector3 position, Vector3 Scale);
    Transform(Vector3 position, Vector3 Scale, Quaternion rotation);

    Matrix get_matrix();

    Vector3 get_up();
    Vector3 get_forward();

    Vector3 apply_to_vector(Vector3 vec);
};

}  // namespace gefest::transform
