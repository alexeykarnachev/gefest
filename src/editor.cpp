#include "editor.hpp"

#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "crosshair.hpp"
#include "dynamic_body.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "planet.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "registry.hpp"
#include "ship.hpp"
#include "skybox.hpp"

namespace gefest::editor {

static int ID = 0;

void push_id() {
    ImGui::PushID(ID++);
}

void pop_id() {
    ImGui::PopID();
}

void reset_id() {
    ID = 0;
}

bool collapsing_header(const char *name, bool is_opened) {
    int flags = is_opened ? ImGuiTreeNodeFlags_DefaultOpen : 0;
    return ImGui::CollapsingHeader(name, flags);
}

bool collapsing_header(const char *name) {
    return collapsing_header(name, true);
}

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
    reset_id();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void end() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void update_camera() {
    static camera::Mode mode = camera::get_mode();

    ImGui::SliderFloat("FOV", &camera::CAMERA.fovy, 10.0, 170.0);
    ImGui::Text("Mode:");
    ImGui::RadioButton("Editor", (int *)&mode, (int)camera::Mode::EDITOR);
    ImGui::SameLine();
    ImGui::RadioButton("Player", (int *)&mode, (int)camera::Mode::FOLLOW);

    if (mode == camera::Mode::FOLLOW) {
    }

    camera::set_mode(mode);
}

void update_skybox() {
    push_id();
    ImGui::SeparatorText("Stars");
    ImGui::SliderFloat("Frequency", &skybox::STARS_FREQUENCY, 10.0, 500.0);
    ImGui::SliderFloat("Min. Brightness", &skybox::STARS_MIN_BRIGHTNESS, 0.0, 1.0);
    pop_id();

    push_id();
    ImGui::SeparatorText("Nebula");
    ImGui::SliderFloat("Frequency", &skybox::NEBULA_FREQUENCY, 1.0, 10.0);
    ImGui::SliderFloat("Min. Brightness", &skybox::NEBULA_MIN_BRIGHTNESS, 0.0, 1.0);
    pop_id();
}

void update_planet() {
    ImGui::SliderFloat3("Position", (float *)&planet::PLANET_POSITION, -50.0, 50.0);

    ImGui::SeparatorText("Perlin Noise");
    ImGui::SliderInt("N Levels", &planet::N_LEVELS, 1, 8);
    ImGui::SliderFloat("Freq. Mult.", &planet::FREQ_MULT, 1.0, 4.0);
    ImGui::SliderFloat("Ampl. Mult.", &planet::AMPL_MULT, 0.05, 1.0);
    ImGui::SliderFloat("Freq. Init.", &planet::FREQ_INIT, 0.05, 4.0);

    ImGui::SeparatorText("Terrain");
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
}

void update_ship() {
    auto entity = registry::registry.view<registry::Player>().front();
    auto &body = registry::registry.get<dynamic_body::DynamicBody>(entity);
    auto &ship = registry::registry.get<ship::Ship>(entity);

    ImGui::SeparatorText("Dynamic Body");
    ImGui::SliderFloat("Mass", &body.mass, 1.0, 1000.0);
    ImGui::SliderFloat("Linear Damp.", &body.linear_damping, 1.0, 1000.0);
    ImGui::SliderFloat("Moment of Inertia", &body.moment_of_inertia, 1.0, 1000.0);
    ImGui::SliderFloat("Angular Damping", &body.angular_damping, 1.0, 1000.0);

    ImGui::SeparatorText("Ship");
    ImGui::SliderFloat("Engine Force", &ship.engine_force, 1.0, 5000.0);
    ImGui::SliderFloat("Pitch Magnitude", &ship.pitch_magnitude, 1.0, 1000.0);
    ImGui::SliderFloat("Roll Magnitude", &ship.roll_magnitude, 1.0, 1000.0);

    ImGui::SeparatorText("Crosshair");
    ImGui::SliderFloat("Length", &crosshair::LENGTH, 1.0, 100.0);
    ImGui::SliderFloat("Thickness", &crosshair::THICKNESS, 0.0, 0.1);
    ImGui::SliderFloat("Attenuation", &crosshair::ATTENUATION, 0.0, 20.0);
    ImGui::SliderFloat("Start Alpha", &crosshair::START_ALPHA, 0.0, 1.0);
    ImGui::SliderFloat3("Offset", (float *)&crosshair::START_OFFSET, -0.3, 0.3);

    ImGui::SeparatorText("Speed");
    ImGui::Text("Linear Speed: %f", body.get_linear_speed());
    ImGui::Text("Angular Speed: %f", body.get_angular_speed());
}

void update_and_draw() {
    begin();

    int flags = ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::Begin("Inspector", NULL, flags);
    {
        if (collapsing_header("Camera")) update_camera();
        if (collapsing_header("Skybox")) update_skybox();
        if (collapsing_header("Planet")) update_planet();
        if (collapsing_header("Ship")) update_ship();
    }
    ImGui::End();

    end();
}

}  // namespace gefest::editor
