#include "drawing.hpp"

#include "camera.hpp"
#include "constants.hpp"
#include "light.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "resources.hpp"
#include <cstdio>

namespace gefest::drawing {

void draw_sphere(Texture texture, Matrix matrix, light::PointLight point_light) {
    Mesh mesh = resources::SPHERE_MESH;
    Material material = resources::get_sphere_material(texture, point_light);
    DrawMesh(mesh, material, matrix);
}

void draw_skybox(Texture texture) {
    static float radius = constants::SCALE * 1e4;

    Vector3 position = camera::CAMERA.position;
    Matrix t = MatrixTranslate(position.x, position.y, position.z);
    Matrix s = MatrixScale(radius, radius, radius);
    Matrix matrix = MatrixMultiply(s, t);

    Mesh mesh = resources::SPHERE_MESH;
    Material material = resources::get_skybox_material(texture);

    DrawMesh(mesh, material, matrix);
}

}  // namespace gefest::drawing
