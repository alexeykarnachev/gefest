#pragma once

#include "raylib/raylib.h"

namespace gefest {
namespace camera {

enum class Mode {
    EDITOR,
    FOLLOW,
};

extern Camera3D CAMERA;
extern Vector3 POSITION_OFFSET;
extern Vector3 TARGET_OFFSET;
extern float FOLLOW_SMOOTHNESS;

void set_mode(Mode);
Mode get_mode();
void update();

}  // namespace camera
}  // namespace gefest
