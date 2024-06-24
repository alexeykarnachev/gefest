#pragma once

#include "raylib/raylib.h"
#include "raylib/raymath.h"

namespace gefest::transform {

class Transform {
public:
    Vector3 position = Vector3Zero();
    Quaternion rotation = QuaternionIdentity();

    Transform(Vector3 position);
    Transform(Vector3 position, Quaternion rotation);
};

}  // namespace gefest::transform
