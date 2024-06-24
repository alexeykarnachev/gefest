#pragma once

#include "raylib/raylib.h"

namespace gefest::camera {

enum class Mode {
    EDITOR,
    FOLLOW,
};

extern Camera3D CAMERA;

void set_mode(Mode);
Mode get_mode();
void update();

}  // namespace gefest::camera
