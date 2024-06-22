#include "game.hpp"

#include "camera.hpp"
#include "constants.hpp"
#include "editor.hpp"
#include "entt/entt.hpp"
#include "planet.hpp"
#include "raylib/raylib.h"

namespace gefest {
namespace game {

static bool WINDOW_SHOULD_CLOSE = false;

void load_window() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1500, 1000, "Gefest");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
}

void load() {
    load_window();
    editor::load();
    planet::load();
}

void unload() {
    planet::unload();
    editor::unload();
    CloseWindow();
}

void update_window_should_close() {
    bool is_alt_f4_pressed = IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_F4);
    WINDOW_SHOULD_CLOSE = (WindowShouldClose() || is_alt_f4_pressed);
}

void update() {
    camera::update();
    planet::update();
    update_window_should_close();
}

void draw() {
    BeginDrawing();
    ClearBackground(BLANK);

    BeginMode3D(camera::CAMERA);

    planet::draw();
    DrawGrid(20, 1.0);

    EndMode3D();

    editor::update_and_draw();

    DrawFPS(0, 0);
    EndDrawing();
}

void run() {
    load();

    float last_update_time = 0.0;
    while (!WINDOW_SHOULD_CLOSE) {
        float time = GetTime();

        while (time - last_update_time >= constants::DT) {
            update();
            last_update_time += constants::DT;
        }

        draw();
    }

    unload();
}

}  // namespace game
}  // namespace gefest
