#include "transform.hpp"

#include "constants.hpp"
#include "raylib/raymath.h"

namespace gefest::transform {

Transform::Transform(Vector3 position)
    : position(position)
    , rotation(QuaternionIdentity()) {}

Transform::Transform(Vector3 position, Vector3 scale)
    : position(position)
    , scale(scale) {}

Transform::Transform(Vector3 position, Vector3 scale, Quaternion rotation)
    : position(position)
    , scale(scale)
    , rotation(rotation) {}

Vector3 Transform::get_forward() {
    return Vector3RotateByQuaternion(constants::FORWARD, this->rotation);
}

Matrix Transform::get_matrix() {
    Matrix r = QuaternionToMatrix(this->rotation);
    Matrix t = MatrixTranslate(this->position.x, this->position.y, this->position.z);
    Matrix s = MatrixScale(this->scale.x, this->scale.y, this->scale.z);

    Matrix mat = MatrixMultiply(s, MatrixMultiply(r, t));

    return mat;
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
