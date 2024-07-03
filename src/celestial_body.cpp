#include "celestial_body.hpp"

#include "entt/entity/fwd.hpp"

namespace gefest::celestial_body {

// -----------------------------------------------------------------------
// celestial body
CelestialBody::CelestialBody(entt::entity entity, Sun sun)
    : entity(entity)
    , type(Type::SUN)
    , sun(sun) {}

CelestialBody::CelestialBody(entt::entity entity, Planet planet)
    : entity(entity)
    , type(Type::PLANET)
    , planet(planet) {}

CelestialBody::CelestialBody(entt::entity entity, Asteroid asteroid)
    : entity(entity)
    , type(Type::PLANET)
    , asteroid(asteroid) {}

// -----------------------------------------------------------------------
// sun

// -----------------------------------------------------------------------
// planet

// -----------------------------------------------------------------------
// asteroid

}  // namespace gefest::celestial_body
