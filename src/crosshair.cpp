#include "crosshair.hpp"

#include "constants.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"

namespace gefest::crosshair {

float LENGTH = constants::SCALE * 1e3;
float THICKNESS = constants::SCALE * 0.05f;
float ATTENUATION = 15.0;
float START_ALPHA = 0.95;
Vector3 START_OFFSET = {constants::SCALE * 1.15f, 0.0, -constants::SCALE * 0.08f};

static Vector3 START_POSITION;
static Matrix MATRIX;

void update() {
    auto entity = registry::registry.view<registry::Player>().front();
    auto tr = registry::registry.get<transform::Transform>(entity);

    Vector3 start_offset = Vector3RotateByQuaternion(START_OFFSET, tr.rotation);
    Vector3 start_position = Vector3Add(tr.position, start_offset);

    Matrix t = MatrixTranslate(start_position.x, start_position.y, start_position.z);
    Matrix r = MatrixMultiply(
        MatrixRotateX(DEG2RAD * -90.0), QuaternionToMatrix(tr.rotation)
    );
    Matrix s = MatrixScale(THICKNESS, LENGTH, THICKNESS);
    Matrix mat = MatrixMultiply(s, MatrixMultiply(r, t));

    START_POSITION = start_position;
    MATRIX = mat;
}

void draw() {
    Mesh mesh = resources::CYLINDER_MESH;
    Material material = resources::CROSSHAIR_MATERIAL;
    Shader shader = material.shader;

    int length_loc = GetShaderLocation(shader, "length");
    int attenuation_loc = GetShaderLocation(shader, "attenuation");
    int start_alpha_loc = GetShaderLocation(shader, "start_alpha");
    int start_position_loc = GetShaderLocation(shader, "start_position");

    SetShaderValue(shader, length_loc, &LENGTH, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, attenuation_loc, &ATTENUATION, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, start_alpha_loc, &START_ALPHA, SHADER_UNIFORM_FLOAT);
    SetShaderValue(shader, start_position_loc, &START_POSITION, SHADER_UNIFORM_VEC3);

    DrawMesh(mesh, material, MATRIX);
}

}  // namespace gefest::crosshair
