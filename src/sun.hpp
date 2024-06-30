#pragma once

#include "light.hpp"
#include "raylib/raylib.h"

namespace gefest::sun {

extern Vector3 POSITION;

light::PointLight get_point_light();

void generate();

void update();
void draw();

}  // namespace gefest::sun
