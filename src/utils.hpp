#pragma once

#include "raylib/raylib.h"

namespace gefest::utils {
namespace shader {

void set_int(Shader shader, const char *name, int val);
void set_float(Shader shader, const char *name, float val);
void set_vec3(Shader shader, const char *name, Vector3 val);
void set_color3(Shader shader, const char *name, Color val);

}  // namespace shader
}  // namespace gefest::utils
