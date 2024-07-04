#pragma once

#include "raylib/raylib.h"

namespace gefest::camera {

enum class Mode {
    EDITOR,
    FOLLOW,
};

extern Camera3D CAMERA;
extern float FOLLOW_SMOOTHNESS;
extern float FOLLOW_SPEED_FOV_MULTIPLIER;

void set_mode(Mode);
Mode get_mode();

void translate(Vector3 vec);

void update();

}  // namespace gefest::camera
