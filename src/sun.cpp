#include "sun.hpp"

#include "constants.hpp"
#include "light.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "resources.hpp"

namespace gefest::sun {

Vector3 POSITION = {
    constants::SCALE * 6e5f, constants::SCALE * 7e5f, -constants::SCALE * 6e5f
};
static float RADIUS = constants::SCALE * 5e4;

static Color COLOR = {255, 240, 255, 255};
static Vector3 ATTENUATION = {1.0, 0.0, 0.0};
static float INTENSITY = 1.0;

static Matrix MATRIX;

light::PointLight get_point_light() {
    light::PointLight point_light(COLOR, POSITION, ATTENUATION, INTENSITY);
    return point_light;
}

void update() {
    Matrix t = MatrixTranslate(POSITION.x, POSITION.y, POSITION.z);
    Matrix s = MatrixScale(RADIUS, RADIUS, RADIUS);

    MATRIX = MatrixMultiply(s, t);
}

void draw_geosphere() {
    Mesh mesh = resources::SPHERE_MESH;
    Material material = resources::SUN_MATERIAL;

    // draw sphere
    DrawMesh(mesh, material, MATRIX);
}

void draw() {
    draw_geosphere();
}

}  // namespace gefest::sun
