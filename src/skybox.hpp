#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::skybox {

class Skybox {
private:
    const entt::entity entity;
    Matrix matrix;

public:
    Skybox(entt::entity entity);

    void update();
};

}  // namespace gefest::skybox
