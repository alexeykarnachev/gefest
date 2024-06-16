#pragma once

#include "raylib/raylib.h"
#include <string>

namespace gefest {
namespace shaders {

Shader load_shader(const std::string &vs_file_name, const std::string &fs_file_name);

}
}  // namespace gefest
