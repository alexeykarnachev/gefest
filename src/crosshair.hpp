#pragma once

#include "raylib/raylib.h"

namespace gefest::crosshair {

extern float LENGTH;
extern float THICKNESS;
extern float ATTENUATION;
extern float START_ALPHA;
extern Vector3 START_OFFSET;

void update();

void draw();

}  // namespace gefest::crosshair
