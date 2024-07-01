#include "asteroid.hpp"

#include "drawing.hpp"
#include "entt/entity/fwd.hpp"
#include "resources.hpp"
#include <cstdio>

namespace gefest::asteroid {

Asteroid::Asteroid(entt::entity entity)
    : entity(entity) {}

void Asteroid::update() {}

// TODO: factor out texture generation function into a separate unit
Texture generate_geosphere_texture(int size) {
    // TODO: this render texture should be registered
    // and cleaned up by resources manager
    RenderTexture render_texture = LoadRenderTexture(size, size);
    auto shader = resources::ASTEROID_TEXTURE_SHADER;

    drawing::draw_texture(render_texture, shader);
    return render_texture.texture;
}

void update() {}

}  // namespace gefest::asteroid
