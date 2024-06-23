#pragma once

#include "raylib/raylib.h"

namespace gefest {
namespace camera {

enum class Mode {
    EDITOR,
    FOLLOW,
};

extern Camera3D CAMERA;

void set_mode(Mode);
Mode get_mode();
void update();

}  // namespace camera
}  // namespace gefest
