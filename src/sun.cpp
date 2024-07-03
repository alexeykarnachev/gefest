#include "sun.hpp"

#include "constants.hpp"
#include "drawing.hpp"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "resources.hpp"

namespace gefest::sun {

Sun::Sun(entt::entity entity)
    : entity(entity) {}

void Sun::update() {}

// TODO: factor out texture generation function into a separate unit
Texture generate_geosphere_texture(int size) {
    // TODO: this render texture should be registered
    // and cleaned up by resources manager
    RenderTexture render_texture = LoadRenderTexture(size, size);
    auto shader = resources::SUN_TEXTURE_SHADER;

    drawing::draw_texture(render_texture, shader);
    return render_texture.texture;
}

}  // namespace gefest::sun
