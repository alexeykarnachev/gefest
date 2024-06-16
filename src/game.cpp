#include "game.hpp"

#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "planet.hpp"
#include "raylib/raylib.h"

namespace gefest {
namespace game {

static const float DT = 1.0 / 60.0;
static bool WINDOW_SHOULD_CLOSE = false;

void load_window() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(1500, 1000, "Gefest");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);
}

void load_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    GLFWwindow *window = (GLFWwindow *)GetWindowHandle();
    glfwGetWindowUserPointer(window);
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 420 core");
    ImGui::StyleColorsDark();
}

void unload_imgui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void load() {
    load_window();
    load_imgui();
    planet::load();
}

void unload() {
    planet::unload();
    unload_imgui();
    CloseWindow();
}

void update_window_should_close() {
    bool is_alt_f4_pressed = IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_F4);
    WINDOW_SHOULD_CLOSE = (WindowShouldClose() || is_alt_f4_pressed);
}

void update() {
    camera::update();
    update_window_should_close();
}

void begin_imgui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void end_imgui() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void draw() {
    BeginDrawing();
    ClearBackground(BLANK);

    BeginMode3D(camera::CAMERA);

    planet::draw();

    DrawGrid(20, 1.0);
    EndMode3D();

    begin_imgui();
    {
        int flags = ImGuiWindowFlags_AlwaysAutoResize;
        ImGui::Begin("Planet", NULL, flags);
        ImGui::SliderInt("N Levels", &planet::N_LEVELS, 1, 8);
        ImGui::SliderFloat("Freq. Mult.", &planet::FREQ_MULT, 1.0, 4.0);
        ImGui::SliderFloat("Ampl. Mult.", &planet::AMPL_MULT, 0.05, 1.0);
        ImGui::SliderFloat("Freq. Init.", &planet::FREQ_INIT, 0.05, 10.0);
        ImGui::End();
    }
    end_imgui();

    DrawFPS(0, 0);
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
