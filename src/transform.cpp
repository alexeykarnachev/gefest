#include "transform.hpp"

#include "constants.hpp"
#include "raylib/raymath.h"

namespace gefest::transform {

Transform::Transform(Vector3 position)
    : position(position)
    , rotation(QuaternionIdentity()) {}

Transform::Transform(Vector3 position, Quaternion rotation)
    : position(position)
    , rotation(rotation) {}

Vector3 Transform::get_forward() {
    return Vector3RotateByQuaternion(constants::FORWARD, this->rotation);
}

Vector3 Transform::get_up() {
    return Vector3RotateByQuaternion(constants::UP, this->rotation);
}

Vector3 Transform::apply_to_vector(Vector3 vec) {
    vec = Vector3RotateByQuaternion(vec, this->rotation);
    vec = Vector3Add(this->position, vec);
    return vec;
}

}  // namespace gefest::transform
