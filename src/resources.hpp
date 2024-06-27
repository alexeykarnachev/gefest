#pragma once

#include "raylib/raylib.h"

namespace gefest::resources {

extern Mesh PLANE_MESH;
extern Mesh SPHERE_MESH;
extern Mesh CYLINDER_MESH;

extern Material SUN_MATERIAL;
extern Material GEOSPHERE_MATERIAL;
extern Material SKYBOX_MATERIAL;
extern Material CROSSHAIR_MATERIAL;
extern Material PROJECTILE_MATERIAL;
extern Material ASTEROID_MATERIAL;

extern Model RED_FIGHTER_MODEL;

void load();
void unload();

Mesh get_asteroid_mesh();

}  // namespace gefest::resources
