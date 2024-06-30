#pragma once

#include "light.hpp"
#include "raylib/raylib.h"

namespace gefest::drawing {

void draw_texture(RenderTexture render_texture, Shader shader);
void draw_sphere(Texture texture, Matrix matrix);
void draw_sphere(Texture texture, Matrix matrix, light::PointLight point_light);
void draw_skybox(Texture texture);

}  // namespace gefest::drawing
