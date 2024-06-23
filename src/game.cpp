#include "game.hpp"

#include "camera.hpp"
#include "constants.hpp"
#include "dynamic_body.hpp"
#include "editor.hpp"
#include "entt/entt.hpp"
#include "planet.hpp"
#include "raylib/raylib.h"
#include "registry.hpp"
#include "resources.hpp"
#include "ship.hpp"
#include "transform.hpp"

namespace gefest {
namespace game {

static bool WINDOW_SHOULD_CLOSE = false;

entt::entity create_ship(Vector3 position, ship::ControllerType controller_type) {
    auto entity = registry::registry.create();

    ship::Ship ship(entity, controller_type);
    transform::Transform transform(position);
    dynamic_body::DynamicBody body(entity, 500.0, 500.0, 10.0, 10.0);

    registry::registry.emplace<ship::Ship>(entity, ship);
    registry::registry.emplace<transform::Transform>(entity, transform);
    registry::registry.emplace<dynamic_body::DynamicBody>(entity, body);

    return entity;
}

entt::entity create_player_ship(Vector3 position) {
    auto entity = create_ship(position, ship::ControllerType::MANUAL);
    registry::registry.emplace<registry::Player>(entity);
    return entity;
}

void load_window() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1500, 1000, "Gefest");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
}

void load() {
    load_window();
    resources::load();
    editor::load();

    create_player_ship({0.0, 4.0, 25.0});
    camera::set_mode(camera::Mode::FOLLOW_PLAYER);
}

void unload() {
    editor::unload();
    resources::unload();
    CloseWindow();
}

void update_window_should_close() {
    bool is_alt_f4_pressed = IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_F4);
    WINDOW_SHOULD_CLOSE = (WindowShouldClose() || is_alt_f4_pressed);
}

void update_ships() {
    auto view = registry::registry.view<ship::Ship>();
    for (auto entity : view) {
        auto &ship = registry::registry.get<ship::Ship>(entity);
        ship.update();
    }
}

void update_dynamic_bodies() {
    auto view = registry::registry.view<dynamic_body::DynamicBody>();
    for (auto entity : view) {
        auto &body = registry::registry.get<dynamic_body::DynamicBody>(entity);
        body.update();
    }
}

void update() {
    update_window_should_close();
    camera::update();
    planet::update();
    update_ships();
    update_dynamic_bodies();
}

void draw_ships() {
    auto view = registry::registry.view<ship::Ship>();
    for (auto entity : view) {
        auto &ship = registry::registry.get<ship::Ship>(entity);
        ship.draw();
    }
}

void draw() {
    BeginDrawing();
    ClearBackground(BLANK);

    BeginMode3D(camera::CAMERA);

    planet::draw();
    draw_ships();
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
