#include "camera.hpp"

#include "constants.hpp"
#include "dynamic_body.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rcamera.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest::camera {

float FOLLOW_SMOOTHNESS = 0.4;
float FOLLOW_SPEED_FOV_MULTIPLIER = 0.01f / constants::SCALE;

static float FOV = 60.0;

Camera3D CAMERA = {
    .position = {0.0, 0.0, 0.0},
    .target = {0.0, 0.0, -1.0},
    .up = {0.0, 1.0, 0.0},
    .fovy = FOV,
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
    static float camera_rot_speed = 0.003;
    static float camera_move_speed = 0.1 * constants::SCALE;
    static float camera_zoom_speed = 10.0 * constants::SCALE;

    CAMERA.up = constants::UP;

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
    auto body = registry::registry.get<dynamic_body::DynamicBody>(entity);
    float speed = body.get_linear_speed();

    // TODO: refactor using Transform::apply
    Vector3 forward = tr.get_forward();
    Vector3 target_up = tr.get_up();
    Vector3 up = Vector3Lerp(target_up, CAMERA.up, FOLLOW_SMOOTHNESS);

    Vector3 forward_offset = Vector3Scale(forward, -15.0 * constants::SCALE);
    Vector3 up_offset = Vector3Scale(up, 8.0 * constants::SCALE);
    Vector3 offset = Vector3Add(forward_offset, up_offset);

    Vector3 position = Vector3Add(tr.position, offset);
    Vector3 target = Vector3Add(tr.position, Vector3Scale(up, 5.0 * constants::SCALE));

    position = Vector3Lerp(position, CAMERA.position, FOLLOW_SMOOTHNESS);
    target = Vector3Lerp(target, CAMERA.target, FOLLOW_SMOOTHNESS);

    float fov = FOV + speed * FOLLOW_SPEED_FOV_MULTIPLIER;

    CAMERA.position = position;
    CAMERA.target = target;
    CAMERA.up = up;
    CAMERA.fovy = fov;
}

void update() {
    switch (MODE) {
        case Mode::EDITOR: update_editor_mode(); break;
        case Mode::FOLLOW: update_follow_mode(); break;
    }
}

}  // namespace gefest::camera
