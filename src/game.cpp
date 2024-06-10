#include "game.hpp"

#include "camera.hpp"
#include "raylib/raylib.h"

namespace gefest {
namespace game {

static const float DT = 1.0 / 60.0;
static bool WINDOW_SHOULD_CLOSE = false;

void load() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1500, 1000, "Gefest");
    SetTargetFPS(60);
}

void unload() {
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

void draw() {
    BeginDrawing();
    ClearBackground(BLANK);

    BeginMode3D(camera::CAMERA);
    DrawGrid(100, 5.0);
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
