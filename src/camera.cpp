#include "camera.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rcamera.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest {
namespace camera {

static Vector3 UP = {0.0, 1.0, 0.0};
static Vector3 FORWARD = {0.0, 0.0, -1.0};

Camera3D CAMERA = {
    .position = {0.0, 5.0, 30.0},
    .target = {0.0, 5.0, 0.0},
    .up = {0.0, 1.0, 0.0},
    .fovy = 60.0,
    .projection = CAMERA_PERSPECTIVE,
};

Mode MODE = Mode::FOLLOW;

void set_mode(Mode mode) {
    MODE = mode;
}

Mode get_mode() {
    return MODE;
}

void update_editor_mode() {
    static constexpr float camera_rot_speed = 0.003;
    static constexpr float camera_move_speed = 0.01;
    static constexpr float camera_zoom_speed = 1.0;

    CAMERA.up = {0.0, 1.0, 0.0};

    bool is_mmb_down = IsMouseButtonDown(2);
    bool is_shift_down = IsKeyDown(KEY_LEFT_SHIFT);
    Vector2 mouse_delta = GetMouseDelta();

    bool is_moving = is_mmb_down && is_shift_down;
    bool is_rotating = is_mmb_down && !is_shift_down;

    // move
    if (is_moving) {
        CameraMoveRight(&CAMERA, -camera_move_speed * mouse_delta.x, true);

        Vector3 up_norm = Vector3Normalize(CAMERA.up);
        Vector3 up = Vector3Scale(up_norm, camera_move_speed * mouse_delta.y);

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

void update_follow_mode() {
    auto entity = registry::registry.view<registry::Player>().front();
    auto tr = registry::registry.get<transform::Transform>(entity);

    Vector3 forward = Vector3RotateByQuaternion(FORWARD, tr.rotation);
    Vector3 up = Vector3RotateByQuaternion(UP, tr.rotation);

    Vector3 forward_offset = Vector3Scale(forward, -20.0);
    Vector3 up_offset = Vector3Scale(up, 10.0);
    Vector3 offset = Vector3Add(forward_offset, up_offset);

    CAMERA.position = Vector3Add(tr.position, offset);
    CAMERA.target = Vector3Add(tr.position, Vector3Scale(up, 5.0));
    CAMERA.up = up;
}

void update() {
    switch (MODE) {
        case Mode::EDITOR: update_editor_mode(); break;
        case Mode::FOLLOW: update_follow_mode(); break;
    }
}

}  // namespace camera
}  // namespace gefest
