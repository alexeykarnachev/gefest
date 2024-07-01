#include "light.hpp"

#include "registry.hpp"
#include "transform.hpp"

namespace gefest::light {

PointLight::PointLight(
    entt::entity entity, Color color, Vector3 attenuation, float intensity
)
    : entity(entity)
    , color(color)
    , attenuation(attenuation)
    , intensity(intensity) {}

void PointLight::set_shader_uniform(Shader shader) {
    auto tr = registry::registry.get<transform::Transform>(entity);

    int color_loc = GetShaderLocation(shader, "point_light.color");
    int position_loc = GetShaderLocation(shader, "point_light.position");
    int attenuation_loc = GetShaderLocation(shader, "point_light.attenuation");
    int intensity_loc = GetShaderLocation(shader, "point_light.intensity");

    auto color = ColorNormalize(this->color);
    auto position = tr.position;

    SetShaderValue(shader, color_loc, &color, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, position_loc, &position, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, attenuation_loc, &this->attenuation, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, intensity_loc, &this->intensity, SHADER_UNIFORM_FLOAT);
}

}  // namespace gefest::light
