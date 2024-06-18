#include "camera.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rcamera.h"

namespace gefest {
namespace camera {

Camera3D CAMERA = {
    .position = {0.0, 5.0, 30.0},
    .target = {0.0, 5.0, 0.0},
    .up = {0.0, 1.0, 0.0},
    .fovy = 60.0,
    .projection = CAMERA_PERSPECTIVE,
};

void update() {
    static const float camera_rot_speed = 0.003;
    static const float camera_move_speed = 0.01;
    static const float camera_zoom_speed = 1.0;

    bool is_mmb_down = IsMouseButtonDown(2);
    bool is_shift_down = IsKeyDown(KEY_LEFT_SHIFT);
    Vector2 mouse_delta = GetMouseDelta();

    bool is_moving = is_mmb_down && is_shift_down;
    bool is_rotating = is_mmb_down && !is_shift_down;

    // move
    if (is_moving) {
        CameraMoveRight(&CAMERA, -camera_move_speed * mouse_delta.x, true);

        Vector3 right = GetCameraRight(&CAMERA);
        Vector3 target_to_camera = Vector3Subtract(CAMERA.position, CAMERA.target);
        Vector3 up = Vector3CrossProduct(target_to_camera, right);
        Vector3 up_norm = Vector3Normalize(up);
        up = Vector3Scale(up_norm, camera_move_speed * mouse_delta.y);

        CAMERA.position = Vector3Add(CAMERA.position, up);
        CAMERA.target = Vector3Add(CAMERA.target, up);
    }

    // rotate
    if (is_rotating) {
        CameraYaw(&CAMERA, -camera_rot_speed * mouse_delta.x, true);
        CameraPitch(&CAMERA, camera_rot_speed * mouse_delta.y, true, true, false);
    }

    // zoom
    CameraMoveToTarget(&CAMERA, -GetMouseWheelMove() * camera_zoom_speed);
}

}  // namespace camera
}  // namespace gefest
