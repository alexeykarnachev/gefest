#include "skybox.hpp"

#include "drawing.hpp"
#include "raylib/rlgl.h"
#include "resources.hpp"

namespace gefest::skybox {

float STARS_FREQUENCY = 300.0;
float STARS_MIN_BRIGHTNESS = 0.83;

float NEBULA_FREQUENCY = 1.3;
float NEBULA_MIN_BRIGHTNESS = 0.3;

static int RENDER_TEXTURE_SIZE = 4096;
static RenderTexture RENDER_TEXTURE;

void generate() {
    if (IsRenderTextureReady(RENDER_TEXTURE)) {
        UnloadRenderTexture(RENDER_TEXTURE);
    }

    RENDER_TEXTURE = LoadRenderTexture(RENDER_TEXTURE_SIZE, RENDER_TEXTURE_SIZE);
    auto shader = resources::SKYBOX_TEXTURE_SHADER;

    // stars uniforms
    int stars_frequency_loc = GetShaderLocation(shader, "stars_frequency");
    int stars_min_brightness_loc = GetShaderLocation(shader, "stars_min_brightness");

    SetShaderValue(shader, stars_frequency_loc, &STARS_FREQUENCY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(
        shader, stars_min_brightness_loc, &STARS_MIN_BRIGHTNESS, SHADER_UNIFORM_FLOAT
    );

    // nebula uniforms
    int nebula_frequency_loc = GetShaderLocation(shader, "nebula_frequency");
    int nebula_min_brightness_loc = GetShaderLocation(shader, "nebula_min_brightness");

    SetShaderValue(shader, nebula_frequency_loc, &NEBULA_FREQUENCY, SHADER_UNIFORM_FLOAT);
    SetShaderValue(
        shader, nebula_min_brightness_loc, &NEBULA_MIN_BRIGHTNESS, SHADER_UNIFORM_FLOAT
    );

    drawing::draw_texture(RENDER_TEXTURE, shader);
}

void draw() {
    Texture texture = RENDER_TEXTURE.texture;
    drawing::draw_skybox(texture);
}

}  // namespace gefest::skybox
