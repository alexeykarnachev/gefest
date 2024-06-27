#include "asteroid.hpp"

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"
#include "registry.hpp"
#include "resources.hpp"
#include "transform.hpp"
#include <cstdio>

namespace gefest::asteroid {

Asteroid::Asteroid(entt::entity entity)
    : entity(entity) {}

void Asteroid::update() {}

void Asteroid::draw() {
    auto &tr = registry::registry.get<transform::Transform>(this->entity);
    Matrix mat = tr.get_matrix();

    Mesh mesh = resources::SPHERE_MESH;
    Material material = resources::ASTEROID_MATERIAL;

    DrawMesh(mesh, material, mat);
}

}  // namespace gefest::asteroid
