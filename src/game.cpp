#include "game.hpp"

#include "asteroid.hpp"
#include "camera.hpp"
#include "constants.hpp"
#include "crosshair.hpp"
#include "dynamic_body.hpp"
#include "editor.hpp"
#include "entt/entt.hpp"
#include "gmodel.hpp"
#include "health.hpp"
#include "planet.hpp"
#include "prefabs.hpp"
#include "projectile.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "resources.hpp"
#include "ship.hpp"
#include "skybox.hpp"
#include "sun.hpp"

namespace gefest::game {

static bool WINDOW_SHOULD_CLOSE = false;

void load_window() {
    int screen_width = 2560;
    int screen_height = 1440;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screen_width, screen_height, "Gefest");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
    rlSetClipPlanes(constants::SCALE * 0.1f, constants::SCALE * 1e6);
}

void load() {
    load_window();
    resources::load();
    editor::load();

    // player ship
    Vector3 position = {0.0, constants::SCALE * 3e4f, constants::SCALE * 3e4f};
    auto entity = prefabs::spawn_red_fighter(position, ship::ControllerType::MANUAL);
    registry::registry.emplace<registry::Player>(entity);

    // asteroid
    prefabs::spawn_asteroid(Vector3Add(position, {0.0, 0.0, -constants::SCALE * 1e3f}));

    // planet
    prefabs::spawn_planet(Vector3Zero(), constants::SCALE * 3e4);

    // sun
    prefabs::spawn_sun(
        {constants::SCALE * 6e5f, constants::SCALE * 7e5f, -constants::SCALE * 6e5f},
        constants::SCALE * 5e4
    );

    // skybox
    prefabs::spawn_skybox();
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

template <typename T> void update_components() {
    auto view = registry::registry.view<T>();
    for (auto entity : view) {
        auto &projectile = registry::registry.get<T>(entity);
        projectile.update();
    }
}

template <typename T> void draw_components() {
    auto view = registry::registry.view<T>();
    for (auto entity : view) {
        auto &projectile = registry::registry.get<T>(entity);
        projectile.draw();
    }
}

void update() {
    update_window_should_close();

    update_components<sun::Sun>();
    update_components<planet::Planet>();
    update_components<dynamic_body::DynamicBody>();
    update_components<ship::Ship>();
    camera::update();
    crosshair::update();
    update_components<projectile::Projectile>();
    update_components<asteroid::Asteroid>();
    update_components<health::Health>();
}

void draw() {
    BeginDrawing();
    ClearBackground(BLANK);

    BeginMode3D(camera::CAMERA);

    draw_components<gmodel::GModel>();
    crosshair::draw();
    draw_components<projectile::Projectile>();

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

}  // namespace gefest::game
