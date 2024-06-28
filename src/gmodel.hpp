#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::gmodel {

class GModel {
public:
    entt::entity entity;

    Model model;

    GModel(entt::entity entity, Model model);

    void draw();
};

class GMesh {
public:
    entt::entity entity;

    Mesh mesh;
    Material material;

    GMesh(entt::entity entity, Mesh mesh);
    GMesh(entt::entity entity, Mesh mesh, Material material);

    void draw();
};

}
