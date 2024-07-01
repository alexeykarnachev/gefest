#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::gmodel {

class GModel {
public:
    entt::entity entity;

    Model model;
    Material material;
    Texture texture;

    bool is_culling_disabled;

    GModel(entt::entity entity, Model model, bool is_culling_disabled);
    GModel(
        entt::entity entity,
        Model model,
        Material material,
        Texture texture,
        bool is_culling_disabled
    );

    void draw();
};

}  // namespace gefest::gmodel
