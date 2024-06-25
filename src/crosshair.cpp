#include "crosshair.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"

namespace gefest::crosshair {

float THICKNESS = 0.2;

static Vector3 OFFSET = {0.0, 0.0, -1.0};
static float SIZE = 0.2;

static Matrix MATRIX;

void update() {
    auto entity = registry::registry.view<registry::Player>().front();
    auto tr = registry::registry.get<transform::Transform>(entity);

    Vector3 offset = Vector3RotateByQuaternion(OFFSET, tr.rotation);
    Vector3 position = Vector3Add(tr.position, offset);

    Matrix t = MatrixTranslate(position.x, position.y, position.z);
    Matrix r = QuaternionToMatrix(tr.rotation);
    Matrix s = MatrixScale(SIZE, SIZE, SIZE);
    Matrix mat = MatrixMultiply(s, MatrixMultiply(r, t));

    r = MatrixRotateX(DEG2RAD * 90.0);
    mat = MatrixMultiply(r, mat);

    MATRIX = mat;
}

void draw() {
    Mesh mesh = resources::PLANE_MESH;
    Material material = resources::CROSSHAIR_MATERIAL;
    Shader shader = material.shader;

    int thickness_loc = GetShaderLocation(shader, "thickness");

    SetShaderValue(shader, thickness_loc, &THICKNESS, SHADER_UNIFORM_FLOAT);

    DrawMesh(mesh, material, MATRIX);
}

}  // namespace gefest::crosshair
