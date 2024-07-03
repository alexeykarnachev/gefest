#include "utils.hpp"

#include "raylib/raylib.h"

namespace gefest::utils {
namespace shader {

void set_int(Shader shader, const char *name, int val) {
    SetShaderValue(shader, GetShaderLocation(shader, name), &val, SHADER_UNIFORM_INT);
}

void set_float(Shader shader, const char *name, float val) {
    SetShaderValue(shader, GetShaderLocation(shader, name), &val, SHADER_UNIFORM_FLOAT);
}

void set_vec3(Shader shader, const char *name, Vector3 val) {
    SetShaderValue(shader, GetShaderLocation(shader, name), &val, SHADER_UNIFORM_VEC3);
}

void set_color3(Shader shader, const char *name, Color val) {
    auto color = ColorNormalize(val);
    SetShaderValue(shader, GetShaderLocation(shader, name), &color, SHADER_UNIFORM_VEC3);
}

}  // namespace shader
}  // namespace gefest::utils
