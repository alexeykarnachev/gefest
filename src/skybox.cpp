#include "skybox.hpp"

#include "camera.hpp"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "transform.hpp"

namespace gefest::skybox {

Skybox::Skybox(entt::entity entity)
    : entity(entity) {}

void Skybox::update() {
    auto &tr = registry::registry.get<transform::Transform>(entity);
    tr.position = camera::CAMERA.position;
}

}  // namespace gefest::skybox
