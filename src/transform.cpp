#include "transform.hpp"

#include "raylib/raymath.h"

namespace gefest::transform {

Transform::Transform(Vector3 position)
    : position(position)
    , rotation(QuaternionIdentity()) {}

Transform::Transform(Vector3 position, Quaternion rotation)
    : position(position)
    , rotation(rotation) {}

}  // namespace gefest::transform
