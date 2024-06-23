#pragma once

#include "raylib/raylib.h"

namespace gefest {
namespace camera {

enum class Mode {
    EDITOR,
    FOLLOW_PLAYER,
};

extern Camera3D CAMERA;
extern Mode MODE;

void update();

}  // namespace camera
}  // namespace gefest
