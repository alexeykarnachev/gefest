#pragma once

#include "light.hpp"
#include "raylib/raylib.h"
#include <vector>

namespace gefest::resources {

extern Mesh PLANE_MESH;
extern Mesh SPHERE_MESH;
extern Mesh CYLINDER_MESH;

extern Shader GEOSPHERE_TEXTURE_SHADER;
extern Shader SKYBOX_TEXTURE_SHADER;
extern Shader SUN_TEXTURE_SHADER;

extern Material MODEL_MATERIAL;
extern Material CROSSHAIR_MATERIAL;
extern Material PROJECTILE_MATERIAL;

extern Model RED_FIGHTER_MODEL;
extern std::vector<Model> ASTEROID_MODELS;

void load();
void unload();

Material get_skybox_material(Texture texture);
Material get_sphere_material(Texture texture);
Material get_sphere_material(Texture texture, light::PointLight point_light);
Model get_asteroid_model();

}  // namespace gefest::resources
