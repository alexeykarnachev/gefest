#include "camera.hpp"

#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rcamera.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest {
namespace camera {

Camera3D CAMERA = {
    .position = {0.0, 5.0, 30.0},
    .target = {0.0, 5.0, 0.0},
    .up = {0.0, 1.0, 0.0},
    .fovy = 60.0,
    .projection = CAMERA_PERSPECTIVE,
};
Vector3 POSITION_OFFSET = {0.0, -0.1, 3.8};
Vector3 TARGET_OFFSET = {0.0, 0.8, -1.6};
float FOLLOW_SMOOTHNESS = 0.0;

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

    // forward
    Vector3 forward = {0.0, 0.0, -1.0};
    forward = Vector3RotateByQuaternion(forward, tr.rotation);

    // rotation
    Quaternion rotation = QuaternionFromVector3ToVector3({0.0, 0.0, -1.0}, forward);

    // position offset
    Vector3 position_offset = Vector3RotateByQuaternion(
        Vector3Normalize(POSITION_OFFSET), rotation
    );
    position_offset = Vector3Scale(position_offset, Vector3Length(POSITION_OFFSET));

    // target offset
    Vector3 target_offset = Vector3RotateByQuaternion(
        Vector3Normalize(TARGET_OFFSET), rotation
    );
    target_offset = Vector3Scale(target_offset, Vector3Length(TARGET_OFFSET));

    // target
    Vector3 target = Vector3Add(tr.position, target_offset);
    target = Vector3Lerp(target, CAMERA.target, FOLLOW_SMOOTHNESS);

    // position
    Vector3 position = Vector3Add(target, position_offset);
    position = Vector3Lerp(position, CAMERA.position, FOLLOW_SMOOTHNESS);

    // set camera values
    CAMERA.position = position;
    CAMERA.target = target;

    // update up vector
    Vector3 right = GetCameraRight(&CAMERA);
    Vector3 target_to_camera = Vector3Subtract(CAMERA.position, CAMERA.target);
    Vector3 up = Vector3Normalize(Vector3CrossProduct(target_to_camera, right));

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
