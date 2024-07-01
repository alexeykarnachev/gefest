#include "gmodel.hpp"

#include "light.hpp"
#include "raylib/raylib.h"
#include "raylib/rlgl.h"
#include "registry.hpp"
#include "transform.hpp"
#include <cstdio>

namespace gefest::gmodel {

GModel::GModel(entt::entity entity, Model model, bool is_culling_disabled)
    : entity(entity)
    , model(model)
    , material(model.materials[0])
    , texture(model.materials[0].maps[0].texture)
    , is_culling_disabled(is_culling_disabled) {}

GModel::GModel(
    entt::entity entity,
    Model model,
    Material material,
    Texture texture,
    bool is_culling_disabled
)
    : entity(entity)
    , model(model)
    , material(material)
    , texture(texture)
    , is_culling_disabled(is_culling_disabled) {}

void GModel::draw() {
    auto tr = registry::registry.get<transform::Transform>(this->entity);
    Matrix matrix = tr.get_matrix();

    Material orig_material = this->model.materials[0];
    Texture orig_texture = orig_material.maps[0].texture;

    this->model.materials[0] = this->material;
    this->model.materials[0].maps[0].texture = this->texture;

    auto view = registry::registry.view<light::PointLight>();
    for (auto entity : view) {
        auto point_light = registry::registry.get<light::PointLight>(entity);
        point_light.set_shader_uniform(this->model.materials[0].shader);

        // TODO: support more than 1 light
        break;
    }

    if (this->is_culling_disabled) {
        rlDisableBackfaceCulling();
    } else {
        rlEnableBackfaceCulling();
    }

    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(matrix));
    DrawModel(this->model, Vector3Zero(), 1.0, WHITE);
    rlPopMatrix();

    this->model.materials[0] = orig_material;
    this->model.materials[0].maps[0].texture = orig_texture;
}

}  // namespace gefest::gmodel
