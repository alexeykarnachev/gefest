#include "celestial_body.hpp"

#include "constants.hpp"
#include "entt/entity/fwd.hpp"

namespace gefest::celestial_body {

CelestialBody::CelestialBody(entt::entity entity)
    : entity(entity) {}

void CelestialBody::update() {}

}  // namespace gefest::celestial_body
