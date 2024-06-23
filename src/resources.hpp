#pragma once

#include "raylib/raylib.h"

namespace gefest {
namespace resources {

extern Mesh SPHERE_MESH;

extern Material GEOSPHERE_MATERIAL;

extern Model RED_FIGHTER_MODEL;

void load();
void unload();

}  // namespace resources
}  // namespace st
