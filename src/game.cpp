#include "game.hpp"

#include "camera.hpp"
#include "raylib/raylib.h"
#include "shaders.hpp"

namespace gefest {
namespace game {

static const float DT = 1.0 / 60.0;
static bool WINDOW_SHOULD_CLOSE = false;

void load() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1500, 1000, "Gefest");
    SetTargetFPS(60);

    shaders::load();
}

void unload() {
    shaders::unload();

    CloseWindow();
}

void update_window_should_close() {
    bool is_alt_f4_pressed = IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_F4);
    bool is_escape_pressed = IsKeyPressed(KEY_ESCAPE);
    WINDOW_SHOULD_CLOSE = (WindowShouldClose() || is_alt_f4_pressed)
                          && !is_escape_pressed;
}

void update() {
    camera::update();
    update_window_should_close();
}

void draw_planet() {
    static Vector3 position = {.x = 0.0, .y = 5.0, .z = 5.0};
    static float radius = 4.5;
    static int n_rings = 128;
    static int n_slices = 128;
    static Color color = DARKBLUE;

    DrawSphereEx(position, radius, n_rings, n_slices, color);
}

void draw() {
    BeginDrawing();
    ClearBackground(BLANK);

    BeginMode3D(camera::CAMERA);

    shaders::begin_planet_shader();
    draw_planet();
    EndShaderMode();

    DrawGrid(20, 1.0);
    EndMode3D();

    EndDrawing();
}

void run() {
    load();

    float last_update_time = 0.0;
    while (!WINDOW_SHOULD_CLOSE) {
        float time = GetTime();

        while (time - last_update_time >= DT) {
            update();
            last_update_time += DT;
        }

        draw();
    }

    unload();
}

}  // namespace game
}  // namespace gefest
