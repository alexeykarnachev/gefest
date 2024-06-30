#include "sun.hpp"

#include "constants.hpp"
#include "drawing.hpp"
#include "light.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include "raylib/rlgl.h"
#include "resources.hpp"

namespace gefest::sun {

Vector3 POSITION = {
    constants::SCALE * 6e5f, constants::SCALE * 7e5f, -constants::SCALE * 6e5f
};
static float RADIUS = constants::SCALE * 5e4;

static Color COLOR = {255, 240, 255, 255};
static Vector3 ATTENUATION = {1.0, 0.0, 0.0};
static float INTENSITY = 1.0;

static int RENDER_TEXTURE_SIZE = 4096;
static RenderTexture RENDER_TEXTURE;
static Matrix MATRIX;

void generate() {
    if (IsRenderTextureReady(RENDER_TEXTURE)) {
        UnloadRenderTexture(RENDER_TEXTURE);
    }

    RENDER_TEXTURE = LoadRenderTexture(RENDER_TEXTURE_SIZE, RENDER_TEXTURE_SIZE);
    auto shader = resources::SUN_TEXTURE_SHADER;

    rlDisableBackfaceCulling();
    BeginTextureMode(RENDER_TEXTURE);
    BeginShaderMode(shader);

    DrawRectangle(0, 0, 1, 1, BLANK);

    EndShaderMode();
    EndTextureMode();

    rlEnableBackfaceCulling();

    SetTextureFilter(RENDER_TEXTURE.texture, TEXTURE_FILTER_BILINEAR);
}

light::PointLight get_point_light() {
    light::PointLight point_light(COLOR, POSITION, ATTENUATION, INTENSITY);
    return point_light;
}

void update() {
    Matrix t = MatrixTranslate(POSITION.x, POSITION.y, POSITION.z);
    Matrix s = MatrixScale(RADIUS, RADIUS, RADIUS);

    MATRIX = MatrixMultiply(s, t);
}

void draw() {
    Texture texture = RENDER_TEXTURE.texture;
    drawing::draw_sphere(texture, MATRIX);
}

}  // namespace gefest::sun
