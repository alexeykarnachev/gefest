#pragma once

#include "entt/entity/fwd.hpp"
#include "raylib/raylib.h"

namespace gefest::light {

class AmbientLight {
private:
    const entt::entity entity;

    Color color;
    float intensity;

public:
    AmbientLight(entt::entity entity, Color color, float intensity);

    void set_shader_uniform(Shader shader);
};

class PointLight {
private:
    const entt::entity entity;

    Color color;
    Vector3 attenuation;
    float intensity;

public:
    PointLight(entt::entity entity, Color color, Vector3 attenuation, float intensity);

    void set_shader_uniform(Shader shader);
};

}  // namespace gefest::light
