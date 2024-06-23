#pragma once

#include "raylib/raylib.h"

namespace gefest {
namespace camera {

enum class Mode {
    EDITOR,
    FOLLOW_PLAYER,
};

extern Camera3D CAMERA;

void set_mode(Mode);
void update();

}  // namespace camera
}  // namespace gefest
