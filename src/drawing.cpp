#include "drawing.hpp"

#include "constants.hpp"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include <cstdio>

namespace gefest::drawing {

// NOTE: the fragment shader of the `shader` must be `screen_rect.vert`
void draw_texture(RenderTexture render_texture, Shader shader) {
    rlDisableBackfaceCulling();
    BeginTextureMode(render_texture);
    BeginShaderMode(shader);

    DrawRectangle(0, 0, 1, 1, BLANK);

    EndShaderMode();
    EndTextureMode();

    rlEnableBackfaceCulling();

    SetTextureFilter(render_texture.texture, TEXTURE_FILTER_BILINEAR);
}

}  // namespace gefest::drawing
