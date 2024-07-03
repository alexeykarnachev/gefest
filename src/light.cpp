#include "light.hpp"

#include "registry.hpp"
#include "transform.hpp"
#include "utils.hpp"

namespace gefest::light {

AmbientLight::AmbientLight(entt::entity entity, Color color, float intensity)
    : entity(entity)
    , color(color)
    , intensity(intensity) {}

PointLight::PointLight(
    entt::entity entity, Color color, Vector3 attenuation, float intensity
)
    : entity(entity)
    , color(color)
    , attenuation(attenuation)
    , intensity(intensity) {}

void AmbientLight::set_shader_uniform(Shader shader) {
    utils::shader::set_color3(shader, "abmient_light.color", this->color);
    utils::shader::set_float(shader, "ambient_light.intensity", this->intensity);
}

void PointLight::set_shader_uniform(Shader shader) {
    auto tr = registry::registry.get<transform::Transform>(entity);

    utils::shader::set_vec3(shader, "point_light.position", tr.position);
    utils::shader::set_color3(shader, "point_light.color", this->color);
    utils::shader::set_vec3(shader, "point_light.attenuation", this->attenuation);
    utils::shader::set_float(shader, "point_light.intensity", this->intensity);
}

}  // namespace gefest::light
