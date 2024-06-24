#pragma once

#include "raylib/raylib.h"

namespace gefest::resources {

extern Mesh SPHERE_MESH;

extern Material GEOSPHERE_MATERIAL;
extern Material SKYBOX_MATERIAL;

extern Model RED_FIGHTER_MODEL;

void load();
void unload();

}  // namespace gefest::resources
