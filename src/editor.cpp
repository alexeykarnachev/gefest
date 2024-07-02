#include "editor.hpp"

#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "crosshair.hpp"
#include "dynamic_body.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "raylib/raylib.h"
#include "registry.hpp"
#include "ship.hpp"

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

void update_camera_follow() {
    ImGui::SliderFloat("Smoothness", &camera::FOLLOW_SMOOTHNESS, 0.0, 0.99);
    ImGui::SliderFloat("FOV multiplier", &camera::FOLLOW_SPEED_FOV_MULTIPLIER, 1.0, 30.0);
}

void update_camera() {
    static camera::Mode mode = camera::get_mode();

    ImGui::SliderFloat("FOV", &camera::CAMERA.fovy, 10.0, 170.0);
    ImGui::Text("Mode:");
    ImGui::RadioButton("Editor", (int *)&mode, (int)camera::Mode::EDITOR);
    ImGui::SameLine();
    ImGui::RadioButton("Player", (int *)&mode, (int)camera::Mode::FOLLOW);

    if (mode == camera::Mode::FOLLOW) update_camera_follow();

    camera::set_mode(mode);
}

void update_ship() {
    auto entity = registry::registry.view<registry::Player>().front();
    auto &body = registry::registry.get<dynamic_body::DynamicBody>(entity);
    auto &ship = registry::registry.get<ship::Ship>(entity);
    auto &crosshair = registry::registry.get<crosshair::Crosshair>(entity);

    static float engine_force_min = ship.engine_force * 0.1f;
    static float engine_force_max = ship.engine_force * 10.0f;
    static float projectile_speed_min = ship.projectile_speed * 0.1f;
    static float projectile_speed_max = ship.projectile_speed * 10.0f;
    static float crosshair_length_min = crosshair.length * 0.1f;
    static float crosshair_length_max = crosshair.length * 10.0f;
    static float crosshair_thickness_min = crosshair.thickness * 0.1f;
    static float crosshair_thickness_max = crosshair.thickness * 10.0f;

    ImGui::SeparatorText("Dynamic Body");
    ImGui::SliderFloat("Mass", &body.mass, 1.0, 200.0);
    ImGui::SliderFloat("Linear Damp.", &body.linear_damping, 1.0, 1000.0);
    ImGui::SliderFloat("Moment of Inertia", &body.moment_of_inertia, 1.0, 1000.0);
    ImGui::SliderFloat("Angular Damping", &body.angular_damping, 1.0, 1000.0);

    ImGui::SeparatorText("Ship");
    ImGui::SliderFloat(
        "Engine Force", &ship.engine_force, engine_force_min, engine_force_max
    );
    ImGui::SliderFloat("Pitch Magnitude", &ship.pitch_magnitude, 1.0, 1000.0);
    ImGui::SliderFloat("Roll Magnitude", &ship.roll_magnitude, 1.0, 1000.0);
    ImGui::SliderFloat("Shoot Rate", &ship.shoot_rate, 1.0, 30.0);
    ImGui::SliderFloat(
        "Proj. Speed", &ship.projectile_speed, projectile_speed_min, projectile_speed_max
    );
    ImGui::SliderFloat3(
        "Proj. Spawn", (float *)&ship.projectile_spawn_offset, -0.006, 0.006
    );

    ImGui::SeparatorText("Crosshair");
    ImGui::SliderFloat(
        "Length", &crosshair.length, crosshair_length_min, crosshair_length_max
    );
    ImGui::SliderFloat(
        "Thickness",
        &crosshair.thickness,
        crosshair_thickness_min,
        crosshair_thickness_max
    );
    ImGui::SliderFloat("Attenuation", &crosshair.attenuation, 0.0, 20.0);
    ImGui::SliderFloat("Start Alpha", &crosshair.start_alpha, 0.0, 1.0);
    ImGui::SliderFloat3("Offset", (float *)&crosshair.start_offset, -0.003, 0.003);

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
        if (collapsing_header("Ship")) update_ship();
    }
    ImGui::End();

    end();
}

}  // namespace gefest::editor
