#pragma once

#include "raylib/raylib.h"

namespace gefest::light {

class PointLight {
private:
    Color color;
    Vector3 position;
    Vector3 attenuation;
    float intensity;

public:
    PointLight(Color color, Vector3 position, Vector3 attenuation, float intensity);

    void set_shader_uniform(Shader shader);
};

}  // namespace gefest::light
