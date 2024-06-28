#include "game.hpp"

#include "asteroid.hpp"
#include "camera.hpp"
#include "collider.hpp"
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
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1500, 1000, "Gefest");
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
    position = Vector3Add(
        position, {0.0, constants::SCALE * 100.0f, -constants::SCALE * 1e3f}
    );
    entity = prefabs::spawn_asteroid(position);
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

    sun::update();
    planet::update();
    skybox::update();
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

    rlDisableDepthTest();
    rlDisableBackfaceCulling();
    skybox::draw();
    rlEnableDepthTest();
    rlEnableBackfaceCulling();

    sun::draw();
    planet::draw();
    draw_components<gmodel::GModel>();
    draw_components<gmodel::GMesh>();
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
