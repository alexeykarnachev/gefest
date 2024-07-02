#include "crosshair.hpp"

#include "constants.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"

namespace gefest::crosshair {

Crosshair::Crosshair(
    entt::entity entity,
    Vector3 start_offset,
    float length,
    float thickness,
    float attenuation,
    float start_alpha
)
    : entity(entity)
    , start_offset(start_offset)
    , length(length)
    , thickness(thickness)
    , attenuation(attenuation)
    , start_alpha(start_alpha) {}

void Crosshair::update() {
    auto tr = registry::registry.get<transform::Transform>(this->entity);

    Vector3 start_offset = Vector3RotateByQuaternion(this->start_offset, tr.rotation);
    Vector3 start_position = Vector3Add(tr.position, start_offset);

    Matrix t = MatrixTranslate(start_position.x, start_position.y, start_position.z);
    Matrix r = MatrixMultiply(
        MatrixRotateX(DEG2RAD * -90.0), QuaternionToMatrix(tr.rotation)
    );
    Matrix s = MatrixScale(this->thickness, this->length, this->thickness);
    Matrix matrix = MatrixMultiply(s, MatrixMultiply(r, t));

    this->start_position = start_position;
    this->matrix = matrix;
}

void Crosshair::draw() {
    Mesh mesh = resources::CYLINDER_MODEL.meshes[0];
    Material material = resources::CROSSHAIR_MATERIAL;
    Shader shader = material.shader;

    int length_loc = GetShaderLocation(shader, "length");
    int attenuation_loc = GetShaderLocation(shader, "attenuation");
    int start_alpha_loc = GetShaderLocation(shader, "start_alpha");
    int start_position_loc = GetShaderLocation(shader, "start_position");

    SetShaderValue(shader, length_loc, &this->length, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, attenuation_loc, &this->attenuation, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, start_alpha_loc, &this->start_alpha, SHADER_UNIFORM_FLOAT);
    SetShaderValue(
        shader, start_position_loc, &this->start_position, SHADER_UNIFORM_VEC3
    );

    DrawMesh(mesh, material, this->matrix);
}

}  // namespace gefest::crosshair
