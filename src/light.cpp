#include "light.hpp"

namespace gefest::light {

PointLight::PointLight(
    Color color, Vector3 position, Vector3 attenuation, float intensity
)
    : color(color)
    , position(position)
    , attenuation(attenuation)
    , intensity(intensity) {}

void PointLight::set_shader_uniform(Shader shader) {
    int color_loc = GetShaderLocation(shader, "point_light.color");
    int position_loc = GetShaderLocation(shader, "point_light.position");
    int attenuation_loc = GetShaderLocation(shader, "point_light.attenuation");
    int intensity_loc = GetShaderLocation(shader, "point_light.intensity");

    auto color = ColorNormalize(this->color);

    SetShaderValue(shader, color_loc, &color, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, position_loc, &this->position, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, attenuation_loc, &this->attenuation, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, intensity_loc, &this->intensity, SHADER_UNIFORM_FLOAT);
}

}  // namespace gefest::light
