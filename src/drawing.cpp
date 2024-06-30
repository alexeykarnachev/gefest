#include "drawing.hpp"

#include "light.hpp"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "resources.hpp"
#include <cstdio>

namespace gefest::drawing {

void draw_textured_sphere(Texture texture, light::PointLight point_light, Matrix matrix) {
    Mesh mesh = resources::SPHERE_MESH;
    Material material = resources::get_sphere_material(texture, point_light);
    DrawMesh(mesh, material, matrix);
}

}  // namespace gefest::drawing
