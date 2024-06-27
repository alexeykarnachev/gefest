#pragma once

#include "raylib/raylib.h"

namespace gefest::sun {

extern Vector3 POSITION;

void set_shader_point_light(Shader shader);

void update();
void draw();

}  // namespace gefest::sun
