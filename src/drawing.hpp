#pragma once

#include "light.hpp"
#include "raylib/raylib.h"

namespace gefest::drawing {

void draw_textured_sphere(Texture texture, light::PointLight point_light, Matrix matrix);

}  // namespace gefest::drawing
