#include "editor.hpp"

#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "planet.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"

namespace gefest {
namespace editor {

void load() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    GLFWwindow *window = (GLFWwindow *)GetWindowHandle();
    glfwGetWindowUserPointer(window);
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 420 core");
    ImGui::StyleColorsDark();
}

void unload() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void update_and_draw() {
    begin();

    {
        int flags = ImGuiWindowFlags_AlwaysAutoResize;
        ImGui::Begin("Planet", NULL, flags);

        ImGui::SliderFloat3("Position", (float *)&planet::PLANET_POSITION, -50.0, 50.0);

        ImGui::Separator();

        ImGui::SliderInt("N Levels", &planet::N_LEVELS, 1, 8);
        ImGui::SliderFloat("Freq. Mult.", &planet::FREQ_MULT, 1.0, 4.0);
        ImGui::SliderFloat("Ampl. Mult.", &planet::AMPL_MULT, 0.05, 1.0);
        ImGui::SliderFloat("Freq. Init.", &planet::FREQ_INIT, 0.05, 4.0);

        ImGui::Separator();

        ImGui::SliderFloat("Water Level", &planet::WATER_LEVEL, 0.0, planet::SAND_LEVEL);
        ImGui::SliderFloat(
            "Sand Level",
            &planet::SAND_LEVEL,
            planet::WATER_LEVEL + EPSILON,
            planet::GRASS_LEVEL
        );
        ImGui::SliderFloat(
            "Grass Level",
            &planet::GRASS_LEVEL,
            planet::SAND_LEVEL + EPSILON,
            planet::ROCK_LEVEL
        );
        ImGui::SliderFloat(
            "Rock Level", &planet::ROCK_LEVEL, planet::GRASS_LEVEL + EPSILON, 1.0
        );

        ImGui::End();
    }

    end();
}

}  // namespace editor
}  // namespace gefest
