#include "gmodel.hpp"

#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "resources.hpp"
#include "sun.hpp"
#include "transform.hpp"
#include <cstdio>

namespace gefest::gmodel {

GModel::GModel(entt::entity entity, Model model)
    : entity(entity)
    , model(model) {}

GMesh::GMesh(entt::entity entity, Mesh mesh)
    : entity(entity)
    , mesh(mesh)
    , material(resources::MODEL_MATERIAL) {}

GMesh::GMesh(entt::entity entity, Mesh mesh, Material material)
    : entity(entity)
    , mesh(mesh)
    , material(material) {}

void GModel::draw() {
    auto tr = registry::registry.get<transform::Transform>(this->entity);
    Matrix mat = tr.get_matrix();
    Shader shader = this->model.materials[0].shader;

    sun::set_shader_point_light(shader);

    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(mat));
    DrawModel(this->model, Vector3Zero(), 1.0, WHITE);
    rlPopMatrix();
}

void GMesh::draw() {
    auto &tr = registry::registry.get<transform::Transform>(this->entity);
    Matrix mat = tr.get_matrix();
    Shader shader = this->material.shader;

    sun::set_shader_point_light(shader);

    DrawMesh(this->mesh, this->material, mat);
}

}  // namespace gefest::gmodel
